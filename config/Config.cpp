//
// Created by julian on 10/27/20.
//

#include "Config.h"

Config::Config() {}
Config::~Config() {}

void Config::setearBondad(bool bondad) {
    this->bondadDeParams = bondad && (this->c > 0 || this->N > 0);
}

void Config::setearCamaras(int camaras){
    this->c = camaras;
}
void Config::setearDimensiones(int dimensiones) {
    this->N = dimensiones;
}

void Config::setearModoDebug(int modoDebug) {
    this->modoDebug = modoDebug;
}

bool Config::chequearBondadParams(){
    return this->bondadDeParams;
}