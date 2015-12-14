#include "AlgoritmoReinas.hpp"
#include <iostream>
#include "Tablero.hpp"

using namespace std;

int main(){

	AlgoritmoReinas alg;
	int reinas;
	Tablero t;
	int contador=0;
	int intentos=0;
	bool bandera=false;
	char opcion;
	char opcion2;

	cout<<"Introduce el numero de reinas: ";
	cin>>reinas;

	t.setOrdenTablero(reinas);

	cout<<"Quiere mostrar los tableros graficamente? (S/n): ";
	cin>>opcion2;

	cout<<"\E[32m*** SOLUCION BACKTRACKING ***\e[0m"<<endl;
	if(alg.hacerAlgoritmo(reinas)==false){
		cout<<"No tiene solucion"<<endl;
	}else{
		
		t=alg.getTableros();
		if(opcion2=='S' || opcion2=='s')
			t.mostrarTableros();
	}
	contador = alg.getContador();
	cout<<"Soluciones = "<<contador<<endl;
	
	cout<<"Desea ejecutar el algoritmo Las Vegas? (S/n): ";
	cin>>opcion;


	if(opcion=='S' || opcion=='s'){

		cout<<"Quiere mostrar los tableros graficamente? (S/n): ";
		cin>>opcion2;

		cout<<"\E[32m*** SOLUCION VEGAS ***\e[0m"<<endl;
		
		if(contador==0){
			cout<<"No tiene solucion"<<endl;
		}else{
			intentos=0;
			t.eraseTableros();
			while(bandera!=true){
				intentos++;
				if(alg.hacerLasVegas(reinas)==true){
					t.addTablero(alg.getTableros());
					if(opcion2=='S' || opcion2=='s')
						t.mostrarTableros();
					bandera=true;
				}else{
					//cout<<"No encuentra solucion"<<endl;
				}

			}
			cout<<"Intentos = "<<intentos<<endl;
		}
	}

	cout<<"Desea buscar las n soluciones del algoritmo Las Vegas? (S/n): ";
	cin>>opcion;

	if(opcion=='S' || opcion=='s'){

		cout<<"Quiere mostrar los tableros graficamente? (S/n): ";
		cin>>opcion2;

		cout<<"\E[32m*** SOLUCION N-VEGAS ***\e[0m"<<endl;
		
		if(contador==0){
			cout<<"No tiene solucion"<<endl;
		}else{
			t.eraseTableros();
			intentos=0;
			while(contador!=t.getNTablero()){
				intentos++;
				if(alg.hacerLasVegas(reinas)==true){
					t.addTablero(alg.getTableros());
				}
			}
			if(opcion2=='S' || opcion2=='s')
				t.mostrarTableros();
			cout<<"Intentos = "<<intentos<<endl;
			cout<<"Soluciones = "<<t.getNTablero()<<endl;
		}
	}

	return 0;
}