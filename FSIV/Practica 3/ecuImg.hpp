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

void calcularHistograma(vector <int> &histograma, const Mat imagen, const Mat mask);
void normalizarHistograma(vector <int> &histograma);
void ecualizacion(Mat &imagen, vector<int> histograma, Mat mask);

#endif
