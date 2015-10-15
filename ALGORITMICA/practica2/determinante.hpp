#ifndef DETERMINANTE_HPP
#define DETERMINANTE_HPP
#include "matriz.hpp"

template <class T>
class Determinante{

	private: 
		Matriz <T> matriz_;
		int orden_;

	public:
		Determinante(){
			orden_=1;
		};
		~Determinante(){
			matriz_.liberarMatriz();
		};
		inline void setMatriz(Matriz<T> m){matriz_=m;};
		inline Matriz <T> getMatriz(){return matriz_;};
		inline void setOrden(int n){orden_=n;};
		inline int getOrden(){return orden_;};
		virtual long getDet()=0;
};

#endif