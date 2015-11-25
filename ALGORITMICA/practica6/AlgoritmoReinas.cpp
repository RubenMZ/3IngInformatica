#include "AlgoritmoReinas.hpp"

	void AlgoritmoReinas::hacerAlgoritmo(const int &n){
		posiciones_=(int *)malloc(n * sizeof(int));
		setPosicion(0,-1);
		int k=0;
		while(k>=0){
			setPosicion(k, getPosicion(k)+1);
			while(getPosicion(k)<n && Lugar(k, getPosiciones())==false ){
				setPosicion(k, getPosicion(k)+1);
			}
			if(getPosicion(k)<n){
				if(k==(n-1)){
					cout<<"***** SOLUCION *****"<<endl;
					muestraSolucion(getPosiciones(),n);
				}else{
					k++;
					setPosicion(k,-1);
				}
			}else{
				k--;
			}
		}//while
		free(posiciones_);
	}

	bool AlgoritmoReinas::Lugar(const int &k, int * x){
		for (int i = 0; i < k; ++i)
		{
			if(x[i]==x[k] || abs(x[i]-x[k])==abs(i-k) )
				return false;
		}
		return true;
	}

	void AlgoritmoReinas::muestraSolucion(int * x, const int &n){
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if(x[i]==j)
					cout<<" [R] ";
				else
					cout<<" [ ] ";
			}
			cout <<endl;
		}
	}