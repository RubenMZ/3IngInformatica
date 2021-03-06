#ifndef UNSHARP_HPP
#define UNSHARP_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void centrarDFT(Mat& img );
void crearFiltroButterworth(Mat &filtro, float r, int n);
Mat crearEspectro(Mat &complexImg);

#endif
