//
// Created by julian on 11/2/20.
//

#include "SerializadorFoto.h"

string SerializadorFoto::serializarFoto(const vector<vector<int>> &foto) {
    int N = (int) foto.size();
    string fotoSerializada = to_string(N);

    for (int row = 0; row < N; ++row)
        for (int col = 0; col < N; col++)
            fotoSerializada += " " + to_string(foto[row][col]);

    return fotoSerializada;
}

vector<vector<int>> SerializadorFoto::deserializarFoto(const string &fotoSerializada) {
    string actNumber;
    int i = 0;

    while (fotoSerializada[i] != ' ') { actNumber += fotoSerializada[i++]; }
    i++; //Para salir del espacio
    int N = stoi(actNumber);

    vector<vector<int>> foto(N, vector<int>(N));

    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++) {
            actNumber = "";
            while (fotoSerializada[i] != ' ') { actNumber += fotoSerializada[i++]; }

            i++; //Para salir del espacio
            foto[row][col] = stoi(actNumber);
        }

    return foto;
}
