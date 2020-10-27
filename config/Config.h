//
// Created by julian on 10/27/20.
//

#ifndef CONCUSAT_CONFIG_H
#define CONCUSAT_CONFIG_H

#include "../logger/Logger.h"

class Config {
    public:
        Config();
        ~Config();

        void setearBondad(bool bondad);
        void setearCamaras(int camaras);
        void setearDimensiones(int dimensiones);
        void setearModoDebug(int modoDebug);
        bool chequearBondadParams();

    private:
        bool bondadDeParams;
        int c; //Cantidad de camaras
        int N; //Dimension de las fotos
        int modoDebug;
};


#endif //CONCUSAT_CONFIG_H
