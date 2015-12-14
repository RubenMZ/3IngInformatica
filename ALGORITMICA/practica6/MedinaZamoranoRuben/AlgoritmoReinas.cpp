#include "AlgoritmoReinas.hpp"

	bool AlgoritmoReinas::hacerAlgoritmo(const int &n){
		setContador(0);
		setPosicion(0,-1);
		int k=0;
		int bandera=false;
		Tablero aux;
		aux.setOrdenTablero(n);

		while(k>=0){
			setPosicion(k, getPosicion(k)+1);
			while(getPosicion(k)<n && Lugar(k, getPosiciones())==false ){
				setPosicion(k, getPosicion(k)+1);
			}
			if(getPosicion(k)<n){
				if(k==(n-1)){
					aux.addTablero(getPosiciones());
					bandera=true;
					setContador(getContador()+1);
				}else{
					k++;
					setPosicion(k,-1);
				}
			}else{
				k--;
			}
		}//while

		setTableros(aux);
		return bandera;
	}

	bool AlgoritmoReinas::Lugar(const int &k, const vector<int> &x){
		for (int i = 0; i < k; ++i)
		{
			if(x[i]==x[k] || abs(x[i]-x[k])==abs(i-k) )
				return false;
		}
		return true;
	}

	/*void AlgoritmoReinas::muestraSolucion(vector<int> x, const int &n){
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if(x[i]==j)
					cout<<" |R| ";
				else
					cout<<" | | ";
			}
			cout <<endl;
		}


	}*/


	bool AlgoritmoReinas::hacerLasVegas(const int &n){
		int ok[n];
		setContador(0);
		Tablero aux;
		aux.setOrdenTablero(n);
		
		
		for (int i = 0; i < n; ++i)
		{
			setPosicion(i,0);
		}
		for (int k = 0; k < n; ++k)
		{
			setContador(0);
			for (int j = 0; j < n; ++j)
			{
				setPosicion(k, j);
				if(Lugar(k, getPosiciones())==true ){
					setContador(getContador()+1);
					ok[getContador()]=j;
				}
			}
			if(getContador()==0)
				break;
			int columna = ok[rand()%getContador()+1];
			setPosicion(k, columna);
		}//for

		if(getContador()==0){
			return false;
		}else{
			aux.addTablero(getPosiciones());
			setTableros(aux);
			return true;
		}
	}