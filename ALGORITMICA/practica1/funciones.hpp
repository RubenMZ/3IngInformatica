#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>
#include <string>
#include <stdint.h> // Para usar uint64_t
using namespace std;

void rellenarVector(vector<int> &v, const int &n);
double calculaMedia(vector<uint64_t> &tiempos);
bool estaOrdenado(const vector <int> v);

void guardarTiempos(const vector<double> n, const vector<double> &tNS, const vector<double> &tNSE, const vector<double> &tS, const vector <double> &tSE, string fichero);

#endif