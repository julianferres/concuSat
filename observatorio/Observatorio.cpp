//
// Created by julian on 10/27/20.
//
#include "Observatorio.h"

Observatorio::Observatorio(const Config& config){
    c = config.obtenerCamaras();
    N = config.obtenerDimensiones();
}
Observatorio::~Observatorio()= default;


//Promedia las entradas de las n camaras para obtener una imagen final
void Observatorio::aplanar(vvvi imagenes){
    vector<vector<int>> imagenAplanada(N, vector<int>(N));

    for(int row = 0; row < N; row++)
        for(int col = 0; col < N; col++){
            long suma = 0;
            for(int nCam = 0; nCam < c; nCam++){
                suma += imagenes[nCam][row][col];
            }
            imagenAplanada[row][col] = suma/c;
        }

    LOG_INFO("Se termino de Aplanar");
    for(int row = 0; row < N; row++)
        for(int col = 0; col < N; col++)
            cout << imagenAplanada[row][col] << " \n"[col == N-1];
    LOG_DEBUG("Se imprimio por salida estandar la imagen de la ");

}




void Observatorio::simular(){
    //Hacer cosas hasta sigint
}

void Observatorio::ronda() {
    vvvi imagenes;

    for(int nCamara = 0; nCamara < c; nCamara++){
        Camara camara(N);
        vector<vector<int>> imagenAct = camara.tomarFoto();

        for(int fila = 0; fila < N; fila++)
            for(int col = 0; col < N; col++)
                cout << imagenAct[fila][col] << " \n" [col == N - 1];
        cout << "\n";
        imagenes.push_back(imagenAct);
    }

    aplanar(imagenes);

    cout << "Todo por ahora\n";
}




