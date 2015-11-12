
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

