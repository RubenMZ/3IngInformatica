#ifndef STATS_HPP
#define STATS_HPP

#include <opencv2/core/core.hpp>
#include <cmath>

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


		void calculateStats(Mat A, int cols, int rows){

			double aux;

			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
				{
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

				}
			}
			media_=suma_/(rows*cols);
			varianza_=(sumaCuadrados_/(rows*cols))-pow(media_,2);
			coefAsim_=((sumaCuadrados_*suma_)*pow(media_,3))/((rows*cols)*pow(sqrt(varianza_),3));

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