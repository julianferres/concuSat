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

vector<vector<int>> vectorizar(const int *fotoHijo, int nHijo) {
    vector<vector<int>> ans(nHijo, vector<int>(nHijo));
    for (int i = 0; i < nHijo * nHijo; ++i) {
        ans[i / nHijo][i % nHijo] = fotoHijo[i];
    }
    return ans;
}
void vectorToArray(vector<vector<int>> foto, int* fotoArray, int nHijo){
    for (int row = 0; row < nHijo; row++)
        for (int col = 0; col < nHijo; col++)
            fotoArray[row * nHijo + col] = foto[row][col];
}


Observatorio::Observatorio(const Config &config) {
    c = config.obtenerCamaras();
    N = config.obtenerDimensiones();
}

Observatorio::~Observatorio() = default;


//Promedia las entradas de las n camaras para obtener una imagen final
void Observatorio::aplanar(vvvi imagenes) const {
    cout << "Comenzando Aplanado..." << endl;
    LOG_INFO("Comenzando Aplanado...\n");
    vector<vector<int>> imagenAplanada(N, vector<int>(N));

    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++) {
            long suma = 0;
            for (int nCam = 0; nCam < c; nCam++) {
                suma += imagenes[nCam][row][col];
            }
            imagenAplanada[row][col] = suma / c;
        }

    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            cout << imagenAplanada[row][col] << " \n"[col == N - 1];

    LOG_INFO("Se termino de Aplanar");
    cout << "Finalizó Aplanado" << endl;
}

//Deja limpios los vectores de solicitud de memoria compartida que una ronda usa
void Observatorio::liberarRecursos() {
    memCompartidas.clear();
    memCompartidasCantidad.clear();
}

void Observatorio::simular() {
    LOG_DEBUG("Observatorio. Mi pid es: " + to_string(getpid()));

    // event handler para la senial SIGINT (-2)
    AjustadorHandlerSIGINT sigint_handler;
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
    liberarRecursos();

    // se recibio la senial SIGINT, el proceso termina
    SignalHandler::destruir();
}

void Observatorio::ronda(long long numeroRonda) {
    LOG_INFO("Comenzando ronda numero " + to_string(numeroRonda));
    sleep(4);
    vvvi imagenes;
    Camara camara(N);
    vector<vector<int>> imagen;

    string archivo = "/bin/ls";

    for (int nCamara = 0; nCamara < c; nCamara++) { //Lanzo los procesos hijos
        // codigo del padre
        try {
            imagen = camara.tomarFoto();

            MemoriaCompartida<int> bufferCantidad(archivo, nCamara, 1); //Por aca va el N
            MemoriaCompartida<int> buffer(archivo, c + nCamara, N * N); //Por aca va el array

            memCompartidasCantidad.push_back(bufferCantidad);
            memCompartidas.push_back(buffer);

            bufferCantidad.escribir(&N, 1);

            //Convierto el vector a array
            int fotoPadre[N * N]; vectorToArray(imagen, fotoPadre, N);

            cout << "Mande la foto: \n";

            for (int row = 0; row < N; row++) {
                for (int col = 0; col < N; col++) {
                    cout << imagen[row][col] << " \n"[col == N - 1];
                }
            }
            cout << "\n";

            buffer.escribir(fotoPadre, N * N);
        } catch (string &mensaje) {
            cerr << mensaje << endl;
        }

        pid_t procId = fork();
        if (procId == 0) {
            // codigo del hijo

            try {
                // En este paso el N, porque sino el proceso hijo no deberia saber cuanto es
                MemoriaCompartida<int> bufferCantidad(archivo, nCamara, 1);
                int nHijo[1];
                bufferCantidad.leer(nHijo, 1);
                cout << "Hijo: Recibi un N = " << nHijo[0] << endl;
                MemoriaCompartida<int> buffer(archivo, c + nCamara, nHijo[0] * nHijo[0]);
                int fotoHijo[(nHijo[0]) * (nHijo[0])];
                buffer.leer(fotoHijo, nHijo[0] * nHijo[0]);

                vector<vector<int>> fotoHijoVector = vectorizar(fotoHijo, nHijo[0]);

                cout << "Recibi la foto: \n";
                for (int row = 0; row < nHijo[0]; row++) {
                    for (int col = 0; col < nHijo[0]; col++) {
                        cout << fotoHijoVector[row][col] << " \n"[col == nHijo[0] - 1];
                    }
                }
                cout << "\n";

                vector<vector<int>> imagenAjustada = Ajustador::ajustar(fotoHijoVector);
                for (int row = 0; row < N; row++)
                    for (int col = 0; col < N; col++)
                        fotoHijo[row * N + col] = imagenAjustada[row][col];

                buffer.escribir(fotoHijo, nHijo[0] * nHijo[0]);

                sleep(3); //Lo pongo a dormir porque sino termina muy rapido

                cout << "Hijo: fin del proceso" << endl;
            } catch (string &mensaje) {
                cerr << mensaje << endl;
            }

            exit(0);

        }
    }

    for (int nCamara = 0; nCamara < c; nCamara++) {
        cout << "Padre: Termino el " << nCamara + 1 << "° hijo\n";
        waitpid(-1, nullptr, 0);
    }

    for (int nCamara = 0; nCamara < c; nCamara++) {
        int fotoPadre[N * N];
        memCompartidas[nCamara].leer(fotoPadre, N * N);
        imagen = vectorizar(fotoPadre, N);
        imagenes.push_back(imagen);
    }

    aplanar(imagenes);
}




