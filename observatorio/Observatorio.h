//
// Created by julian on 10/27/20.
//

#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

typedef vector<vector<vector<int>>> vvvi;
// Abreviatura para ahorrar espacio

#include "../concu/memoria/MemoriaCompartida.h"
#include "../config/Config.h"
#include "../logger/Logger.h"
#include "../observatorio/Camara.h"
#include "Ajustador.h"
#include "../serializador/SerializadorFoto.h"
#include "../concu/fifos/FifoLectura.h"
#include "../concu/fifos/FifoEscritura.h"


#ifndef CONCUSAT_OBSERVATORIO_H
#define CONCUSAT_OBSERVATORIO_H

/*
 * Modelado del observatorio, que es quien se encarga de tomar las fotos, enviar
 * a los ajustadores y aplana el resultado de los mismos
 */
class Observatorio {
public:
    explicit Observatorio(const Config &config);

    ~Observatorio();

    //    Este metodo se ocupa de correr las sucevivas rondas.
    //    En caso de recibir un SIGINT, se ocupa de terminar la ronda actual,
    //    liberar los recursos y salir de forma grateful
    void simular();

    //    Dentro de este metodo se produce la toma de fotos (mediante la clase
    //    camara), La creacion de diferentes procesos para ajustar cada una de las
    //    imagenes resultantes, y el posterior aplando de la imagen
    void ronda(long long numeroRonda);

    //    Este metodo recibe las fotos ajustadas (de tamano NxN) y se ocupa
    //    de emplear un algortimo que las combine (o aplane), retornando por
    //    stdout el resultado final
    void aplanar(vvvi fotos) const;

    //    Libera recursos de una ronda en particular
    void liberarRecursos();

    //Wrapper para leer del fifo, descserializar y logear algunas cosas
    vector<vector<int>> leerFifo(string actor, int nCamara);

    //Wrapper para serializar, escribir del fifo y logear algunas cosas
    void escribirFifo(const string& actor, int nCamara, const vector<vector<int>>& foto);


private:
    int c;
    int N;
    vector<FifoLectura> fifosLectura;
    vector<FifoEscritura> fifosEscritura;
    int FIFO_BUFFSIZE;
    const string ARCHIVO_FIFO = "/tmp/concuSat_fifo";
};

#endif // CONCUSAT_OBSERVATORIO_H
