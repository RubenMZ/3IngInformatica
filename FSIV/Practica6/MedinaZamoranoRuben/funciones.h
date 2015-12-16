#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <fstream>
#include <cmath>

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>

#define PI (3.141592653589793)
#define E (2.71828182845904)

using namespace std;
using namespace cv;

typedef struct Stat{
	float longitud;
	float diametro;
	RotatedRect rectangulo;
	float excentricidad;
	float area;
	float ocupacion;
	float compacidad;
	float ocupacion_convexa;
	float solidez;
	vector< float > fourier;
}Stat;


void guardaFichero(const Mat & image, const vector< Point > & v, string fichero);

void getEstadisticos(const Mat &dst, const vector< Point > &v, Stat &datos);

void getFourier(const vector< Point> &seq_pts, vector< float > &seq_fourier);

float getDiametro(const vector< Point > & v);




#endif