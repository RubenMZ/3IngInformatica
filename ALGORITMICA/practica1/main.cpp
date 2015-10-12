/*!
    @author Ruben
    @file main.cpp
    @brief Main que procesa una serie de vectores y estima los tiempos para los algoritmos InsercionBinaria y Shell
*/


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

    //VARIABLES

    int minimo, maximo, incremento, repeticiones;//Variables para la ejecucion de los algoritmos, introducidas por comandos
    vector<uint64_t> tiemposInsercion, tiemposShell;//Vectores de tiempos
    vector<double> tiemposMediosInsercion, tiemposMediosShell;
    vector<double> tiemposEstimadosInsercion, tiemposEstimadosShell;
    vector<double> elementos;
    vector<int> vector;

    //Instancias de las diferentes clases para el tiempo, los algoritmos y el ajuste del tiempo
    Clock c;
    InsercionBinaria insercionBinaria;
    Shell shell;
    Ajuste ajuste1;

    double a0Ins, a1Ins, a2Ins, r2Ins;//Coeficientes de Insercion
    double a0She, a1She, r2She;//Coeficientes de Shell

    long respuesta=1;//Variable para calcular los dias de los algotirmos segun n del usuario

    int k=0;//Variable para recorrer el vector de elementos.


    //Asignacion de los comandos a las variables de ejecucion
    minimo=atoi(argv[1]);
    maximo=atoi(argv[2]);
    incremento=atoi(argv[3]);
    repeticiones=atoi(argv[4]);
    srand(time(NULL));

    if (minimo<=0 || maximo<=0 || incremento<=0 || repeticiones<=0 || minimo>maximo || incremento>maximo)
    {
        cout<<"ERROR. Los valores <minimo><maximo><incremento><repeticiones> estan mal."<<endl;
        exit(-1);
    }

    for (int i = minimo; i <= maximo; i+=incremento)
    {
            tiemposInsercion.clear();
            tiemposShell.clear();

            elementos.push_back(i);

        for (int j = 1; j <= repeticiones; ++j)
        {
            //Creamos un vector de numeros aleatorios [0,9999]
            vector.clear();
            rellenarVector(vector, i);            
            //Asignamos el vector creado a cada algoritmo
            insercionBinaria.setVector(vector);
            insercionBinaria.setElementos(i);
            shell.setVector(vector);
            shell.setElementos(i);

            //Medimos el tiempo para Insercion Binaria
            c.start();
            insercionBinaria.ordenar();
            c.stop();
            vector= insercionBinaria.getVector();
            //Comprobamos si esta ordenado
            if (estaOrdenado(vector)!=true){//Comprueba si esta ordenado
                printf("No esta ordenado correctamente por insercionBinaria.\n");
            }

            tiemposInsercion.push_back(c.elapsed());

            //Medimos el tiempo para Shell
            c.start();
            shell.ordenar();
            c.stop();
            vector= shell.getVector();
            //Comprobamos si esta ordenado
            if (estaOrdenado(vector)!=true){
                printf("No esta ordenado correctamente por shell.\n");
            }
            tiemposShell.push_back(c.elapsed());

        }//for repeticiones

        //Insertamos en el vector de tiemposMedios, las medias de los tiempos recogidos
        tiemposMediosInsercion.push_back(calculaMedia(tiemposInsercion));
        tiemposMediosShell.push_back(calculaMedia(tiemposShell));
        //Mostramos cada tiempoMedio
        cout<<"\t Tiempo medio InsercionBinaria-> "<<elementos[k]<<" elementos = "<<tiemposMediosInsercion[k]<<endl;
        cout<<"\t Tiempo medio Shell-> "<<elementos[k]<<" elementos = "<<tiemposMediosShell[k]<<endl;
        k++;//Incrementamos la variable para el vector de elementos y tiemposMedios

    }//for incremento

        //Calculamos el Ajuste para ambos algoritmos en funcion de los elementos y los tiemposMedios
        //Obtenemos los coeficientes
        ajuste1.calcularAjustePolinomico(elementos, tiemposMediosInsercion, a0Ins, a1Ins, a2Ins, r2Ins);
        ajuste1.calcularAjusteLineal(elementos, tiemposMediosShell, a0She, a1She, r2She);

        //Calculamos los tiemposEstimados para cada algoritmo en funcion de su ajuste
        ajuste1.calcularTiemposEstimadosLineales(elementos, a0She, a1She, tiemposEstimadosShell);
        ajuste1.calcularTiemposEstimadosCuadraticos(elementos, a0Ins, a1Ins, a2Ins, tiemposEstimadosInsercion);

        for (int i = 0; i < elementos.size(); ++i)
        {
            cout<<"\t Tiempo estimado InsercionBinaria-> "<<elementos[i]<<" elementos = "<<tiemposEstimadosInsercion[i]<<endl;
            cout<<"\t Tiempo estimado Shell-> "<<elementos[i]<<" elementos = "<<tiemposEstimadosShell[i]<<endl;
        }
        //Guardamos los tiemposMedios y Estimados en un fichero para la posterior grafica
        guardarTiempos(elementos, tiemposMediosInsercion, tiemposEstimadosInsercion, tiemposMediosShell, tiemposEstimadosShell, "Datos.txt");

        cout<<"Coef. Determinacion R2 (InsercionBinaria) = "<<r2Ins<<endl;
        cout<<"t(n) = "<<a2Ins<<"*n² + "<<a1Ins<<"*n + "<<a0Ins<<endl;

        cout<<"Coef. Determinacion R2 (Shell) = "<<r2She<<endl;
        cout<<"t(n) = "<<a1She<<"*n*ln(n) + "<<a0She<<endl;

        //Pedimos al usuario valores n para calcular el tiempo de ordenacion en dias, 0 para salir
        while(respuesta!=0){

            cout<<"Introduce un numero de elementos (0-salir): ";
            cin>>respuesta;

            if(respuesta!=0){
                cout<<"Repuesta= "<<respuesta<<endl;
                cout<<"Aproximacion por Insercion = "<< ajuste1.calcularDias(respuesta, a0Ins, a1Ins, a2Ins,0)<<" dias"<<endl;
                cout<<"Aproximacion por Shell = "<<ajuste1.calcularDias(respuesta, a0She, a1She, 0,1)<<" dias"<<endl;   
            }
        }

    return 0;
}