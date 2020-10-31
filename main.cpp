#include <iostream>
#include <cstring>
#include "config/Config.h"
#include "observatorio/Observatorio.h"
#include "logger/Logger.h"


using namespace std;

const string MSG_PARAMS_INVALIDOS  = "El formato de los parametros ingresados no es valido!\n";
const string DESCRIPCION_DE_PARAMS = "Uso: ./concuSat -c $CANTIDAD_DE_CAMARAS -N $TAMAÑO_GRILLA -debug $MODO_DEBUG\n"\
                                     "Descripcion de Parametros:\n"\
                                     " - CANTIDAD_DE_CAMARAS: (Numero entero mayor que 0) Cantidad de camaras a utilizar\n"\
                                     " - TAMAÑO_GRILLA: (Numero entero mayor que 0) Dimensiones de las fotografias a tomar y procesar\n"\
                                     " - MODO_DEBUG: (Valor 0 o 1) Para indicar si se quiere ejecutar en 'modo logger'\n";

const int PARAMETROS_ESPERADOS = 6;

Config llenarParams(char *argv[]){
    Config config;
    if(strcmp(argv[1], "-c") != 0 || strcmp(argv[3], "-N") != 0 || strcmp(argv[5], "-debug") != 0) {
        //Chequeo que los flags de los parametros esten correctamente ingresados
        config.setearBondad(false);
        return config;
    }
    try {
        config.setearCamaras(stoi(argv[2]));
        config.setearDimensiones(stoi(argv[4]));
        config.setearModoDebug(stoi(argv[6]));
        config.setearBondad(true); //Bondad es bool y tiene la info de la validez de los parametros

    } catch (const invalid_argument &e) {
            cout << e.what() << "\n";
            config.setearBondad(false);
    }
    return config;
}



int contadorDeParams(char* argv[]) {
    int i = 0;
    while(argv[i]) i++;
    return i - 1;
}

int main(int argc, char *argv[]) {

    int cantidadDeParams = contadorDeParams(argv);

    if(cantidadDeParams != PARAMETROS_ESPERADOS) {
        cout << MSG_PARAMS_INVALIDOS << DESCRIPCION_DE_PARAMS;
        return 0;
    }
    Config config = llenarParams(argv);

    if(!config.chequearBondadParams()) {
        //Problemas con los parametros
        cout << MSG_PARAMS_INVALIDOS << DESCRIPCION_DE_PARAMS;
        return 0;
    }
    Logger::iniciar(config.obtenerModoDebug());
    Observatorio observatorio(config);
    observatorio.simular();

    Logger::terminar();
    return 0;
}
