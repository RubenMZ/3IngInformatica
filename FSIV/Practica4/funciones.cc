#include "funciones.hpp"


void centrarDFT(Mat& img )
{
  	Mat tmp, q0, q1, q2, q3;

	int cx = img.cols/2;
	int cy = img.rows/2;

	q0 = img(Rect(0, 0, cx, cy));
	q1 = img(Rect(cx, 0, cx, cy));
	q2 = img(Rect(0, cy, cx, cy));
	q3 = img(Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

void crearFiltroButterworth(Mat &filtro, float r, int n)
{
	Mat tmp = Mat(filtro.rows, filtro.cols, CV_32F);
	
	Point centre = Point(filtro.rows / 2, filtro.cols / 2);
	double radius;
	
	for (int i = 0; i < filtro.rows; i++)
	{
		for (int j = 0; j < filtro.cols; j++)
		{
			radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
			tmp.at<float>(i, j) = (float) ( 1 / (1 + pow( (double) (radius / r), (double) (2 * n))));
		}
	}
	
	Mat toMerge[] = {tmp, tmp};
	merge(toMerge, 2, filtro);
}

Mat crearEspectro(Mat &imagenCompleja)
{
    Mat planos[2];

    split(imagenCompleja, planos);
    magnitude(planos[0], planos[1], planos[0]);

    Mat espectro = (planos[0]).clone();
    espectro += Scalar::all(1);
    log(espectro, espectro);

    centrarDFT(espectro);

    normalize(espectro, espectro, 0, 1, CV_MINMAX);

    return espectro;

}
