#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdint.h> // Para usar uint64_t
#include "Clock.hpp"
#include "metodoInsercionBinaria.hpp"
#include "funciones.hpp"

using namespace std;

int main (int argc, char ** argv){

    if (argc!=5){
        cout<<"ERROR en argumentos, <elementos min><elementos max><incremento><repeticiones>"<<endl;
        exit(-1);
    }

    int minimo, maximo, incremento, repeticiones;
    vector<uint64_t> tiempos1, tiempos2;
    vector<int> vector;
    Clock c;
    InsercionBinaria algoritmo;

    minimo=atoi(argv[1]);
    maximo=atoi(argv[2]);
    incremento=atoi(argv[3]);
    repeticiones=atoi(argv[4]);
    srand(time(NULL));

    for (int i = minimo; i <= maximo; i+=incremento)
    {
        for (int j = 1; j <= repeticiones; ++j)
        {
            rellenarVector(vector, i);
            algoritmo.setVector(vector);
            algoritmo.setElementos(i);
            c.start();
            algoritmo.ordenar();
            c.stop();
            cout<<"Ha tardado... "<<c.elapsed()<<" microsegundos"<<endl;
            cout<<minimo<<endl<<maximo<<endl<<incremento<<endl<<repeticiones<<endl;
            cout<<i<<endl<<j<<endl;
            vector.clear();
        }

    }
    cout<<"Aqui"<<endl;
    vector= algoritmo.getVector();

    for (int i = 0; i < maximo; ++i)
    {
        cout<<vector[i]<<endl;
    }

    return 0;
}