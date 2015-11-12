#include "Cambio.hpp"
#include "funciones.hpp"

int main(){

	Cambio c("monedas.txt");
	vector<int> solucion;
	vector<int> monedas;
	int ** matriz;
	int suma=0;
	int dinero;

	cout<<"Introduce tu cambio en cents (ej. 14.50€ = 1450):";
	cin>>dinero;

	if(c.hacerAlgoritmo(dinero)){
		solucion=c.getSolucion();
		suma = c.getSuma();
	}else{
		cout<<"No se ha encontrado solucion"<<endl;		
	}

	if(suma==dinero)
		imprimeSolucion(solucion);
	else
		cout<<"No se ha calculado correctamente"<<endl;

	c.hacerAlgoritmoDinamico(dinero);


	monedas=c.getMonedas();
	matriz= c.getMatriz();
	
	for (unsigned int i = 0; i <monedas.size() ; ++i)
	{
		cout<<monedas[i]<<"-> ";
		for (int j = 0; j <= dinero; ++j)
		{
			cout<<"  "<<matriz[i][j]<<"  ";
		}
		cout<<endl;
	}

	imprimeSolucionDinamica(matriz, monedas.size(), dinero, monedas);

	exit(EXIT_SUCCESS);
}
