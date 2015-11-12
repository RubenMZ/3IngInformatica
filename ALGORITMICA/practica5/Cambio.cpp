#include "Cambio.hpp"



		Cambio::Cambio(const string &fichero){
			ifstream file(fichero.c_str());

			if (!file.is_open())
			{
				cout<<"El fichero no se puede abrir."<<endl;
				exit(EXIT_FAILURE);
			}

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
			sort(monedas_.begin(), monedas_.end(), comp);
		}



		bool Cambio::hacerAlgoritmo(const int &n){
			int x;
			unsigned int index=0;	
			solucion_.clear();
			suma_=0;

			sort(monedas_.begin(), monedas_.end(), comp);
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

		bool Cambio::hacerAlgoritmoDinamico(const int &n){

			solucion_.clear();
			int tam = monedas_.size();

			matriz_=(int **)malloc(tam*sizeof(int *));
			for (int i = 0; i < tam; ++i)
			{
				matriz_[i]=(int*)malloc((n+1)*sizeof(int));
			}

			sort(monedas_.begin(), monedas_.end(), comp2);

			for (int i = 0; i < tam; ++i)
			{
				matriz_[i][0]=0;
			}

			for (int i = 0; i < tam; ++i)
			{
				for (int j = 0; j <= n; ++j)
				{
					if(i==0 && j<monedas_[i])
						matriz_[i][j]=numeric_limits<int>::infinity();
					else{
						if(i==0){
							matriz_[i][j]=1+matriz_[i][j-monedas_[i]];
						}else{
							if(j<monedas_[i])
								matriz_[i][j]=matriz_[i-1][j];
							else
								matriz_[i][j]=minimo(matriz_[i-1][j],1+matriz_[i][j-monedas_[i]]);
						}
					}
				}
			}

			return true;
		}


