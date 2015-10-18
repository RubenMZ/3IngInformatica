/*!
	@author Ruben
	@file ajuste.hpp
	@brief Declaracion de la class Ajuste
*/

#ifndef AJUSTE_H
#define AJUSTE_H

#include <vector>
using namespace std;

/*!
	@class Ajuste
	@brief Clase que permite ajustar un algoritmo por su funcion en tiempo
*/

class Ajuste{

	public:

		void calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &r2);
		void calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &a3, double &r2);
		double calculaMedia(const vector<double> & v);
		double calcularVarianza(const vector<double> & v);

		
		void calcularTiemposEstimadosLineales(const vector<double> &x, const double  &a0, const double   &a1, vector<double> &yEstimada);
		void calcularTiemposEstimadosCubicos(const vector<double> &x, const double &a0, const double &a1, const double &a2, const double &a3, vector<double> &yEstimada); 
		double calcularDias(const double n, const double &a0, const double &a1, const double &a2, int opcion);
		double factorial(const double &n);

};


#endif