#include "funciones.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char * argv[]){
	int max=999999;
	int min=0;
	int num;
	int llamadas=0;
	vector<int> v;
	srand(time(NULL));

	if (argc!=2)
	{
		cout<<"Argumentos mal: <"<<argv[0]<<"><nElementos vector>"<<endl;
		exit(EXIT_FAILURE);
	}

	num=atoi(argv[1]);

	rellenarVector(v, num);
	mostrarVector(v);
	minimoMaximo(v, num-1, 0, num-1, max, min, llamadas);

	cout << "Maximo-> " << max << endl;
	cout << "Minimo-> " << min << endl;
	cout << "Llamadas-> " << llamadas << endl;

	return 0;
}