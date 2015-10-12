#include "funciones.hpp"


template <class T>
T determinanteIterativo (const Matriz <T> &m){

	// Algoritmo para la eliminación simple de Gauss

    int i, j, k;

    double factor;

    double **L, *D, *X;
 
    X = new double [n]; D = new double [n];

    L = new double* [n];
  
    for (j = 0; j < n; j++)

        L[j] = new double [n];

    for (k = 0; k < n - 1; k++) {
     
        for (i = k+1; i < n;  i++) {

            factor = a[i][k]/a[k][k];

            for (j = k+1; j < n + 1; j++) {

                a[i][j] = a[i][j] - factor * a[k][j];

            }
   

        }

    }

// Cálculo del determinante

    determ = 1.;

    for (i = 0; i < n; i++) {

        determ = determ * a[i][i];

    }

    delete L, D, X;
}

template <class T>
T determinanteRecursivo(const Matriz <T> &m);

template <class T>
void rellenaMatriz(const Matriz <T> &m, const int &fil, const int &col);