/*!
    @author Ruben
    @file main.cpp
    @brief Main que procesa una serie de vectores y estima los tiempos para los algoritmos iterativo y recursivo
*/



#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdint.h>
 // Para usar uint64_t
#include "Clock.hpp"
#include "funciones.hpp"
#include "ajuste.hpp"
#include "matriz.hpp"
#include "determinanteRecursivo.hpp"
#include "determinanteIterativo.hpp"

//nice -n -20 ./main

using namespace std;

int main (int argc, char ** argv){

    if (argc!=6){
        cout<<"ERROR en argumentos, <orden min><orden max><repeticiones><num min><num max>"<<endl;
        exit(-1);
    }

    //VARIABLES

    int minimo, maximo, incremento, repeticiones, a,b;//Variables para la ejecucion de los algoritmos, introducidas por comandos
    vector<uint64_t> tiemposIterativo, tiemposRecursivo;//Vectores de tiempos
    vector<double> tiemposMediosIterativo, tiemposMediosRecursivo;
    vector<double> tiemposEstimadosIterativo, tiemposEstimadosRecursivo;
    vector<double> orden, ordenFactorial;

    DeterminanteRecursivo<double> recur;
    DeterminanteIterativo<double> itera;
    
    double det;

    //Instancias de las diferentes clases para el tiempo, los algoritmos y el ajuste del tiempo
    Clock c;
    Ajuste ajuste1;

    double a0Iter, a1Iter, a2Iter, a3Iter, r2Iter;//Coeficientes de iterativo
    double a0Recur, a1Recur, r2Recur;//Coeficientes de recursivo

    int k=0;//Variable para recorrer el vector de orden.


    //Asignacion de los comandos a las variables de ejecucion
    minimo=atoi(argv[1]);
    maximo=atoi(argv[2]);
    repeticiones=atoi(argv[3]);
    a=atoi(argv[4]);
    b=atoi(argv[5]);



    srand(time(NULL));



    if (minimo<=0 || maximo<=0 || repeticiones<=0 || minimo>maximo || b<a || a<=0 || b<=0)
    {
        cout<<"ERROR. Los valores <orden minimo><orden maximo><repeticiones><num min><num max> estan mal."<<endl;
        exit(-1);
    }

    for (int i = minimo; i <= maximo; ++i)
    {
            tiemposIterativo.clear();
            tiemposRecursivo.clear();
            orden.push_back(i);

        for (int j = 1; j <= repeticiones; ++j)
        {
            Matriz<double> matriz(i,i);
            rellenaMatriz(matriz, i,i, a, b);
            Matriz<double>matriz2(matriz);
            matriz.verMatriz();       

            //Medimos el tiempo para iterativo
            c.start();
            det=itera.determinanteIterativo(matriz, i);
            c.stop();
            cout << " Deteterminante por Iterativo Gauss "<<det<<endl;
            tiemposIterativo.push_back(c.elapsed());
            
            //Medimos el tiempo para recursivo
            c.start();
            det=recur.determinanteRecursivo(matriz2, i);
            c.stop();
            cout << " Determinante por Recursivo "<<det<<endl;
            tiemposRecursivo.push_back(c.elapsed());

        }//for repeticiones

        //Insertamos en el vector de tiemposMedios, las medias de los tiempos recogidos
        tiemposMediosIterativo.push_back(calculaMedia(tiemposIterativo));
        tiemposMediosRecursivo.push_back(calculaMedia(tiemposRecursivo));
        //Mostramos cada tiempoMedio
        cout<<"\t Tiempo medio iterativo-> "<<orden[k]<<" orden = "<<tiemposMediosIterativo[k]<<" microsegundos"<<endl;
        cout<<"\t Tiempo medio recursivo-> "<<orden[k]<<" orden = "<<tiemposMediosRecursivo[k]<<" microsegundos"<<endl;
        k++;//Incrementamos la variable para el vector de orden y tiemposMedios

    }//for incremento

        //Calculamos el Ajuste para ambos algoritmos en funcion de los orden y los tiemposMedios
        //Obtenemos los coeficientes
        for (int i = 0; i < orden.size(); ++i)
        {  
            ordenFactorial.push_back( ajuste1.factorial(orden[i]));
        }

        ajuste1.calcularAjustePolinomico(orden, tiemposMediosIterativo, a0Iter, a1Iter, a2Iter, a3Iter , r2Iter);
        ajuste1.calcularAjusteLineal(ordenFactorial, tiemposMediosRecursivo, a0Recur, a1Recur, r2Recur);

  
        //Calculamos los tiemposEstimados para cada algoritmo en funcion de su ajuste
        ajuste1.calcularTiemposEstimadosLineales(ordenFactorial, a0Recur, a1Recur, tiemposEstimadosRecursivo);
        ajuste1.calcularTiemposEstimadosCubicos(orden, a0Iter, a1Iter, a2Iter, a3Iter,tiemposEstimadosIterativo);

        

        for (int i = 0; i < orden.size(); ++i)
        {
            cout<<"\t Tiempo estimado iterativo-> "<<orden[i]<<" orden = "<<tiemposEstimadosIterativo[i]<<endl;
            cout<<"\t Tiempo estimado recursivo-> "<<orden[i]<<" orden = "<<tiemposEstimadosRecursivo[i]<<endl;
        }
        //Guardamos los tiemposMedios y Estimados en un fichero para la posterior grafica
        guardarTiempos(orden, tiemposMediosIterativo, tiemposEstimadosIterativo, tiemposMediosRecursivo, tiemposEstimadosRecursivo, "Datos.txt");

        cout<<"Coef. Determinacion R2 (iterativo) = "<<r2Iter<<endl;
        cout<<"t(n) = "<<a3Iter<<"*n³ + "<<a2Iter<<"*n² + "<<a1Iter<<"*n + "<<a0Iter<<endl;

        cout<<"Coef. Determinacion R2 (recursivo) = "<<r2Recur<<endl;
        cout<<"t(n) = "<<a1Recur<<"*n! + "<<a0Recur<<endl;




    return 0;
}