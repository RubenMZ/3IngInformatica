#ifndef STATS_HPP
#define STATS_HPP

#include <opencv2/core/core.hpp>
#include <cmath>
#include <iostream>

using namespace std;

using namespace cv;

class Stats{
	private:
		double min_;
		double max_;
		double media_;
		double varianza_;
		double suma_;
		double sumaCuadrados_;
		double areaPos_;
		double areaNeg_;
		double coefAsim_;
		double ceros_;

	public:

		Stats(){
			min_=256.0;
			max_=0.0;
			media_=0.0;
			varianza_=0.0;
			suma_=0.0;
			sumaCuadrados_=0.0;
			areaPos_=0.0;
			areaNeg_=0.0;
			coefAsim_=0.0;
			ceros_=0;
		};


		void calculateStats(const Mat &A, const Mat &mask, const int &cols, const int &rows){

			double aux;
			int calculate=1;
			double num=0.0;
			double sumaCubos=0.0;

			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					
				if(!mask.empty() && (mask.at<uchar>(i,j)==0.0) ){
					calculate=0;
				}else{
					calculate=1;
				}
					if(calculate==1){
						aux= A.at <uchar> (i,j);
						if(aux<min_)
							min_=aux;
						if(aux>max_)
							max_=aux;

						if(aux==0)
							ceros_++;

						if (aux>=0)
							areaPos_+=aux;
						else
							areaNeg_+=aux;

						suma_+=aux;
						sumaCuadrados_+=pow(aux,2);

						num++;
					}
				}
			}
			media_=suma_/(num);
			varianza_=(sumaCuadrados_/(num))-pow(media_,2);


			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
					
				if(!mask.empty() && (mask.at<uchar>(i,j)<255.0) ){
					calculate=0;
				}else{
					calculate=1;
				}
					if(calculate==1){
						aux= A.at <uchar> (i,j);
						sumaCubos+=pow(aux- media_ ,3);
					}
				}
			}
			coefAsim_ =sumaCubos / (pow(sqrt(varianza_),3) *(num) );

		}
		inline double getMin(){return min_;};
		inline double getMax(){return max_;};
		inline double getMedia(){return media_;};
		inline double getVarianza(){return varianza_;};
		inline double getSuma(){return suma_;};
		inline double getSumaCuadrados(){return sumaCuadrados_;};
		inline double getAreaPos(){return areaPos_;};
		inline double getAreaNeg(){return areaNeg_;};
		inline double getCoefAsim(){return coefAsim_;};
		inline int getCeros(){return ceros_;};

};

#endif 