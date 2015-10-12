/*!
    @author Ruben
    @file metodoInsercionBinaria.hpp
    @brief Declaracion de las funciones para Insercion Binaria
*/


#ifndef METODOINSERCION_H
#define METODOINSERCION_H

#include <vector>
#include "metodo.hpp"

using namespace std;

/*!
	@class InsercionBinaria
	@brief Clase que hereda del Metodo y ordena por metodo Insercion Binaria
*/

class InsercionBinaria:virtual public Metodo{

	public:
		/*!
			@fn virtual void ordenar();
			@brief Clase ordenacion del metodo, virtual
		*/
		virtual void ordenar();
		/*!
			@fn inline InsercionBinaria(){};
			@brief Constructor
		*/
		inline InsercionBinaria(){};
		/*!
			@fn inline ~InsercionBinaria(){};
			@brief Destructor
		*/
		inline ~InsercionBinaria(){};
};

#endif