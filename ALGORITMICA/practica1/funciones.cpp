#include "funciones.hpp"
#include <cstdlib>
#include <cassert>     /* assert */

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