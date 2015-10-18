
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
#include "matriz.hpp"
#include "determinanteRecursivo.hpp"

using namespace std;

	void Ajuste::calcularAjusteLineal(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &r2){

		double sumax=0.0;
		double sumay=0.0;
		double sumax2=0.0;
		double sumaxy=0.0;
		double mediax=0.0;
		double mediay=0.0;
		double varianzay=0.0;
		double varianzaEstimados=0.0;
		int n=x.size();

		vector <double> tEstimados;

		assert(x.size()==y.size());

		for (int i = 0; i < x.size(); ++i)
		{
			sumax+=x[i];
			sumay+=y[i];
			sumaxy+=x[i]*y[i];
			sumax2+=pow(x[i],2);

			mediax+=x[i];
			mediay+=y[i];
		}

		a0=((sumay*sumax2)-(sumaxy*sumax)) / ((n*sumax2)-(sumax*sumax)) ;
		a1=((n*sumaxy)-(sumax*sumay)) / ((n*sumax2)-(sumax*sumax)) ;

		calcularTiemposEstimadosLineales(x, a0, a1, tEstimados);

		varianzaEstimados=calcularVarianza(tEstimados);
		varianzay=calcularVarianza(y);

		r2=varianzaEstimados/varianzay;
	}

	void Ajuste::calcularAjustePolinomico(const vector<double> &x, const vector<double> &y, double &a0, double &a1, double &a2, double &a3, double &r2){
		
		double sumax=0.0;
		double sumay=0.0;
		double sumax2=0.0;
		double sumaxy=0.0;
		double sumax2y=0.0;
		double sumax3y=0.0;
		double sumax3=0.0;
		double sumax4=0.0;
		double sumax5=0.0;
		double sumax6=0.0;

		double varianzay=0.0;

		double detA0=0.0;
		double detA1=0.0;
		double detA2=0.0;
		double detA3=0.0;
		double det=0.0;

		vector <double> tEstimados;
		double varianzaEstimados=0.0;

		assert(x.size()==y.size());

		for (int i = 0; i < x.size(); ++i)
		{
			sumax+=x[i];
			sumay+=y[i];
			sumaxy+=x[i]*y[i];
			sumax2y+=pow(x[i],2)*y[i];
			sumax3y+=pow(x[i],3)*y[i];
			sumax2+=pow(x[i],2);
			sumax3+=pow(x[i],3);
			sumax4+=pow(x[i],4);
			sumax5+=pow(x[i],5);
			sumax6+=pow(x[i],6);
		}

		Matriz<double> mat(4,4);
		vector<double> ind;
		DeterminanteRecursivo<double> itera;

		mat.elemento(1,1, x.size());
		mat.elemento(1,2, sumax);
		mat.elemento(1,3, sumax2);
		mat.elemento(1,4, sumax3);
		mat.elemento(2,1, sumax);
		mat.elemento(2,2, sumax2);
		mat.elemento(2,3, sumax3);
		mat.elemento(2,4, sumax4);
		mat.elemento(3,1, sumax2);
		mat.elemento(3,2, sumax3);
		mat.elemento(3,3, sumax4);
		mat.elemento(3,4, sumax5);
		mat.elemento(4,1, sumax3);
		mat.elemento(4,2, sumax4);
		mat.elemento(4,3, sumax5);
		mat.elemento(4,4, sumax6);
		ind.push_back(sumay);
		ind.push_back(sumaxy);
		ind.push_back(sumax2y);
		ind.push_back(sumax3y);

		Matriz<double> maux(mat);
		maux.verMatriz();
		det = itera.determinanteRecursivo(maux, 4);

		for (int j = 1; j <= 4; ++j)
		{
			maux=mat;
			for (int i = 1; i <= 4; ++i)
			{
				maux.elemento(i,j, ind[i-1]);
			}

			if(j==1){
				detA0=itera.determinanteRecursivo(maux, 4);
			}
			if(j==2){
				detA1=itera.determinanteRecursivo(maux, 4);
			}
			if(j==3){
				detA2=itera.determinanteRecursivo(maux, 4);
			}
			if(j==4){
				detA3=itera.determinanteRecursivo(maux, 4);
			}
		}

		a0=detA0/det;
		a1=detA1/det;
		a2=detA2/det;
		a3=detA3/det;

		calcularTiemposEstimadosCubicos(x, a0, a1, a2, a3, tEstimados);

		varianzaEstimados=calcularVarianza(tEstimados);
		varianzay=calcularVarianza(y);

		r2=varianzaEstimados/varianzay;
	}

	double Ajuste::calculaMedia(const vector<double> & v){
		double media =0.0;

		for (int i = 0; i < v.size(); ++i)
		{
			media+=v[i];
		}
		return(media/v.size());
	}

	double Ajuste::calcularVarianza(const vector<double> & v){
		double varianza=0.0;
		double media=calculaMedia(v);

		for (int i = 0; i < v.size(); ++i)
		{
			varianza+=pow(v[i]-media, 2);
		}
		return (varianza/v.size());
	}


		
	void   Ajuste::calcularTiemposEstimadosLineales(const vector<double> &x, const double &a0, const double &a1, vector<double> &yEstimada){

		yEstimada.clear();

		for (int i = 0; i < x.size(); ++i)
		{
			yEstimada.push_back(a1*x[i]+a0);
		}
	}

	void   Ajuste::calcularTiemposEstimadosCubicos(const   vector<double>   &x,   const double &a0, const double &a1, const double &a2, const double &a3,vector<double> &yEstimada){

		yEstimada.clear();
		
		for (int i = 0; i < x.size(); ++i)
		{
			yEstimada.push_back(a3*pow(x[i],3)+a2*pow(x[i],2)+a1*x[i]+a0);
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

	double Ajuste::factorial(const double &n){
		if (n==2)
			return n;
		else
			return (n*factorial(n-1));
	}