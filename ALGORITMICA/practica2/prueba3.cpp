#include "matriz.hpp"

template <class T>
T determinanteIterativo(Matriz <T> &mat, const int &n) {
  	    	Matriz <T> mAux = mat;
	
  	int NoCero,A,NoReg = 0,Perm=0;/*permutaciones*/
  	double Pivote,V1,Det=1.0;
  	for(int i=1 ; i <= mAux.filas() ; i++){
    	NoCero=0;A=i;
      
      	while((NoCero==0)&&(A<=mAux.filas())){
        	if(mAux.elemento(A,i)!=0){  // Si m[A][i]!=0
          		NoCero=1;
       	 	}
        	else A++;
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

    mAux.verMatriz();

  	for(int k = 1 ; k <= mAux.filas() ; k++) 
      Det=Det*mAux.elemento(k,k);
  		
  	A=Perm;
  	if ((A%2)==1) Det=-Det; /*Caso de permutaciones impares*/
  	if (NoReg==1) Det=0;
  	return Det;

    }


  int main(int argc, char const *argv[])
  {
    Matriz <double> mat(5,5);

    mat.elemento(1,1, 7);
    mat.elemento(1,2, 5);
    mat.elemento(1,3, 7);
    mat.elemento(1,4, 5);
    mat.elemento(1,5, 4);
    mat.elemento(2,1, 3);
    mat.elemento(2,2, 5);
    mat.elemento(2,3, 3);
    mat.elemento(2,4, 6);
    mat.elemento(2,5, 3);
    mat.elemento(3,1, 6);
    mat.elemento(3,2, 7);
    mat.elemento(3,3, 6);
    mat.elemento(3,4, 7);
    mat.elemento(3,5, 6);
    mat.elemento(4,1, 8);
    mat.elemento(4,2, 8);
    mat.elemento(4,3, 4);
    mat.elemento(4,4, 4);
    mat.elemento(4,5, 5);
    mat.elemento(5,1, 7);
    mat.elemento(5,2, 6);
    mat.elemento(5,3, 4);
    mat.elemento(5,4, 7);
    mat.elemento(5,5, 6);

    mat.verMatriz();

    double det= determinanteIterativo(mat, 5);

    cout <<det<<endl;

    return 0;
  }