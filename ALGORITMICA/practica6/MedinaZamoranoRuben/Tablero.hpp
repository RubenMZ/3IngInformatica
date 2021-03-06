#ifndef TABLERO_HPP
#define TABLERO_HPP

#include <vector>
#include <cassert>

using namespace std;

class Tablero{
	private:
		vector< vector<int> > tableros_;
		int nTab_;
		int ordenTab_;
	public:

		Tablero(){
			nTab_=0;
			ordenTab_=1;
		};

		inline vector < vector<int> > getTableros(){return tableros_;};
		inline vector<int> getTablero(const int &i){
			assert(i<getNTablero());
			return tableros_[i];
		};
		inline int getNTablero(){return nTab_;};
		inline int getOrdenTablero(){return ordenTab_;};

		inline void setOrdenTablero(const int &n){ordenTab_=n;};
		inline void setTableros(const vector < vector<int> > &x){tableros_=x;};
		inline void setTablero(const int &i, const vector<int> &tab){
			assert(i<getNTablero());
			if(i<getNTablero())
				tableros_[i]=tab;
		};

		inline bool addTablero(const vector<int> &tab){
			vector<int> aux;

			for (int i = 0; i < getNTablero(); ++i)
			{
				aux=getTablero(i);
				if (comparaTablero(aux, tab)==true)
				{
					return false;
				}
			}
			tableros_.push_back(tab);
			nTab_++;
			return true;
		};

		inline bool comparaTablero(const vector<int> &a, const vector<int> &b){
			bool flag=true;

			if(a.size()==b.size()){
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					if (a[i]!=b[i])
					{
						flag=false;
					}
				}
				return flag;
			}else{
				return false;
			}
		};

		inline bool addTablero(int * tab){
			vector<int> aux;
			bool flag;

			for (int i = 0; i < getOrdenTablero(); ++i)
			{
				aux.push_back(tab[i]);
			}
			flag=addTablero(aux);

			return (flag);
		};

		inline bool addTablero( Tablero tab){
			vector<int> aux;
			vector<int> t;
			int flag;

			for (int k = 0; k < tab.getNTablero(); ++k)
			{
				flag=false;
				t = tab.getTablero(k);
				for (int i = 0; i < getNTablero(); ++i)
				{
					aux=getTablero(i);
					if (comparaTablero(aux, t)==true)
					{
						flag=true;
					}
				}
				if(flag==false){
					tableros_.push_back(t);
					nTab_++;
				}
			}
			return true;
		};

		inline void eraseTableros(){
			tableros_.clear();
			nTab_=0;
		};

		inline void mostrarTableros(){
			for (int i = 0; i < getNTablero(); ++i)
			{
				mostrarTablero(getTablero(i));
			}
		};

		inline void mostrarTablero(const vector<int> &x){
			for (int i = 0; i < getOrdenTablero(); ++i)
			{
				for (int j = 0; j < getOrdenTablero(); ++j)
				{
					if(x[i]==j)
						cout<<" (R) ";
					else
						cout<<" ( ) ";
				}
				cout <<endl;
			}
			cout<<endl;
		}

		~Tablero(){
			tableros_.clear();
		}
};

#endif