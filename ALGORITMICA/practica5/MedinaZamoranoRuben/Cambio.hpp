#ifndef CAMBIO_HPP
#define CAMBIO_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include "funciones.hpp"
#include <algorithm> 
#include <limits>
#include "Moneda.hpp"

using namespace std;

class Cambio{

	private: 
		vector <Moneda> monedas_;
		vector <int> solucion_;
		int ** matriz_;
		int suma_;
	public:
		Cambio(const string &fichero);
		Cambio(const vector<Moneda> &v);
		inline Cambio(){ cout <<"El objeto cambio require parametros"<<endl; exit(-1);};
		~Cambio();

		inline vector <Moneda> getMonedas(){return monedas_;};
		inline vector <int> getSolucion(){return solucion_;};
		inline int getSuma(){return suma_;};
		inline int ** getMatriz(){return matriz_;};

		inline void setMonedas(const vector <Moneda> &v){monedas_=v;};
		inline void setSolucion(const vector <int> &v){solucion_=v;};
		inline void setSuma(const int &suma){suma_=suma;};
		inline void setMatriz(int** m){matriz_=m;};

		bool hacerAlgoritmo(const int &n);
		bool hacerAlgoritmoDinamico(const int &n);

};



#endif
