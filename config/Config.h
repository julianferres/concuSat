//
// Created by julian on 10/27/20.
//

#ifndef CONCUSAT_CONFIG_H
#define CONCUSAT_CONFIG_H

#include "../logger/Logger.h"

/*
 * Config se ocupa de recibir los parametros, validar que los mismos sean validos
 * y se envia al Observatorio para configurar el mismo
 */
class Config {
public:
    Config();

    ~Config();

    void setearBondad(bool bondad);

    void setearCamaras(int camaras);

    void setearDimensiones(int dimensiones);

    [[nodiscard]] int obtenerCamaras() const;

    [[nodiscard]] int obtenerDimensiones() const;

    void setearModoDebug(int modoDebug);

    [[nodiscard]] int obtenerModoDebug() const;

    [[nodiscard]] bool chequearBondadParams() const;

private:
    bool bondadDeParams{};
    int c{}; //Cantidad de camaras
    int N{}; //Dimension de las fotos
    int modoDebug{};
};


#endif //CONCUSAT_CONFIG_H
