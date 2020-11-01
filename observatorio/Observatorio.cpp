//
// Created by julian on 10/27/20.
//
#include "Observatorio.h"
#include <unistd.h>
#include <cstdlib>
#include <wait.h>
#include <sys/types.h>
#include <sys/wait.h>



vector<vector<int>> vectorizar(int* fotoHijo, int nHijo){
    vector<vector<int>> ans(nHijo, vector<int>(nHijo));
    for(int i = 0; i < nHijo*nHijo; ++i){
        ans[i/nHijo][i%nHijo] = fotoHijo[i];
    }
    return ans;
}

Observatorio::Observatorio(const Config& config){
    c = config.obtenerCamaras();
    N = config.obtenerDimensiones();
}
Observatorio::~Observatorio()= default;


//Promedia las entradas de las n camaras para obtener una imagen final
void Observatorio::aplanar(vvvi imagenes){
    vector<vector<int>> imagenAplanada(N, vector<int>(N));

    for(int row = 0; row < N; row++)
        for(int col = 0; col < N; col++){
            long suma = 0;
            for(int nCam = 0; nCam < c; nCam++){
                suma += imagenes[nCam][row][col];
            }
            imagenAplanada[row][col] = suma/c;
        }

    LOG_INFO("Se termino de Aplanar");
    for(int row = 0; row < N; row++)
        for(int col = 0; col < N; col++)
            cout << imagenAplanada[row][col] << " \n"[col == N-1];
    LOG_DEBUG("Se imprimio por salida estandar la imagen de la ");

}

void Observatorio::simular(){
    LOG_DEBUG("Observatorio. Mi pid es: " + to_string(getpid()));

    for(long long rondas = 0; rondas < 1; rondas++){
        //Por ahora simulo 3 rondas, despues tnego que hacerlo
        //Infinito y cerrarlo con SIGINT
        ronda(rondas);

    }
}

void Observatorio::ronda(long long numeroRonda) {
    LOG_INFO("Comenzando ronda numero " + to_string(numeroRonda));
    vvvi imagenes;
    vector<pid_t> pidsAjustadores(c);

    for(int nCamara = 0; nCamara < c; nCamara++){

        Camara camara(N);
        vector<vector<int>> imagen = camara.tomarFoto();

        string archivo = "/bin/ls";
        pid_t procId = fork();

        if ( procId == 0 ) {
            // codigo del hijo

            try {
                // En este paso el N, porque sino el proceso hijo no deberia saber cuanto es
                MemoriaCompartida<int> bufferCantidad ( archivo,'A', 1);
                int nHijo[1];
                bufferCantidad.leer(nHijo, 1);
                cout << "Hijo: Recibi un N = " << nHijo[0] << endl;
                MemoriaCompartida<int> buffer ( archivo,'B', nHijo[0]*nHijo[0]);
                int fotoHijo[(nHijo[0])*(nHijo[0])];
                buffer.leer(fotoHijo, nHijo[0]*nHijo[0]);

                vector<vector<int>> fotoHijoVector = vectorizar(fotoHijo, nHijo[0]);

                cout << "Recibi la foto: \n";
                for(int row = 0; row < nHijo[0]; row++){
                    for(int col = 0; col < nHijo[0]; col++){
                        cout << fotoHijoVector[row][col] << " \n"[col == nHijo[0]-1];
                    }
                }
                cout << "\n";

                vector<vector<int>> imagenAjustada = Ajustador::ajustar(fotoHijoVector);
                for(int row = 0; row < N; row++)
                    for(int col = 0; col < N; col++)
                        fotoHijo[row*N+col] = imagenAjustada[row][col];

                buffer.escribir(fotoHijo, nHijo[0] * nHijo[0]);

                sleep ( 4 ); //Lo pongo a dormir porque sino termina muy rapido

                cout << "Hijo: fin del proceso" << endl;
            } catch ( string& mensaje ) {
                cerr << mensaje << endl;
            }

            exit(0);
        } else {
            // codigo del padre
            try {


                MemoriaCompartida<int> bufferCantidad( archivo, 'A', 1); //Por aca va el N
                MemoriaCompartida<int> buffer ( archivo,'B', N*N); //Por aca va el array

                bufferCantidad.escribir(&N, 1);
                int fotoPadre[N*N];
                for(int row = 0; row < N; row++)
                    for(int col = 0; col < N; col++)
                        fotoPadre[row*N+col] = imagen[row][col];
                cout << "Mande la foto: \n";

                for(int row = 0; row < N; row++){
                    for(int col = 0; col < N; col++){
                        cout << imagen[row][col] << " \n"[col == N-1];
                    }
                }
                cout << "\n";


                buffer.escribir(fotoPadre, N*N);

                int status;
                waitpid(procId, &status, 0); //Espero a que el hijo termine de procesar

                buffer.leer(fotoPadre, N*N);
                imagen = vectorizar(fotoPadre, N);

                // espera a que termine el hijo
                cout << "Padre: esperando a que termine el hijo" << endl;
                wait(nullptr);
            } catch ( string& mensaje ) {
                cerr << mensaje << endl;
            }
        }

        imagenes.push_back(imagen);
    }

    aplanar(imagenes);

    cout << "Todo por ahora\n";
}




