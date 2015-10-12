
/*!
	@author Ruben
	@file ajuste.cpp
	@brief Definicion de las funciones para la class Ajuste
*/

#include "ajuste.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>  
#include <cstdlib> 

using namespace std;

	void Ajuste::calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &r2){

		double sumax=0.0;
		double sumay=0.0;
		double sumax2=0.0;
		double sumaxy=0.0;
		double mediax=0.0;
		double mediay=0.0;
		double varianzax=0.0;
		double varianzay=0.0;
		double covarianza=0.0;
		double n=x.size();

		assert(x.size()==y.size());

		for (int i = 0; i < x.size(); ++i)
		{
			sumax+=x[i]*log(x[i]);
			sumay+=y[i];
			sumaxy+=x[i]*log(x[i])*y[i];
			sumax2+=pow(x[i]*log(x[i]),2);

			mediax+=x[i];
			mediay+=y[i];
		}

		a0=((sumay*sumax2)-(sumaxy*sumax)) / ((n*sumax2)-(sumax*sumax)) ;
		a1=((n*sumaxy)-(sumax*sumay)) / ((n*sumax2)-(sumax*sumax)) ;

		mediax=mediax/n;
		mediay=mediay/n;

		for (int i = 0; i < x.size(); ++i)
		{
			varianzax+=pow(x[i]-mediax,2);
			varianzay+=pow(y[i]-mediay,2);
			covarianza+=(x[i]-mediax)*(y[i]-mediay);
		}

		varianzax=varianzax/n;
		varianzay=varianzay/n;
		covarianza=covarianza/n;

		r2=pow(covarianza,2)/(varianzax*varianzay);
	}

	void Ajuste::calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &r2){
		
		double sumax=0.0;
		double sumay=0.0;
		double sumax2=0.0;
		double sumaxy=0.0;
		double sumax2y=0.0;
		double sumax3=0.0;
		double sumax4=0.0;

		double mediax=0.0;
		double mediay=0.0;
		double varianzax=0.0;
		double varianzay=0.0;
		double covarianza=0.0;
		double n=x.size();

		double detA0;
		double detA1;
		double detA2;
		double det;

		vector <double> tEstimados;
		double sumaEstimados=0.0;
		double mediaEstimados=0.0;
		double varianzaEstimados=0.0;


		assert(x.size()==y.size());

		for (int i = 0; i < x.size(); ++i)
		{
			sumax+=x[i];
			sumay+=y[i];
			sumaxy+=x[i]*y[i];
			sumax2y+=pow(x[i],2)*y[i];
			sumax2+=pow(x[i],2);
			sumax3+=pow(x[i],3);
			sumax4+=pow(x[i],4);
		}

		detA0=calculaDeterminante 	(sumay,sumax, sumax2, 
									sumaxy, sumax2, sumax3, 
									sumax2y,sumax3,sumax4);
		detA1=calculaDeterminante 	(n, sumay, sumax2,
									sumax, sumaxy, sumax3, 
									sumax2, sumax2y, sumax4);
		detA2=calculaDeterminante 	(n, sumax, sumay,
									sumax,sumax2, sumaxy,
									sumax2, sumax3, sumax2y);
		det=calculaDeterminante 	(n,sumax,sumax2,
									sumax, sumax2, sumax3,
									sumax2, sumax3, sumax4);


		a0=detA0/det;
		a1=detA1/det;
		a2=detA2/det;

		mediax=sumax/n;
		mediay=sumay/n;

		calcularTiemposEstimadosCuadraticos(x, a0, a1, a2, tEstimados);

		for (int i = 0; i < tEstimados.size(); ++i)
		{
			sumaEstimados+=tEstimados[i];
		}

		mediaEstimados=sumaEstimados/tEstimados.size();

		for (int i = 0; i < x.size(); ++i)
		{
			varianzay+=pow(y[i]-mediay,2);
			varianzaEstimados+=pow(tEstimados[i]-mediaEstimados, 2);
		}

		varianzaEstimados=varianzaEstimados/n;
		varianzay=varianzay/n;

		r2=varianzaEstimados/varianzay;
	}
		
	
	double Ajuste::calculaDeterminante (const double &a1, const double &a2, const double &a3, const double &a4, const double &a5, const double &a6, const double &a7, const double &a8, const double &a9){
		return a1*a5*a9 + a4*a8*a3 + a7*a2*a6 - (a3*a5*a7 + a6*a8*a1 + a9*a2*a4);
	}


	void   Ajuste::calcularTiemposEstimadosLineales(const vector<double> &x, const double &a0, const double &a1, vector<double> &yEstimada){

		yEstimada.clear();

		for (int i = 0; i < x.size(); ++i)
		{
			yEstimada.push_back(a1*x[i]*log(x[i])+a0);
		}
	}

	void   Ajuste::calcularTiemposEstimadosCuadraticos(const   vector<double>   &x,   const double &a0, const double &a1, const double &a2, vector<double> &yEstimada){

		yEstimada.clear();
		
		for (int i = 0; i < x.size(); ++i)
		{
			yEstimada.push_back(a2*pow(x[i],2)+a1*x[i]+a0);
		}

	}

	double Ajuste::calcularDias(const double n, const double &a0, const double &a1, const double &a2, int opcion){

		double retorno=0;

		if(opcion==1){
			retorno= (a1*n*log(n) +a0 ) / 1000000;
			retorno=retorno/3600;
			retorno=retorno/24;
		}else{
			retorno=(a2*pow(n,2) + a1*n +a0 ) / 1000000;
			retorno=retorno/3600;
			retorno=retorno/24;
		}
		return retorno;
	}