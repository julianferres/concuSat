//
// Created by julian on 10/28/20.
//

#include <vector>
#include <cstdlib> //For rand()
#include "Config.h"

using namespace std;

#ifndef CONCUSAT_CAMARA_H
#define CONCUSAT_CAMARA_H


class Camara {
public:
    explicit Camara(int dimensiones);

    ~Camara();

    vector<vector<int>> tomarFoto();

private:
    int N; //Dimension de la foto
};


#endif //CONCUSAT_CAMARA_H
