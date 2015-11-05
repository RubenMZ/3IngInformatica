#include "Cambio.hpp"
#include "funciones.hpp"

int main(){

	Cambio c("monedas.txt");
	vector<int> solucion;
	int suma=0;

	if(c.hacerAlgoritmo(432234)){
		solucion=c.getSolucion();
		suma = c.getSuma();
	}else{
		cout<<"No se ha encontrado solucion"<<endl;		
	}

	cout<<"Solucion ->"<<suma<<endl;
	mostrarVector(c.getMonedas());	

	imprimeSolucion(solucion);

	

	exit(EXIT_SUCCESS);
}
