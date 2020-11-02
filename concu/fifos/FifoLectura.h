//
// Created by julian on 11/2/20.
//

#ifndef CONCUSAT_FIFOLECTURA_H
#define CONCUSAT_FIFOLECTURA_H

#include "Fifo.h"

class FifoLectura : public Fifo {
public:
    FifoLectura(const std::string nombre);

    ~FifoLectura();

    void abrir();

    ssize_t leer(void *buffer, const ssize_t buffsize) const;
};


#endif //CONCUSAT_FIFOLECTURA_H
