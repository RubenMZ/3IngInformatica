#ifndef DETERMINANTEITERATIVO_HPP
#define DETERMINANTEITERATIVO_HPP

#include "matriz.hpp"


template <class T>
class DeterminanteIterativo{

	public:

		T determinanteIterativo(const Matriz <T> &mat) {

			// Algoritmo para la eliminación simple de Gauss
		    Matriz <T> mAux = mat;
	

		  	int NoCero,A,NoReg = 0,Perm=0;/*permutaciones*/
		  	double Pivote,V1,Det=1.0;
		  	for(int i=1 ; i <= mAux.filas() ; i++){
		    	NoCero=0;A=i;
		      
		      	while((NoCero==0)&&(A<=mAux.filas())){
		        	if((mAux.elemento(A,i)>0.0000001)||((mAux.elemento(A,i)<-0.0000001))){  // Si m[A][i]!=0
		          		NoCero=1;
		       	 	}
		        	else 
		        		A++;
		      	}
		      	if (A>mAux.filas()) 
		      		NoReg=1;

		      	if (A!=i) 
		      		Perm++;

		      	if (A>mAux.filas()){
		        	printf ("Esta matriz no tiene determinante.");
		        	return 0;
		      	} 

		      	Pivote=mAux.elemento(A,i);
		      
		      	for(int j=1 ; j <= mAux.filas() ; j++){
		        	V1 = mAux.elemento(A,j);
		        	mAux.elemento(A, j, mAux.elemento(i, j));
		        	mAux.elemento(i, j, V1);
		      	}
		      	for(int k = i+1 ; k <= mAux.filas() ; k++){
		      		V1 = mAux.elemento(k,i);
		      		for(int j = i ; j <= mAux.filas() ; j++){
		          		mAux.elemento(k,j, mAux.elemento(k,j)-((V1/Pivote)*mAux.elemento(i,j)));
		        	}
		     	}
		  	}
		  	for(int k = 1 ; k <= mAux.filas() ; k++) Det=Det*mAux.elemento(k,k);
		  		
		  	A=Perm;
  			if ((A%2)==1) Det=-Det; /*Caso de permutaciones impares*/
  			if (NoReg==1) Det=0;
  				return Det;
		}
		inline DeterminanteIterativo(){};
		inline ~DeterminanteIterativo(){};
};

#endif