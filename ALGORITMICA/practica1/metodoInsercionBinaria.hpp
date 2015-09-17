#include <vector>
#include "metodo.hpp"

using namespace std;

class InsercionBinaria:virtual public Metodo{

	public:
		virtual void ordenar();
		inline InsercionBinaria(){};
		inline ~InsercionBinaria(){};
};
