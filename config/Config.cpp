//
// Created by julian on 10/27/20.
//

#include "Config.h"

Config::Config() = default;
Config::~Config() = default;

void Config::setearBondad(bool bondad) {
    this->bondadDeParams = bondad && ( c > 0 &&
                                       N > 0 &&
                                       modoDebug >= 0 &&
                                       modoDebug <= 1 );
}

//Getters y setters a piaccere
void Config::setearCamaras(int camaras){
    this->c = camaras;
}
int Config::obtenerCamaras() const {
    return c;
}

void Config::setearDimensiones(int dimensiones) {
    this->N = dimensiones;
}
int Config::obtenerDimensiones() const {
    return N;
}

void Config::setearModoDebug(int modoDbg) {
    this->modoDebug = modoDbg;
}
int Config::obtenerModoDebug() const {
    return modoDebug;
}

bool Config::chequearBondadParams() const{
    return bondadDeParams;
}