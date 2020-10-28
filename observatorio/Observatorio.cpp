//
// Created by julian on 10/27/20.
//
#include<iostream>
using namespace std;

#include "Observatorio.h"
#include "../camara/Camara.h"

Observatorio::Observatorio(const Config& config){
    this->c = config.obtenerCamaras();
    this->N = config.obtenerDimensiones();
}
Observatorio::~Observatorio()= default;

void Observatorio::simular() {

    for(int nCamara = 0; nCamara < c; nCamara++){
        Camara camara(N);
        vector<vector<int>> act = camara.tomarFoto();

        for(int fila = 0; fila < N; fila++)
            for(int col = 0; col < N; col++)
                cout << act[fila][col] << " \n" [col == N-1];
        cout << "\n";

    }
    cout << "Todo por ahora\n";
}




