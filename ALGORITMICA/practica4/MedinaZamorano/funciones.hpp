#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <vector>
#include <algorithm> 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

void imprimeSolucion(const vector<int> &v);
void mostrarVector(const vector<int> &v);
ifstream& operator>>(ifstream& os, vector<int> &v);
bool comp(int p1, int p2);



#endif
