#include "AlgoritmoReinas.hpp"
#include <iostream>

using namespace std;

int main(){

	AlgoritmoReinas alg;
	int reinas;

	cout<<"Introduce el numero de reinas: ";
	cin>>reinas;

	alg.hacerAlgoritmo(reinas);

	return 0;
}