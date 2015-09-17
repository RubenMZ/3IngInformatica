#include "metodoInsercionBinaria.hpp"
#include <vector>


using namespace std;

void InsercionBinaria::ordenar()
{
    int j,aux,izq,der,m;
    vector<int> auxV= getVector();

    for(int i=0;i<getElementos();i++)
    {
               	aux = auxV[i];
                izq=0;
                der=i-1;
                while(izq<=der)
                {
		            m=((izq+der)/2);
		            if (aux<auxV[m])
		                der=m-1;
		            else
		                izq=m+1;              
                }

                j=i-1;

                while(j>=izq)
                {
            		auxV[j+1]=auxV[j];
                	j=j-1;
                }
                auxV[izq]=aux;
    }

}


