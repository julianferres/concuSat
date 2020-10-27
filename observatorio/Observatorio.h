//
// Created by julian on 10/27/20.
//

#include "../config/Config.h"

#ifndef CONCUSAT_OBSERVATORIO_H
#define CONCUSAT_OBSERVATORIO_H

/*
 * Modelado del observatorio, que es quien se encarga de tomar las fotos, enviar a los ajustadores
 * y aplana el resultado de los mismos
 */
class Observatorio {
public:
    explicit Observatorio(const Config& config);
    ~Observatorio();

    void simular();

private:
    int c;
    int N;

};


#endif //CONCUSAT_OBSERVATORIO_H
