#ifndef ALGORITMOREINAS_HPP
#define ALGORITMOREINAS_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Tablero.hpp"

using namespace std;

class AlgoritmoReinas{

	private:
		vector<int> posiciones_;
		int contador_;
		Tablero tab_;
		int pos_;

	public:

		AlgoritmoReinas(){
			contador_=0;
			//posiciones_=NULL;
			srand(time(NULL));
			pos_=0;
		};



		inline vector <int> getPosiciones(){return posiciones_;};
		inline int getPosicion(const int &i){return posiciones_[i];};
		inline int getContador(){return contador_;};
		inline Tablero getTableros(){return tab_;};

		inline void setPosiciones(const vector<int> &v){posiciones_=v;};
		inline void setPosicion(const int &i, const int &n){
			if(i<pos_){
				posiciones_[i]=n;
			}else{
				pos_++;
				posiciones_.push_back(n);
			}
		};
		inline void setContador(const int &x){contador_=x;};
		inline void setTableros(const Tablero &x){tab_=x;};

		bool hacerAlgoritmo(const int &n);
		bool Lugar(const int &k, const vector<int> &x);
		//void muestraSolucion(int * x, const int &n);
		bool hacerLasVegas(const int &n);

};

#endif