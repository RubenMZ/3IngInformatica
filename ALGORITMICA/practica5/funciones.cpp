
#include "funciones.hpp"

	void imprimeSolucion(const vector<int> &v){
		unsigned int i=0;		
		int j;
		int aux;

		while(i<v.size()){
			aux=v[i];
			j=0;			
			while(aux==v[i]){
				j++;
				i++;
			}
			if(aux/500 ==0)
				cout<<j<<" moneda(s) de valor "<<aux<<" cents"<<endl;
			else
				cout<<j<<" billete(s) de valor "<<aux<<" cents"<<endl;
		}
	}

	void imprimeSolucionDinamica(int** m, const int &fil, const int &col, const vector<int> &monedas){
		int i=fil-1, j=col;
		int contador=0;
		int moneda=0;

		while(j!=0 && i>=0){
			if(i==0){
				if(m[i][j-monedas[i]]+1==m[i][j]){
					moneda=monedas[i];
					contador++;
					j=j-monedas[i];
				}else{
					j--;
				}
			}else
				if(m[i][j]==m[i-1][j]){
					i--;
					if(contador!=0){
						if(moneda/500 ==0)
							cout<<contador<<" moneda(s) de valor "<<moneda<<" cents"<<endl;
						else
							cout<<contador<<" billete(s) de valor "<<moneda<<" cents"<<endl;
						contador=0;
					}
				}else{
					if(m[i][j-monedas[i]]+1==m[i][j]){
						moneda=monedas[i];
						j=j-monedas[i];
						contador++;
					}else{
						j--;
					}
				}
		}
		if(contador!=0){
			cout<<contador<<" moneda(s) de valor "<<moneda<<" cents"<<endl;
		}
	}	

		void mostrarVector(const vector<int> &v){
			//Mostramos el vector
			for(unsigned int i=0; i<v.size(); i++){
				cout << v[i] << " ";
			}
			cout << endl;
		}


		ifstream& operator>>(ifstream& os, vector<int> &v){
			string cad;			
			while(getline(os,cad)){
				v.push_back(atoi(cad.c_str()));
			}
			return os;
		}

		bool comp(int p1, int p2){
			return p1>p2;
		}

		bool comp2(int p1, int p2){
			return p1<p2;
		}

		int minimo(const int &a, const int &b){
			if(a<b)
				return a;
			else
				return b;
		}

