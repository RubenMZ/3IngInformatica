#ifndef UNSHARP_HPP
#define UNSHARP_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void shiftDFT(Mat& fImage );
void create_butterworth_lowpass_filter(Mat &dft_Filter, float D, int n);
Mat create_spectrum_magnitude_display(Mat &complexImg);

#endif
