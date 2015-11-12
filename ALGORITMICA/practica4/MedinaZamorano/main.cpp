#include "Cambio.hpp"
#include "funciones.hpp"

int main(){

	Cambio c("monedas.txt");
	vector<int> solucion;
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
	

	exit(EXIT_SUCCESS);
}
