#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdint.h> // Para usar uint64_t
#include "Clock.hpp"
#include "metodoInsercionBinaria.hpp"
#include "funciones.hpp"
#include "metodoShell.hpp"

using namespace std;

int main (int argc, char ** argv){

    if (argc!=5){
        cout<<"ERROR en argumentos, <elementos min><elementos max><incremento><repeticiones>"<<endl;
        exit(-1);
    }

    int minimo, maximo, incremento, repeticiones;
    vector<uint64_t> tiempos1, tiempos2;
    vector<double> tiemposMedios1, tiemposMedios2;
    vector<int> vector;
    Clock c;
    InsercionBinaria insercionBinaria;
    Shell shell;

    minimo=atoi(argv[1]);
    maximo=atoi(argv[2]);
    incremento=atoi(argv[3]);
    repeticiones=atoi(argv[4]);
    srand(time(NULL));

    for (int i = minimo; i <= maximo; i+=incremento)
    {
            tiempos1.clear();
            tiempos2.clear();

        for (int j = 1; j <= repeticiones; ++j)
        {
            vector.clear();
            rellenarVector(vector, i);

            insercionBinaria.setVector(vector);
            insercionBinaria.setElementos(i);
            shell.setVector(vector);
            shell.setElementos(i);

            c.start();
            insercionBinaria.ordenar();
            c.stop();
            vector= insercionBinaria.getVector();

            if (estaOrdenado(vector)==true){
                printf("Esta ordenado correctamente por insercionBinaria.\n");
            }
            cout<<"Ha tardado... "<<c.elapsed()<<" microsegundos"<<endl;
            tiempos1.push_back(c.elapsed());

            c.start();
            cout<<"hola";
            shell.ordenar();
            cout<<"adios";
            c.stop();
            vector= shell.getVector();

            if (estaOrdenado(vector)==true){
                printf("Esta ordenado correctamente por shell.\n");
            }
            cout<<"Ha tardado... "<<c.elapsed()<<" microsegundos"<<endl;
            tiempos2.push_back(c.elapsed());

        }
        tiemposMedios1.push_back(calculaMedia(tiempos1));
        cout<<"Media "<<calculaMedia(tiempos1)<<endl;
        tiemposMedios2.push_back(calculaMedia(tiempos2));
        cout<<"Media "<<calculaMedia(tiempos2)<<endl;
    }

        for (int j = 0; j <= (maximo-minimo)/incremento; j++)
        {
            cout<<"\t Tiempo "<<j<<" = "<<tiemposMedios1[j]<<endl;
        }

        for (int i = 0; i <=(maximo-minimo)/incremento; i++)
        {
            cout<<"\t Tiempo "<<i<<" = "<<tiemposMedios2[i]<<endl;
        }


    return 0;
}