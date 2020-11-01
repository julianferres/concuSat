//
// Created by julian on 10/28/20.
//

#include "Camara.h"

const int MAXIMO_VALOR_PIXEL = 1e6;

vector<vector<int>> Camara::tomarFoto() {
    vector<vector<int>> foto(N, vector<int>(N));
    for (int fila = 0; fila < N; fila++)
        for (int col = 0; col < N; col++)
            foto[fila][col] = rand() % MAXIMO_VALOR_PIXEL;

    return foto;
}

Camara::Camara(int dimensiones) {
    this->N = dimensiones;
}

Camara::~Camara() {}
