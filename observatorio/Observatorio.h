//
// Created by julian on 10/27/20.
//

#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

typedef vector<vector<vector<int>>> vvvi;
//Abreviatura para ahorrar espacio

#include "../config/Config.h"
#include "../observatorio/Camara.h"
#include "../logger/Logger.h"
#include "Ajustador.h"
#include "../concu/MemoriaCompartida.h"


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

//    Este metodo se ocupa de correr las sucevivas rondas.
//    En caso de recibir un SIGINT, se ocupa de terminar la ronda actual,
//    liberar los recursos y salir de forma grateful
    void simular();

//    Dentro de este metodo se produce la toma de fotos (mediante la clase camara),
//    La creacion de diferentes procesos para ajustar cada una de las imagenes resultantes,
//    y el posterior aplando de la imagen
    void ronda(long long numeroRonda);

//    Este metodo recibe las imagenes ajustadas (de tamano NxN) y se ocupa
//    de emplear un algortimo que las combine (o aplane), retornando por stdout el
//    resultado final
    void aplanar(vvvi imagenes);

private:
    int c;
    int N;
};


#endif //CONCUSAT_OBSERVATORIO_H
