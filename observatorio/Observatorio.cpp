//
// Created by julian on 10/27/20.
//
#include "Observatorio.h"
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include "../concu/señales/ObservatorioHandlerSIGINT.h"
#include "../concu/señales/SignalHandler.h"

#define SEPARADOR cout << "======================================" << endl
#define SEPARADOR_PUNTO cout << "......................................" << endl

Observatorio::Observatorio(const Config &config) {
    c = config.obtenerCamaras();
    N = config.obtenerDimensiones();

    //Estimo que voy a tener aprox 5 chars para cada numero (4 del numero <10000 mas el espacio)
    //Entonces uso 6 para asegurarme que no lo voy a desbordad y el +1 por la dimension que va
    //Al principio
    FIFO_BUFFSIZE = 6 * (N * N + 1);
}

Observatorio::~Observatorio() = default;


//Promedia las entradas de las n camaras para obtener una foto final
void Observatorio::aplanar(vvvi fotos) const {
    cout << "Comenzando Aplanado..." << endl;
    LOG_INFO("Comenzando Aplanado...\n");
    vector<vector<int>> fotoAplanada(N, vector<int>(N));

    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++) {
            long suma = 0;
            for (int nCam = 0; nCam < c; nCam++) {
                suma += fotos[nCam][row][col];
            }
            fotoAplanada[row][col] = suma / c;
        }

    SEPARADOR_PUNTO;
    cout << "IMAGEN APLANADA!!!!\n";
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            cout << fotoAplanada[row][col] << " \n"[col == N - 1];
    SEPARADOR_PUNTO;

    LOG_INFO("Se termino de Aplanar");
    cout << "Finalizó Aplanado" << endl;
}

//Deja limpios los vectores de solicitud de memoria compartida que una ronda usa
void Observatorio::liberarRecursos() {
    cout << "Comienzo a eliminar los fifos...\n";
    for (const auto& canalLectura: fifosLectura){
        canalLectura.eliminar();
    }
    for (const auto& canalEscritura: fifosEscritura){
        canalEscritura.eliminar();
    }
    fifosLectura.clear();
    fifosEscritura.clear();
    cout << "Termine de eliminar los fifos.\n";
}

//Hace las acciones de crear el fifo, leer y deserializar
vector<vector<int>> Observatorio::leerFifo(string actor, int nCamara){
    FifoLectura canal ( ARCHIVO_FIFO + to_string(nCamara) );
    char buffer[FIFO_BUFFSIZE];

    canal.abrir();
    fifosLectura.push_back(canal);
    cout << "[" << actor << " - Lector " << nCamara << "] A punto de leer del fifo" << endl;
    ssize_t bytesLeidos = canal.leer(static_cast<void*>(buffer),FIFO_BUFFSIZE);

    string mensaje = buffer;
    mensaje.resize ( bytesLeidos );
    cout << "[" << actor << " Lector " << nCamara << "] Lei el dato del fifo: " << mensaje << endl;
    canal.cerrar();
    return SerializadorFoto::deserializarFoto(mensaje);
}

void Observatorio::escribirFifo(const string& actor, int nCamara, const vector<vector<int>>& foto){
    FifoEscritura canal(ARCHIVO_FIFO + to_string(nCamara));

    canal.abrir();
    fifosEscritura.push_back(canal);
    cout << "[" << actor << " - Escritor " << nCamara << "] Se abrio el Canal de escritura" << endl;
    string fotoSerializada = SerializadorFoto::serializarFoto(foto);
    canal.escribir(static_cast<const void *>(fotoSerializada.c_str()), fotoSerializada.length());
    cout << "[" << actor << " - Escritor " << nCamara << "] Escribi el mensaje " << fotoSerializada << " en el fifo" << endl;
    canal.cerrar();
}


void Observatorio::simular() {

    LOG_DEBUG("Observatorio. Mi pid es: " + to_string(getpid()));

    // event handler para la senial SIGINT (-2)
    ObservatorioHandlerSIGINT sigint_handler;
    // se registra el event handler declarado antes
    SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

    // mientras no se reciba la senial SIGINT, el proceso realiza su trabajo
    long long nroRonda = 1;
    while (sigint_handler.getGracefulQuit() == 0) {
        LOG_INFO("Inicia la ronda numero: " + to_string(nroRonda));
        SEPARADOR;
        cout << "Comenzando ronda numero " + to_string(nroRonda) << "\n";
        SEPARADOR;
        ronda(nroRonda);
        LOG_INFO("Finalizó la ronda numero: " + to_string(nroRonda));
        cout << "Finalizó ronda numero " + to_string(nroRonda) << "\n";

        nroRonda++;
    }
    LOG_INFO("Se recibio una interrupcion, terminando...");

    // se recibio la senial SIGINT, el proceso termina
    SignalHandler::destruir();
}

void Observatorio::ronda(long long numeroRonda) {
    LOG_INFO("Comenzando ronda numero " + to_string(numeroRonda));
    vvvi fotos;
    Camara camara(N);
    vector<vector<int>> foto;


    for (int nCamara = 0; nCamara < c; nCamara++) { //Lanzo los procesos hijos
        pid_t procId = fork();
        if (procId == 0) {
            // codigo del hijo

            try {
                //Uso nCamara para padre->hijo
                vector<vector<int>> fotoHijoVector = leerFifo("Hijo", nCamara);

                sleep(2); //Lo pongo a dormir porque sino termina muy rapido
                vector<vector<int>> fotoAjustada = Ajustador::ajustar(fotoHijoVector);

                //Hago un offset de c para hijo -> padre
                escribirFifo("Hijo", nCamara + c, fotoHijoVector);

                cout << "[Hijo - Lector " << nCamara << "] Fin del proceso" << endl;

            } catch (string &mensaje) {
                cerr << mensaje << endl;
            }

            exit(0);
        } else {
            try {
                foto = camara.tomarFoto();

                //Uso nCamara para padre->hijo
                escribirFifo("Padre", nCamara, foto);

                //Hago un offset de c para hijo -> padre
                fotos.push_back(leerFifo("Padre", nCamara + c));

            } catch (string &mensaje) {
                cerr << mensaje << endl;
            }
        }
    }

    //Espero a que terminen todos
    for (int nCamara = 0; nCamara < c; nCamara++) {
        cout << "Padre: Termino el " << nCamara + 1 << "° hijo\n";
        waitpid(-1, nullptr, 0);
    }

    liberarRecursos();

    aplanar(fotos);
}




