
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void invermat(int n, double **a, double &determ);

int main() {

    system ("clear");

    srand(time(NULL));
    ifstream label1 ("datos.in"); // Abre el archivo de entrada de datos

    // Definición de variables y asignación dinámica de memoria    

    int i, j, n=4;

        label1 >> n;

    double **a, determ = 0;

    a = new double* [n];

    for(j=0; j<n; j++){

        a[j] = new double [n];
    
    }    

    // Lectura de la matriz (label1 apunta a datos.in en el subdirectorio datos del home de usuario)

        for(i=0; i<n; i++){

                for(j=0; j<n; j++){

                          label1 >> a[i][j];
                }

    }

    cout << "Imprime la matriz de origen\n\n";

    // Matriz de origen; a

    for(i=0; i<n; i++){

                for(j=0; j<n; j++){

                         cout <<  a[i][j] << " ";
                }

    cout << endl;

        }

    cout << endl;

    invermat (n, a, determ);

    cout << "El determinante de la matriz anterior es = " << determ << "\n\n";

    delete a;

    return 0;

}

void invermat(int n, double **a, double &determ) {

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

        for(i=0; i<n; i++){

                for(j=0; j<n; j++){

                         cout <<  a[i][j] << " ";
                }

    cout << endl;

        }

// Cálculo del determinante

    determ = 1.;

    for (i = 0; i < n; i++) {

        determ = determ * a[i][i];

    }

    delete L, D, X;

}