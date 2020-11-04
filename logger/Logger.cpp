//
// Created by julian on 10/27/20.
//

#include "Logger.h"

using namespace std;

//Declaro las variables de clase
string Logger::rutaArchivoLog = "concuSat.log";
ofstream Logger::outstream;
vector<string> Logger::stringsLoggerType;
int Logger::modoDebug;

void Logger::iniciar(int _modoDebug) {
    stringsLoggerType = {"INFO", "DEBUG"};
    rutaArchivoLog = "concuSat.log";
    outstream.open(rutaArchivoLog, ios::out);
    LOG_INFO("Iniciando log.");
    LOG_DEBUG("Iniciando log DEBUG.");
    modoDebug = _modoDebug;
}

//Cierro el archivo que tengo abierto para log, y termino
void Logger::terminar() {
    LOG_DEBUG("Terminando log DEBUG.");
    LOG_INFO("Terminando log.");
    outstream.close();
}

void Logger::escribir(int _modoDebug, string msg, string archivo, long linea) {
    //Cuando estamos en modo normal los LOG_DEBUG no tienen efecto
    if (modoDebug < _modoDebug) return;

    // En esta parte calculo todas las constantes de padding, para poder
    // alinear [INFO] y [DEBUG], el nombre y linea de archivo
    // la hora y el mensaje
    string timestamp = obtenerTimestamp();
    string nombreArchivo = limpiarPathArchivo(archivo);
    int largoMetadata = stringsLoggerType[_modoDebug].size() + nombreArchivo.size() + (linea >= 100);
    string padding(AJUSTE - largoMetadata + _modoDebug, ' ');

    outstream << "[" << stringsLoggerType[_modoDebug] << "]" << " "[_modoDebug];
    outstream << " " << limpiarPathArchivo(nombreArchivo) << ":" << to_string(linea);
    outstream << padding;
    outstream << "(" << timestamp << ") ||";
    outstream << " " << msg << "\n";
}

string Logger::obtenerTimestamp() {
    time_t tiempoAct = time(nullptr);
    struct tm *tiempoInfo;
    char buff[100];
    time(&tiempoAct);
    tiempoInfo = localtime(&tiempoAct);
    strftime(buff, sizeof(buff), "%H:%M:%S", tiempoInfo);
    return string(buff);
}

string Logger::limpiarPathArchivo(const string &pathArchivo) {
    string nombreArchivo;
    for (char c: pathArchivo) {
        nombreArchivo += c;
        if (c == '/') nombreArchivo = "";
        //Desecho lo anterior al caracter separador de carpetas en linux
    }
    return nombreArchivo;
}