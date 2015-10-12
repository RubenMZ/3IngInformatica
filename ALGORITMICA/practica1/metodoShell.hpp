/*!
    @author Ruben
    @file metodoShell.hpp
    @brief Declaracion de las funciones para Shell
*/

#ifndef METODOSHELL_H
#define METODOSHELL_H

#include <vector>
#include "metodo.hpp"

using namespace std;

/*!
	@class Shell
	@brief Clase que hereda del Metodo y ordena por metodo Shell
*/

class Shell:virtual public Metodo{

	public:
		/*!
			@fn virtual void ordenar();
			@brief Clase ordenacion del metodo, virtual
		*/
		virtual void ordenar();
		/*!
			@fn inline Shell(){};
			@brief Constructor
		*/
		inline Shell(){};
		/*!
			@fn inline ~Shell(){};
			@brief Destructor
		*/
		inline ~Shell(){};
};

#endif