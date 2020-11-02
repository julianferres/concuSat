//
// Created by julian on 11/2/20.
//

#ifndef CONCUSAT_SERIALIZADORFOTO_H
#define CONCUSAT_SERIALIZADORFOTO_H

#include <vector>
#include <string>

using namespace std;

// Las fotos serializadas constan de un string de N*N + 1 numeros separados por espacios
// El primer numero indica la dimension N del vector<vector<int>> enviado, y los siguientes
// N*N numeros son los valores de los casilleros en si

class SerializadorFoto {
public:

// Decodifico el primer numero de la string y luego le siguen los proximos N*N numeros
    static vector<vector<int>> deserializarFoto(const string &fotoSerializada);

    static string serializarFoto(const vector<vector<int>> &foto);


};


#endif //CONCUSAT_SERIALIZADORFOTO_H
