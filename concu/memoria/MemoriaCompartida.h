//
// Created by julian on 10/31/0.
//

#ifndef CONCUSAT_MEMORIACOMPARTIDA_H
#define CONCUSAT_MEMORIACOMPARTIDA_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <cerrno>

using namespace std;

template<class T>
class MemoriaCompartida {

private:
    int shmId;
    T *ptrDatos;

    int cantidadProcesosAdosados() const;

public:
    MemoriaCompartida();

    void crear(const std::string &archivo, const int letra);

    void liberar();

    MemoriaCompartida(const std::string &archivo, const int letra, int cantidad);

    MemoriaCompartida(const MemoriaCompartida &origen);

    ~MemoriaCompartida();

    MemoriaCompartida<T> &operator=(const MemoriaCompartida &origen);

    void escribir(int *dato, int cantidad);

    void leer(int *salida, int cantidad) const;
};

template<class T>
MemoriaCompartida<T>::MemoriaCompartida():shmId(0), ptrDatos(NULL) {
}

template<class T>
void MemoriaCompartida<T>::crear(const std::string &archivo, const int letra) {
    key_t clave = ftok(archivo.c_str(), letra);

    if (clave > 0) {
        this->shmId = shmget(clave, sizeof(T), 0644 | IPC_CREAT);

        if (this->shmId > 0) {
            void *tmpPtr = shmat(this->shmId, NULL, 0);
            if (tmpPtr != (void *) -1) {
                this->ptrDatos = static_cast<T *> (tmpPtr);
            } else {
                std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
                throw mensaje;
            }
        } else {
            std::string mensaje = std::string("Error en shmget(): ") + std::string(strerror(errno));
            throw mensaje;
        }
    } else {
        std::string mensaje = std::string("Error en ftok(): ") + std::string(strerror(errno));
        throw mensaje;
    }
}

template<class T>
void MemoriaCompartida<T>::liberar() {
    int errorDt = shmdt((void *) this->ptrDatos);

    if (errorDt != -1) {
        int procAdosados = this->cantidadProcesosAdosados();
        if (procAdosados == 0) {
            shmctl(this->shmId, IPC_RMID, NULL);
        }
    } else {
        std::string mensaje = std::string("Error en shmdt(): ") + std::string(strerror(errno));
        throw mensaje;
    }
}

template<class T>
MemoriaCompartida<T>::MemoriaCompartida(const std::string &archivo, const int letra, const int cantidad):shmId(0),
                                                                                                         ptrDatos(
                                                                                                                 NULL) {
    key_t clave = ftok(archivo.c_str(), letra);

    if (clave > 0) {
        this->shmId = shmget(clave, cantidad * sizeof(T), 0644 | IPC_CREAT);

        if (this->shmId > 0) {
            void *tmpPtr = shmat(this->shmId, NULL, 0);
            if (tmpPtr != (void *) -1) {
                this->ptrDatos = static_cast<T *> (tmpPtr);
            } else {
                std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
                throw mensaje;
            }
        } else {
            std::string mensaje = std::string("Error en shmget(): ") + std::string(strerror(errno));
            throw mensaje;
        }
    } else {
        std::string mensaje = std::string("Error en ftok(): ") + std::string(strerror(errno));
        throw mensaje;
    }
}

template<class T>
MemoriaCompartida<T>::MemoriaCompartida(const MemoriaCompartida &origen):shmId(origen.shmId) {
    void *tmpPtr = shmat(origen.shmId, NULL, 0);

    if (tmpPtr != (void *) -1) {
        this->ptrDatos = static_cast<T *> (tmpPtr);
    } else {
        std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
        throw mensaje;
    }
}

template<class T>
MemoriaCompartida<T>::~MemoriaCompartida() {
    int errorDt = shmdt(static_cast<void *> (this->ptrDatos));

    if (errorDt != -1) {
        int procAdosados = this->cantidadProcesosAdosados();
        if (procAdosados == 0) {
            shmctl(this->shmId, IPC_RMID, NULL);
        }
    } else {
        std::cerr << "Error en shmdt(): " << strerror(errno) << std::endl;
    }
}

template<class T>
MemoriaCompartida<T> &MemoriaCompartida<T>::operator=(const MemoriaCompartida &origen) {
    this->shmId = origen.shmId;
    void *tmpPtr = shmat(this->shmId, NULL, 0);

    if (tmpPtr != (void *) -1) {
        this->ptrDatos = static_cast<T *> (tmpPtr);
    } else {
        std::string mensaje = std::string("Error en shmat(): ") + std::string(strerror(errno));
        throw mensaje;
    }

    return *this;
}

template<class T>
void MemoriaCompartida<T>::escribir(int *dato, int cantidad) {
    copy(dato, dato + cantidad, this->ptrDatos);
}

template<class T>
void MemoriaCompartida<T>::leer(int *salida, int cantidad) const {
    for (int i = 0; i < cantidad; ++i) {
        salida[i] = (this->ptrDatos)[i];
    }
}

template<class T>
int MemoriaCompartida<T>::cantidadProcesosAdosados() const {
    shmid_ds estado;
    shmctl(this->shmId, IPC_STAT, &estado);
    return estado.shm_nattch;
}

#endif //CONCUSAT_MEMORIACOMPARTIDA_H
