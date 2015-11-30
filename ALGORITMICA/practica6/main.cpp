#include "AlgoritmoReinas.hpp"
#include <iostream>
#include "Tablero.hpp"

using namespace std;

int main(){

	AlgoritmoReinas alg;
	int reinas;
	Tablero t;
	int contador;
	int intentos=0;
	bool bandera=false;
	char opcion;

	cout<<"Introduce el numero de reinas: ";
	cin>>reinas;

	t.setOrdenTablero(reinas);

	cout<<"*** SOLUCION BACKTRACKING ***"<<endl;
	if(alg.hacerAlgoritmo(reinas)==false){
		cout<<"No tiene solucion"<<endl;
	}else{
		
		t=alg.getTableros();
		t.mostrarTableros();
	}
	contador = alg.getContador();
	cout<<"Soluciones = "<<contador<<endl;
	
	cout<<"Desea ejecutar el algoritmo Las Vegas? (S/n): ";
	cin>>opcion;

	if(opcion=='S' || opcion=='s'){
		cout<<"*** SOLUCION VEGAS ***"<<endl;
		
		if(contador==0){
			cout<<"No tiene solucion"<<endl;
		}else{
			intentos=0;
			t.eraseTableros();
			while(bandera!=true){
				intentos++;
				if(alg.hacerLasVegas(reinas)==true){
					t=alg.getTableros();
					t.mostrarTableros();
					bandera=true;
				}else{
					cout<<"No encuentra solucion"<<endl;
				}

			}
			cout<<"Intentos = "<<intentos<<endl;
		}
	}

	cout<<"Desea buscar las n soluciones del algoritmo Las Vegas? (S/n): ";
	cin>>opcion;

	if(opcion=='S' || opcion=='s'){
		cout<<"*** SOLUCION N-VEGAS ***"<<endl;
		
		if(contador==0){
			cout<<"No tiene solucion"<<endl;
		}else{
			t.eraseTableros();
			intentos=0;
			while(contador!=t.getNTablero()){
				cout<<contador<< " = " <<t.getNTablero()<<endl;
				intentos++;
				if(alg.hacerLasVegas(reinas)==true){
					t.addTablero(alg.getTableros());	
				}
				//t.mostrarTableros();

			}
			t.mostrarTableros();
			cout<<"Intentos = "<<intentos<<endl;
		}
	}

	return 0;
}