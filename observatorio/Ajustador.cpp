//
// Created by julian on 10/30/20.
//

#include "Ajustador.h"


//Mi version de ajustar "suaviza la imagen recibida", poniendo el promedio
//ponderado de la casilla y de sus vecinas
// Ponderaciones:
//      1 para la principal
//    0.5 para las adyacentes
//   0.25 para las esquinas
// Si algun elemento no tiene sus 9 casillas vecinas, se ponderan las que tengan
// Se trunca a entero en caso de ser decimal
vector<vector<int>> Ajustador::ajustar(vector<vector<int>> imagen) {

    int N = (int)imagen.size();
    vector<vector<int>> vectorAjustado(N, vector<int>(N));

    for(int row = 0; row < N; row++)
        for(int col = 0; col < N; col++){
            int cnt = 1, sumaPonderada = imagen[row][col];

            if(row > 0 && col > 0){ //Tiene vecino superior izquierdo
                sumaPonderada += imagen[row-1][col-1];
                cnt++;
            }
            if(row > 0){ //Tiene vecino superior
                sumaPonderada += 2*imagen[row-1][col];
                cnt++;
            }
            if(row > 0 && col < N-1){ //Tiene vecino superior derecho
                sumaPonderada += imagen[row-1][col+1];
                cnt++;
            }
            if(col < N-1){ //Tiene vecino derecho
                sumaPonderada += imagen[row][col+1];
                cnt++;
            }
            if(row < N-1 && col < N-1){ //Tiene vecino inferior derecho
                sumaPonderada += imagen[row+1][col+1];
                cnt++;
            }
            if(row < N-1){ //Tiene vecino inferior
                sumaPonderada += imagen[row+1][col];
                cnt++;
            }
            if(row < N-1 && col > 0) { //Tiene vecino inferior izquierdo
                sumaPonderada += imagen[row+1][col-1];
                cnt++;
            }
            if(col > 0){ //Tiene vecino izquierdo
                sumaPonderada += imagen[row][col-1];
                cnt++;
            }

            vectorAjustado[row][col] = sumaPonderada/(4*cnt);
        }

    return vectorAjustado;



}
