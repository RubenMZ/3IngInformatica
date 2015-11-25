#ifndef ALGORITMOREINAS_HPP
#define ALGORITMOREINAS_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

class AlgoritmoReinas{

	private:
		int * posiciones_;

	public:

		inline int * getPosiciones(){return posiciones_;};
		inline int getPosicion(const int &i){return posiciones_[i];};
		inline void setPosiciones(int * v){posiciones_=v;};
		inline void setPosicion(const int &i, const int &n){posiciones_[i]=n;};

		void hacerAlgoritmo(const int &n);
		bool Lugar(const int &k, int * x);
		void muestraSolucion(int * x, const int &n);


};

#endif