#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>
#include <algorithm> 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Moneda.hpp"


using namespace std;

void imprimeSolucion(const vector<int> &v, const vector<Moneda> &m);
void imprimeSolucionDinamica(int **m, const int &fil, const int &col, const vector<Moneda> &mon);
void mostrarVector(const vector<int> &v);
ifstream& operator>>(ifstream& os, vector<Moneda> &v);
bool comp(Moneda p1, Moneda p2);
bool comp2(Moneda p1, Moneda p2);
int minimo(const int &a, const int &b);
void guardarTiempos(const vector<double> &cambio, const vector<double> &tiempos1, const vector<double> &tiempos2, const string &fichero);
double calculaMedia(const vector<double> &v);

#endif
