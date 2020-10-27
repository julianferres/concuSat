//
// Created by julian on 10/27/20.
//
#include<iostream>

#include "Observatorio.h"

Observatorio::Observatorio(const Config& config){
    this->c = config.obtenerCamaras();
    this->N = config.obtenerDimensiones();
}
Observatorio::~Observatorio(){}

void Observatorio::simular() {
    std::cout << this ->c << " " << this->N << std::endl;
}



