//
// Created by julian on 10/27/20.
//

#ifndef CONCUSAT_DEBUG_H
#define CONCUSAT_DEBUG_H

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

const int INFO = 0, DEBUG = 1;
const int AJUSTE = 32; //Sirve para alinear todas las lineas del log

//Macros para utilizar en el texto que son exportadas
//Son las que vamos a usar para poder tener la salida de los programas.
#define LOG_INFO( msg ) Logger::escribir(INFO, msg, __FILE__, __LINE__)
#define LOG_DEBUG( msg ) Logger::escribir(DEBUG, msg, __FILE__, __LINE__)

class Logger {

public:

//    Inicializa el log con el nivel debug introducido (INFO = 0, DEBUG = 1)
    explicit Logger(int _modoDebug);
    ~Logger();

//    Indica que terminó el proceso de log
    void terminar();
//    Funcion para escribir en el archivo de log
    void escribir(int modoDebug, string msg, string archivo, long linea);

//    Saca el path del archivo, dejando solo el nombre y la extension
    static string limpiarPathArchivo(const string& nombreArchivo);


private:
    int modoDebug;
    vector<string> nivelLogStrings;

//    Obtiene un string con el tiempo que luego sera agregado cuando se logee una linea.
    static string obtenerTimestamp();

    vector<string> stringsLoggerType;
    string rutaArchivoLog;
    ofstream outstream;
};


#endif //CONCUSAT_DEBUG_H
