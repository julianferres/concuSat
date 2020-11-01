//
// Created by julian on 10/30/20.
//

#include "Ajustador.h"


//Mi version de ajustar "suaviza la imagen recibida", poniendo el promedio
//ponderado de la casilla y de sus vecinas
// Ponderaciones:
//      1 para la principal
//    0.5 para las adyacentes
// Si algun elemento no tiene sus 9 casillas vecinas, se ponderan las que tengan
// Se trunca a entero en caso de ser decimal
// Dicho de otra manera, es similar a una convolucion con matriz deslizante igual a
// [0   0.5   0]
// [0.5  1  0.5]
// [0   0.5   0]
// Que en si lo que hace es suavizar la matriz (le baja un poco los picos y depresiones)
vector<vector<int>> Ajustador::ajustar(vector<vector<int>> imagen) {

    int N = (int) imagen.size();
    vector<vector<int>> vectorAjustado(N, vector<int>(N));

    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++) {
            int cnt = 1, sumaPonderada = 2 * imagen[row][col];

            if (row > 0) { //Tiene vecino superior
                sumaPonderada += imagen[row - 1][col];
                cnt++;
            }
            if (col < N - 1) { //Tiene vecino derecho
                sumaPonderada += imagen[row][col + 1];
                cnt++;
            }
            if (row < N - 1) { //Tiene vecino inferior
                sumaPonderada += imagen[row + 1][col];
                cnt++;
            }
            if (col > 0) { //Tiene vecino izquierdo
                sumaPonderada += imagen[row][col - 1];
                cnt++;
            }

            vectorAjustado[row][col] = sumaPonderada / (cnt * 2);
        }

    return vectorAjustado;


}
