//
// Created by julian on 11/2/20.
//

#include "FifoEscritura.h"

FifoEscritura::FifoEscritura(const std::string nombre) : Fifo(nombre) {
}

FifoEscritura::~FifoEscritura() {
}

void FifoEscritura::abrir() {
    do { fd = open(nombre.c_str(), O_WRONLY); }
    while (fd == -1 && errno == EINTR);
}

ssize_t FifoEscritura::escribir(const void *buffer, const ssize_t buffsize) const {
    ssize_t bytesEscritos;

    do { bytesEscritos = write(fd, buffer, buffsize); }
    while (bytesEscritos == -1 && errno == EINTR);

    return bytesEscritos;
}
