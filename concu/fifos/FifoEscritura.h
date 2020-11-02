//
// Created by julian on 11/2/20.
//

#ifndef CONCUSAT_FIFOESCRITURA_H
#define CONCUSAT_FIFOESCRITURA_H

#include "Fifo.h"

class FifoEscritura : public Fifo {
public:
    FifoEscritura(const std::string nombre);
    ~FifoEscritura();

    void abrir();
    ssize_t escribir(const void* buffer,const ssize_t buffsize) const;
};

#endif //CONCUSAT_FIFOESCRITURA_H
