//
// Created by julian on 11/2/20.
//

#include "FifoLectura.h"

FifoLectura::FifoLectura(const std::string nombre) : Fifo(nombre) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
    do { fd = open(nombre.c_str(), O_RDONLY); }
    while (fd == -1 && errno == EINTR);
}

ssize_t FifoLectura::leer(void *buffer, const ssize_t buffsize) const {
    ssize_t bytesLeidos;

    do { bytesLeidos = read(fd, buffer, buffsize); }
    while (bytesLeidos == -1 && errno == EINTR);

    return bytesLeidos;
}
