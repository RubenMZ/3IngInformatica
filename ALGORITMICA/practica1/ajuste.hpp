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
		/*!
			@fn void calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &r2);
			@brief Calcula el ajuste lineal para el algoritmo Sofisticado, con elementos 'x' y tiempos 'y'
		*/
		void calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &r2);
		/*!
			@fn void calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &r2);
			@brief Calcula el ajuste polinomico para el algoritmo no sofisticado, con elementos 'x' y tiempos 'y'
		*/
		void calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &r2);
		/*!
			@fn double calculaDeterminante (const double &a1, const double &a2, const double &a3, const double &a4, const double &a5, const double &a6, const double &a7, const double &a8, const double &a9);
			@brief Calcula el determinamente para los coeficientes de una matriz, auxiliar para los ajustes
		*/
		double calculaDeterminante (const double &a1, const double &a2, const double &a3, const double &a4, const double &a5, const double &a6, const double &a7, const double &a8, const double &a9);
		/*!
			@fn void calcularTiemposEstimadosLineales(const vector<double> &x, const double  &a0, const double   &a1, vector<double> &yEstimada);
			@brief Calcula los tiempos estimados de forma lineal
		*/
		void calcularTiemposEstimadosLineales(const vector<double> &x, const double  &a0, const double   &a1, vector<double> &yEstimada);
		/*!
			@fn void calcularTiemposEstimadosCuadraticos(const vector<double> &x, const double &a0, const double &a1, const double &a2, vector<double> &yEstimada); 
			@brief Calcula los tiempos estimados de forma cuadratica
		*/
		void calcularTiemposEstimadosCuadraticos(const vector<double> &x, const double &a0, const double &a1, const double &a2, vector<double> &yEstimada); 
		/*!
			@fn double calcularDias(const double n, const double &a0, const double &a1, const double &a2, int opcion);
			@brief Calcula los dias que tarda en ejecutarse un algoritmo en funcion de sus coeficientes
		*/
		double calcularDias(const double n, const double &a0, const double &a1, const double &a2, int opcion);
};


#endif