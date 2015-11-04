/*!

    g++ -Wall -o unsharp unsharp.cc funciones.cc `pkg-config opencv --cflags --libs`

*/

//#include <stdio.h>
//#include <ctype.h>
//#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <vector>
#include "funciones.hpp"

//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


  using namespace std;
  using namespace cv;


  int main (int argc, char* const* argv)
{

	Mat imagen = imread(argv[1],-1);
	Mat imagen2= imread(argv[2],-1);
	Mat final = imagen.clone();

	/*for (int i = 0; i < imagen.rows; ++i)
	{
		for (int j = 0; j < imagen.cols; ++j)
		{
			//if(imagen.at<uchar>(i,j)<=imagen2.at<uchar>(i,j)+5.0 && imagen.at<uchar>(i,j)>=imagen2.at<uchar>(i,j)-5.0)
			//	final.at<uchar>(i,j)=0.0;
			//else
				final.at<uchar>(i,j)=255.0-imagen.at<uchar>(i,j);
		}
	}*/



	final =imagen- imagen2;


	imshow("Comparacion.png", final);
	waitKey();
	return 0;

}