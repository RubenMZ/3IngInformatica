#ifndef AJUSTE_H
#define AJUSTE_H

#include <vector>
using namespace std;

class Ajuste{

	public:
		void calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &r2);
		void calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &r2);
		double calculaDeterminante (const double &a1, const double &a2, const double &a3, const double &a4, const double &a5, const double &a6, const double &a7, const double &a8, const double &a9);
		void calcularTiemposEstimadosLineales(const vector<double> &x, const double  &a0, const double   &a1, vector<double> &yEstimada);
		void calcularTiemposEstimadosCuadraticos(const vector<double> &x, const double &a0, const double &a1, const double &a2, vector<double> &yEstimada); 
		double calcularDias(const double n, const double &a0, const double &a1, const double &a2, int opcion);
};


#endif