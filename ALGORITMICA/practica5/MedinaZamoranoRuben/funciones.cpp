
#include "funciones.hpp"

	void imprimeSolucion(const vector<int> &v, const vector<Moneda> &m){
		vector<Moneda> monedas = m;

		sort(monedas.begin(), monedas.end(), comp);
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			if(v[i]!=0){
				if(monedas[i].getEtiqueta() ==0)
					cout<<v[i]<<" moneda(s) de valor "<<monedas[i].getValor()<<" cents"<<endl;
				else
					cout<<v[i]<<" billete(s) de valor "<<monedas[i].getValor()<<" cents"<<endl;
			}
		}
	}

	void imprimeSolucionDinamica(int** m, const int &fil, const int &col, const vector<Moneda> &mon){
		int i=fil-1, j=col;
		int contador=0;
		Moneda moneda;
		vector<Moneda> monedas = mon;

		moneda.setValor(0);
		moneda.setEtiqueta(0);

		sort(monedas.begin(), monedas.end(), comp2);
		while(j!=0 && i>=0){
			if(i==0){
				if(m[i][j-monedas[i].getValor()]+1==m[i][j]){
					moneda=monedas[i];
					contador++;
					j=j-monedas[i].getValor();
				}else{
					j--;
				}
			}else
				if(m[i][j]==m[i-1][j]){
					i--;
					if(contador!=0){
						if(moneda.getEtiqueta() ==0)
							cout<<contador<<" moneda(s) de valor "<<moneda.getValor()<<" cents"<<endl;
						else
							cout<<contador<<" billete(s) de valor "<<moneda.getValor()<<" cents"<<endl;
						contador=0;
					}
				}else{
					if(m[i][j-monedas[i].getValor()]+1==m[i][j]){
						moneda=monedas[i];
						j=j-monedas[i].getValor();
						contador++;
					}else{
						j--;
					}
				}
		}
		if(contador!=0){
			if(moneda.getEtiqueta() ==0)
				cout<<contador<<" moneda(s) de valor "<<moneda.getValor()<<" cents"<<endl;
			else
				cout<<contador<<" billete(s) de valor "<<moneda.getValor()<<" cents"<<endl;
		}
	}	

		void mostrarVector(const vector<int> &v){
			//Mostramos el vector
			for(unsigned int i=0; i<v.size(); i++){
				cout << v[i] << " ";
			}
			cout << endl;
		}


		ifstream& operator>>(ifstream& os, vector<Moneda> &v){
			string cad;
			Moneda m;			
			while(getline(os,cad)){
				m.setValor(atoi(cad.c_str()));
				if(m.getValor()/500==0)
					m.setEtiqueta(0);
				else	
					m.setEtiqueta(1);
				v.push_back(m);
			}
			return os;
		}

		bool comp(Moneda p1, Moneda p2){
			return p1.getValor()>p2.getValor();
		}

		bool comp2(Moneda p1, Moneda p2){
			return p1.getValor()<p2.getValor();
		}

		int minimo(const int &a, const int &b){
			if(a<b)
				return a;
			else
				return b;
		}


	void guardarTiempos(const vector<double> &cambio, const vector<double> &tiempos1, const vector<double> &tiempos2, const string &fichero){

		ofstream f(fichero.c_str());

		if(!f.is_open()){
			cout<<"Fichero no abierto"<<endl;
			exit(-1);
		}

		for (unsigned int i = 0; i < cambio.size(); ++i)
		{
			f<<cambio[i]<<" "<<tiempos1[i]<<" "<<tiempos2[i]<<endl;
		}
		f.close();
	}

	double calculaMedia(const vector<double> &v){
		double ret=0;

		for (unsigned int i = 0; i < v.size(); ++i)
		{
			ret+=v[i];
		}

		return ret/v.size();
	}

