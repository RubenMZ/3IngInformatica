#include "Cambio.hpp"
#include "funciones.hpp"
#include "Clock.hpp"
#include "Moneda.hpp"

int main(){

	Cambio cambio("monedas.txt");
	vector<int> solucion;
	vector<Moneda> monedas = cambio.getMonedas();
	int ** matriz;
	int suma=0;
	int dinero1=50000, dinero2=100000, inc=100, rep=5;
	Clock c;
	vector<double> tiempos1, tiempos2, tiemposM1, tiemposM2, cambios;
	char opcion='S';

	cout<<"Introduce tu incremento en cents (ej. 0.10€ = 10): ";
	cin>>inc;

	cout<<"Introduce numero de repeticiones: ";
	cin>>rep;

	cout<<"¿Desea mostrar resultados? (S/n): ";
	cin>>opcion;

	for (int i = dinero1; i <= dinero2; i+=inc)
	{
		for (int j = 0; j < rep; ++j)
		{

			tiempos1.clear();
			tiempos2.clear();

			c.start();
			cambio.hacerAlgoritmo(i);
			c.stop();

			tiempos1.push_back(c.elapsed());

			solucion=cambio.getSolucion();
			suma = cambio.getSuma();

			c.start();
			cambio.hacerAlgoritmoDinamico(i);
			c.stop();

			tiempos2.push_back(c.elapsed());

			matriz= cambio.getMatriz();

		}
		if(opcion=='S' || opcion=='s'){
			printf("*** VALOR -> %d ***\n", i);

			printf("ALGORITMO VORAZ\n");
			printf("---------------\n");
			if(suma==i)
				imprimeSolucion(solucion, monedas);
			else
				cout<<"No se ha calculado correctamente"<<endl;

			printf("ALGORITMO DINAMICO\n");
			printf("---------------\n");
			imprimeSolucionDinamica(matriz, monedas.size(), i, monedas);
		}
		tiemposM1.push_back( calculaMedia(tiempos1));
		tiemposM2.push_back( calculaMedia(tiempos2));
		cambios.push_back(i);

	}

	guardarTiempos(cambios, tiemposM1, tiemposM2, "tiemposGuardados.txt");



	exit(EXIT_SUCCESS);
}
