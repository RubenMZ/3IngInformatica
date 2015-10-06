#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdint.h> // Para usar uint64_t
#include "Clock.hpp"
#include "metodoInsercionBinaria.hpp"
#include "funciones.hpp"
#include "metodoShell.hpp"
#include "ajuste.hpp"

//nice -n -20 ./main

using namespace std;

int main (int argc, char ** argv){

    if (argc!=5){
        cout<<"ERROR en argumentos, <elementos min><elementos max><incremento><repeticiones>"<<endl;
        exit(-1);
    }

    int minimo, maximo, incremento, repeticiones;
    vector<uint64_t> tiemposInsercion, tiemposShell;
    vector<double> tiemposMediosInsercion, tiemposMediosShell;
    vector<double> tiemposEstimadosInsercion, tiemposEstimadosShell;
    vector<double> elementos;
    vector<int> vector;
    Clock c;
    InsercionBinaria insercionBinaria;
    Shell shell;
    Ajuste ajuste1;

    double a0Ins, a1Ins, a2Ins, r2Ins;
    double a0She, a1She, r2She;

    long respuesta=1;

    int k=0;

    minimo=atoi(argv[1]);
    maximo=atoi(argv[2]);
    incremento=atoi(argv[3]);
    repeticiones=atoi(argv[4]);
    srand(time(NULL));

    for (int i = minimo; i <= maximo; i+=incremento)
    {
            tiemposInsercion.clear();
            tiemposShell.clear();

            elementos.push_back(i);

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

            if (estaOrdenado(vector)!=true){
                printf("No esta ordenado correctamente por insercionBinaria.\n");
            }

            tiemposInsercion.push_back(c.elapsed());

            c.start();
            shell.ordenar();
            c.stop();
            vector= shell.getVector();

            if (estaOrdenado(vector)!=true){
                printf("No esta ordenado correctamente por shell.\n");
            }
            tiemposShell.push_back(c.elapsed());

        }
        tiemposMediosInsercion.push_back(calculaMedia(tiemposInsercion));
        tiemposMediosShell.push_back(calculaMedia(tiemposShell));
        cout<<"\t Tiempo medio InsercionBinaria-> "<<elementos[k]<<" elementos = "<<tiemposMediosInsercion[k]<<endl;
        cout<<"\t Tiempo medio Shell-> "<<elementos[k]<<" elementos = "<<tiemposMediosShell[k]<<endl;
        k++;
    }

        ajuste1.calcularAjustePolinomico(elementos, tiemposMediosInsercion, a0Ins, a1Ins, a2Ins, r2Ins);
        ajuste1.calcularAjusteLineal(elementos, tiemposMediosShell, a0She, a1She, r2She);

        ajuste1.calcularTiemposEstimadosLineales(elementos, a0She, a1She, tiemposEstimadosShell);
        ajuste1.calcularTiemposEstimadosCuadraticos(elementos, a0Ins, a1Ins, a2Ins, tiemposEstimadosInsercion);

        for (int i = 0; i < elementos.size(); ++i)
        {
            cout<<"\t Tiempo estimado InsercionBinaria-> "<<elementos[i]<<" elementos = "<<tiemposEstimadosInsercion[i]<<endl;
            cout<<"\t Tiempo estimado Shell-> "<<elementos[i]<<" elementos = "<<tiemposEstimadosShell[i]<<endl;
        }

        cout<<"Coef. Determinacion R2 (InsercionBinaria) = "<<r2Ins<<endl;
        cout<<"t(n) = "<<a2Ins<<"*n² + "<<a1Ins<<"*n + "<<a0Ins<<endl;

        cout<<"Coef. Determinacion R2 (Shell) = "<<r2She<<endl;
        cout<<"t(n) = "<<a1She<<"*n*ln(n) + "<<a0She<<endl;

        while(respuesta!=0){

            cout<<"Introduce un numero de elementos: ";
            cin>>respuesta;

            if(respuesta!=0){
                cout<<"Repuesta= "<<respuesta<<endl;
                cout<<"Aproximacion por Insercion = "<< ajuste1.calcularDias(respuesta, a0Ins, a1Ins, a2Ins,0)<<" dias"<<endl;
                cout<<"Aproximacion por Shell = "<<ajuste1.calcularDias(respuesta, a0She, a1She, 0,1)<<" dias"<<endl;   
            }
        }

        guardarTiempos(elementos, tiemposMediosInsercion, tiemposEstimadosInsercion, tiemposMediosShell, tiemposEstimadosShell, "Datos2.txt");

    return 0;
}