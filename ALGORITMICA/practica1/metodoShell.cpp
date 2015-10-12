/*!
	@author Ruben
	@file metodoShell.cpp
	@brief Definicion de las funciones para Shell
*/

#include "metodoShell.hpp"
#include <vector>

using namespace std;

void Shell::ordenar(){

	vector<int> array=getVector();
  	int n = array.size();
 	int j, intervalo, temp;
 	intervalo = n/2;

		while (intervalo > 0) {

			for (int i=intervalo; i < n; i++) {
				 j = i;
				 temp = array[i];

				 while ((j >= intervalo) && (array[j - intervalo] > temp)) {
					 array[j] = array[j - intervalo];
					 j = j - intervalo;
				 }
				 array[j] = temp;
			}
			intervalo /= 2;
		}

    setVector(array);

}