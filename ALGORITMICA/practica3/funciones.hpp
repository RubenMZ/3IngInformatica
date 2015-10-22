/*!
	@author Ruben
	@file funciones.hpp
	@brief Declaracion de las funciones basicas para el procesado de los datos
*/


#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>
#include <string>
#include <stdint.h> // Para usar uint64_t
#include <iostream>
#include <cstdlib>

using namespace std;

/*!
	@fn void rellenarVector(vector<int> &v, const int &n);
	@brief Rellena el vector de n numeros random [0,9999]
*/
template <class T>
void rellenarVector(vector<T> &v, const int &n){

	for (int i = 0; i < n; ++i)
	{
		v.push_back(rand()%10000);
	}
}
/*!
	@fn double calculaMedia(vector<uint64_t> &tiempos);
	@brief Calcula la media de los elementos del vector tiempos
*/
template <class T>
double calculaMedia(vector<T> &tiempos){

	double suma=0;
	int n=tiempos.size();

	for (int i = 0; i < n; ++i)
	{
		suma+=(double)tiempos[i];
	}
	return suma/n;
}
/*!
	@fn bool estaOrdenado(const vector <int> v);
	@brief Comprueba si el vector esta ordenado
*/
template <class T>
bool estaOrdenado(const vector <T> &v){

	for (int i = 1; i < v.size(); ++i)
	{
			if(v[i]>=v[i-1])
				return false;
	}
	return true;
}

template <class T>
T Minimo(T min1, T min2){
	if(min1<min2){
		return min1;
	}else{
		return min2;
	}
}

template <class T>
T Maximo(T max1, T max2){
	if(max1>max2){
		return max1;
	}else{
		return max2;
	}
}


template <class T>
void minimoMaximo(vector<T> &v, int n, int i, int j, int &max, int &min, int &llamadas){
	int mitad;
	T maximo1, minimo1, maximo2, minimo2;
	if (estaOrdenado(v)==true)
	{
		max=v[j];
		min=v[i];
	}else{
		if(i==j){
			max = v[i];
			min = v[i];
		}else{
			if(i ==(j-1)){
				if(v[i]<v[j]){
					max = v[j];
					min = v[i];
				}else{
					max = v[i];
					min = v[j];
				}

			}else{
				mitad = (i+j)/2;
				llamadas++;
				minimoMaximo(v,n,i,mitad,maximo1,minimo1, llamadas);
				llamadas++;
				minimoMaximo(v,n,mitad+1,j,maximo2, minimo2, llamadas);
				//muestraVector(v);
				max = Maximo(maximo1, maximo2);
				min = Minimo(minimo1, minimo2);

			}
		}
	}
}

template <class T>
void mostrarVector(const vector<T> &v){
	//Mostramos el vector
	for(int i=0; i<v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}

#endif