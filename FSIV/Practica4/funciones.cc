#include "unsharp.hpp"
/*FUENTES:
	http://breckon.eu/toby/teaching/dip/opencv/lecture_demos/c++/butterworth_lowpass.cpp
	https://github.com/alessandro-gentilini/opencv_exercises-butterworth/blob/master/butterworth.cpp
*/

//Reordena los cuadrantes de una imagen de Fourier de manera que el origen esté en el centro de la imagen
void shiftDFT(Mat& fImage )
{
  	Mat tmp, q0, q1, q2, q3;

	//fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));

	int cx = fImage.cols/2;
	int cy = fImage.rows/2;

	q0 = fImage(Rect(0, 0, cx, cy));
	q1 = fImage(Rect(cx, 0, cx, cy));
	q2 = fImage(Rect(0, cy, cx, cy));
	q3 = fImage(Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

//Función que crea un filtro Butterworth de paso baja de 2 canales con radio D (frecuencia de corte) y orden n
void create_butterworth_lowpass_filter(Mat &dft_Filter, float D, int n)
{
	Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F); //Guardo la imagen en un auxiliar
	
	Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2); //Almaceno el punto central de la imagen para trabajar con el radio desde el centro de la imagen
	double radius;
	
	for (int i = 0; i < dft_Filter.rows; i++)
	{
		for (int j = 0; j < dft_Filter.cols; j++)
		{
			radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
			tmp.at<float>(i, j) = (float) ( 1 / (1 + pow( (double) (radius / D), (double) (2 * n))));
		}
	}
	
	Mat toMerge[] = {tmp, tmp};
	merge(toMerge, 2, dft_Filter);
}
