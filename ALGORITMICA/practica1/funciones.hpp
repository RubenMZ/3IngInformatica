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
using namespace std;

/*!
	@fn void rellenarVector(vector<int> &v, const int &n);
	@brief Rellena el vector de n numeros random [0,9999]
*/

void rellenarVector(vector<int> &v, const int &n);
/*!
	@fn double calculaMedia(vector<uint64_t> &tiempos);
	@brief Calcula la media de los elementos del vector tiempos
*/
double calculaMedia(vector<uint64_t> &tiempos);

/*!
	@fn bool estaOrdenado(const vector <int> v);
	@brief Comprueba si el vector esta ordenado
*/
bool estaOrdenado(const vector <int> v);
/*!
	@fn void guardarTiempos(const vector<double> n, const vector<double> &tNS, const vector<double> &tNSE, const vector<double> &tS, const vector <double> &tSE, string fichero);
	@brief Guarda los tiempos de los vectores en un fichero
*/
void guardarTiempos(const vector<double> n, const vector<double> &tNS, const vector<double> &tNSE, const vector<double> &tS, const vector <double> &tSE, string fichero);

#endif