#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP


#include "matriz.hpp"
#include <cmath>
#include "fstream"

template <class T>
void rellenaMatriz( Matriz <T> &m, const int &fil, const int &col, const int &a, const int &b){

    //Matriz <T> aux(fil,col);

    for (int i = 1; i <= fil; ++i)
    {
        for (int j = 1; j <= col; ++j)
        {
            m.elemento(i,j,rand()%(b-a)+a);
        }
    }
    m.filas(fil);
    m.columnas(col);
}

/*template <class T>
T determinanteRecursivo(const Matriz <T> &m, const int &n){
double det=0, p=0, h=0, k=0, i=0, j=0;
 Matriz<T> temp(n,n);

	if(n==1) {
		return m.elemento(1,1);
	} else 
		if(n==2) {
		 	det=(m.elemento(1,1)*m.elemento(2,2)-m.elemento(1,2)*m.elemento(2,1));
			return det;
		} else {
		 	for(p=1;p<=n;p++) {
		 		h = 1;
		 		k = 1;
		 		for(i=2;i<=n;i++) {
					 for( j=1;j<=n;j++) {
					 	if(j==p) {
					 		continue;
					 	}
					 	temp.elemento(h,k,m.elemento(i,j));
					 	k++;
					 	if(k==n) {
					 		h++;
					 		k = 1;
					 	}
					 }
		 		}
		 		det=det+m.elemento(1,p)*pow(-1,p)*determinanteRecursivo(temp,n-1);
		 	}
			 return (-1)*det;
	 	}

}

template <class T>
T determinanteIterativo(Matriz <T> &a, const int &n) {

// Algoritmo para la eliminación simple de Gauss

    T det,aux;
    T factor;
 
    for (int k = 1; k < n ; k++) {
        for (int i = k+1; i <= n;  i++) {
            factor = a.elemento(i,k)/a.elemento(k,k);
            for (int j = k+1; j < n+1 ; j++) {
            	aux=a.elemento(i,j) - factor * a.elemento(k,j);
                a.elemento(i,j, aux);
            }
        }
    }

// Cálculo del determinante
    det = 1;
    for (int i = 1; i <= n; i++) {
        det = det * a.elemento(i,i);
    }

    return det;
}
*/
double calculaMedia(vector<uint64_t> &tiempos){

	double suma=0;
	int n=tiempos.size();

	for (int i = 0; i < n; ++i)
	{
		suma+=(double)tiempos[i];
	}
	return suma/n;
}

void guardarTiempos(const vector<double> n, const vector<double> &tNS, const vector<double> &tNSE, const vector<double> &tS, const vector <double> &tSE, string fichero){

	ofstream f(fichero.c_str());

	if(!f.is_open()){
		cout<<"Fichero no abierto"<<endl;
		exit(-1);
	}

	for (int i = 0; i < n.size(); ++i)
	{
		f<<n[i]<<" "<<tNS[i]<<" "<<tNSE[i]<<" "<<tS[i]<<" "<<tSE[i]<<endl;
	}
	f.close();
}
#endif