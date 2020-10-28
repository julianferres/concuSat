//
// Created by julian on 10/27/20.
//

#include "Config.h"

Config::Config() = default;
Config::~Config() = default;

#include <iostream>

void Config::setearBondad(bool bondad) {
    this->bondadDeParams = bondad && ( c > 0 &&
                                       N > 0 &&
                                       modoDebug >= 0 &&
                                       modoDebug <= 1 );
}

void Config::setearCamaras(int camaras){
    this->c = camaras;
}
void Config::setearDimensiones(int dimensiones) {
    this->N = dimensiones;
}

int Config::obtenerCamaras() const {
    return c;
}

int Config::obtenerDimensiones() const {
    return N;
}

void Config::setearModoDebug(int modoDbg) {
    this->modoDebug = modoDbg;
}

bool Config::chequearBondadParams() const{
    return bondadDeParams;
}