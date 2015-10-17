#ifndef DETERMINANTEITERATIVO_HPP
#define DETERMINANTEITERATIVO_HPP

#include "matriz.hpp"


template <class T>
class DeterminanteIterativo{

	public:

		T determinanteIterativo(Matriz <T> &mat, const int &n) {

			// Algoritmo para la eliminación simple de Gauss

		    T det,aux;
		    T factor;
		    Matriz<T> a(mat);
		 
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
		    det = 1.0;
		    for (int i = 1; i <= n; i++) {
		        det = det * a.elemento(i,i);
		    }

		    return det;
		}
		inline DeterminanteIterativo(){};
		inline ~DeterminanteIterativo(){};
};

#endif