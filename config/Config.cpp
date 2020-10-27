//
// Created by julian on 10/27/20.
//

#include "Config.h"

Config::Config() = default;
Config::~Config() = default;

void Config::setearBondad(bool bondad) {
    this->bondadDeParams = bondad && ( this->c > 0 &&
                                       this->N > 0 &&
                                       0 <= this->modoDebug &&
                                       this->modoDebug <= 1 );
}

void Config::setearCamaras(int camaras){
    this->c = camaras;
}
void Config::setearDimensiones(int dimensiones) {
    this->N = dimensiones;
}

int Config::obtenerCamaras() const {
    return this->c;
}

int Config::obtenerDimensiones() const {
    return this->N;
}

void Config::setearModoDebug(int modoDbg) {
    this->modoDebug = modoDbg;
}

bool Config::chequearBondadParams() const{
    return this->bondadDeParams;
}