#ifndef METODOSHELL_H
#define METODOSHELL_H

#include <vector>
#include "metodo.hpp"

using namespace std;

class Shell:virtual public Metodo{

	public:
		virtual void ordenar();
		inline Shell(){};
		inline ~Shell(){};
};

#endif