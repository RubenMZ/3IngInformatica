#include "funciones.hpp"
#include <cstdlib>

void rellenarVector(vector<int> &v, const int &n){

	for (int i = 0; i < n; ++i)
	{
		v.push_back(rand()%10000);
	}
}

uint64_t calculaMedia(vector<uint64_t> &tiempos, const int &n){

	uint64_t suma=0;

	for (int i = 0; i < n; ++i)
	{
		suma+=tiempos[0];
	}
	return suma/n;
}