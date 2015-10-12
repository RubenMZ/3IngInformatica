/*!
	@author Ruben
	@file funciones.cpp
	@brief Definicion de las funciones basicas para el procesado de los datos
*/


#include "funciones.hpp"
#include <cstdlib>
#include <cassert>     /* assert */
#include <fstream>
#include <iostream>

using namespace std;

void rellenarVector(vector<int> &v, const int &n){

	for (int i = 0; i < n; ++i)
	{
		v.push_back(rand()%10000);
	}
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

bool estaOrdenado(const vector <int> v){

	for (int i = 1; i < v.size(); ++i)
	{
			assert(v[i]>=v[i-1]);
	}
	return true;
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