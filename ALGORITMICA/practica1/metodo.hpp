/*!
	@author Ruben
	@file metodo.hpp
	@brief Declaracion de la virtual class Metodo
*/

#ifndef METODO_H
#define METODO_H
#include <vector>

/*!
	@class Metodo
	@brief Clase virtual con un vector y elementos, cuyo metodo es virtual para implementarlo en funcion de la clase Metodo X que herede
*/
class Metodo{

	private: 
		std::vector<int> vector_;
		int elementos_;

	public:
		/*!
			@fn inline void setVector(std::vector<int> v){vector_=v;};
			@brief Modificador que asigna un vector
		*/
		inline void setVector(std::vector<int> v){vector_=v;};
		/*!
			@fn inline std::vector<int> getVector(){return vector_;};
			@brief Observador que devuelve el vector
		*/
		inline std::vector<int> getVector(){return vector_;};

		/*!
			@fn inline void setElementos(int n){elementos_=n;};
			@brief Modificador que asigna el n elementos
		*/
		inline void setElementos(int n){elementos_=n;};
		/*!
			@fn inline int getElementos(){return elementos_;};
			@brief Observador que devuelve el numero de elementos
		*/
		inline int getElementos(){return elementos_;};

		virtual void ordenar()=0;
};

#endif