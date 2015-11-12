#include "Cambio.hpp"



		Cambio::Cambio(const string &fichero){
			ifstream file(fichero.c_str());

			suma_=0;
			file>>monedas_;
			file.close();
			sort(monedas_.begin(), monedas_.end(), comp);
		}
		Cambio::Cambio(const vector<int> &v){
			suma_=0;
			monedas_=v;
			sort(monedas_.begin(), monedas_.end(), comp);
		}

		Cambio::~Cambio(){
			monedas_.clear();
			solucion_.clear();
		}



		bool Cambio::hacerAlgoritmo(const int &n){
			int x;
			unsigned int index=0;	
			solucion_.clear();

			while(getSuma()!=n){
				x = monedas_[index];
				if(getSuma()+x <= n){
					solucion_.push_back(x);
					setSuma(getSuma()+x);
				}else{
					index++;
				}
				if(index==(monedas_.size())  && getSuma() != n){
					return false;
				}
			}
			return true;
		}




