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