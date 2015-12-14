#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <fstream>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

typedef struct Stat{
	float longitud;
	float diametro;
	float rectangulo;
	float excentricidad;
	float area;
	float ocupacion;
	float compacidad;
	float ocupacion_convexa;
	float solidez;
	float fourier;
}Stat;


void guardaFichero(const Mat & image, const vector< vector<Point> > & v, string fichero);

void getEstadisticos(const vector< Point > &v, Stat &datos);




#endif