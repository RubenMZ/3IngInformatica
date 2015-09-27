#ifndef AJUSTE_H
#define AJUSTE_H

class Ajuste{

	public:
		void calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &r2);
		void calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &r2);
};


#endif