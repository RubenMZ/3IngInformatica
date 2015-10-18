/*!

    g++ -Wall -o ecuImg ecuImg.cc funciones.cc `pkg-config opencv --cflags --libs`

	José Enrique Ortega Ortega OPC2
*/


#ifndef ECUIMG_HPP
#define ECUIMG_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void crearHistograma(vector <double> &histograma, const Mat imagen, const Mat mask);
void normalizar(vector <double> &histograma);
void ecualizar(vector<double> histograma, Mat &imagen, Mat mask);

#endif
