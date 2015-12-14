/*!
g++ getContour.cc funciones.cc -o getContour `pkg-config opencv --cflags --libs`
*/

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <cmath>
#include <vector>
#include <cstdio>

#include "funciones.h"

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

struct CLIParams
{
  CLIParams ()
    : fourier(0),
       imageIn(""),
       imageOut(""),
       flagimageIn(false),
       flagimageOut(false),
       flagTxt(false),
       txt("contorno.txt")
    {}
  int fourier;
  string imageIn;
  string imageOut;
  bool flagimageIn;
  bool flagimageOut;
  bool flagTxt;
  string txt;
};

static void mostrarUso (const char * progname) throw ()
{
  cout << endl;
  cout << "Este programa sirve para Representación y descripción de contornos:" << endl;
  cout << "Uso: " << progname << " getContour [-o cont.txt] [-n <int>] []" << endl;
  cout << "Donde: " << endl;
  cout << "-h\t\tMuestra esta ayuda." << endl;
  cout << "-t\t\tSelecciona n primeros descriptores de Fourier" << endl;
  cout << "-i\t\tImagen de entrada" << endl;
  cout << "-c\t\tImagen de Salida" << endl;
  cout << "-c\t\tArchivo con los puntos de contorno" << endl;
}

static int parseCLI (int argc, char* const* argv, CLIParams& params) throw ()
{

  int opcion;
  while ((opcion = getopt (argc, argv, "n:i:o:c:h")) != -1)
  {
    switch (opcion)
    {
      case 'n':
      		params.fourier=atoi(optarg);
      		break;

      case 'h':
		mostrarUso(argv[0]);
		exit (EXIT_SUCCESS);
		break;
	
      case 'i':
		params.flagimageIn=true;
		params.imageIn=optarg;
		break;
	
      case 'c':
		params.flagimageOut= true;
		params.imageOut=optarg;
		break;

	case 'o':
		params.flagTxt=true;
		params.txt=optarg;
		break;
	
      case '?': // en caso de error getopt devuelve el caracter ?
	
	if (isprint (optopt))
	  std::cerr << "Error: Opción desconocida \'" << optopt
	    << "\'" << std::endl;
	else
	  std::cerr << "Error: Caracter de opcion desconocido \'x" << std::hex << optopt
	    << "\'" << std::endl;
	mostrarUso(argv[0]);    
	exit (EXIT_FAILURE);
	
	// en cualquier otro caso lo consideramos error grave y salimos
      default:
	std::cerr << "Error: línea de comandos errónea." << std::endl;
	mostrarUso(argv[0]);
	exit(EXIT_FAILURE);	
    }  // case
    
  }// while
  return optind;
}



int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    
    CLIParams params;

    parseCLI(argc, argv, params);

    cout << endl;
    cout << "Los parámetros son:" << endl;
    cout << "-n\t" << params.fourier << endl;
    cout << "-i\t" << '\"' << params.imageIn << '\"' << endl;
    cout << "-c\t" << '\"' << params.imageOut << '\"' << endl;
    cout << "-o\t" << '\"' << params.txt << '\"' << endl;

    Mat src;
    if(params.flagimageIn){
    	if(!(src=imread(params.imageIn, 0)).data)
        	return -1;
    }else{
    	cout << "Introduce imagen: -i <imagen>"<<endl;
    	return -1;
    }

    Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);

    src = src > 1;
    namedWindow( "Original", 1 );
    imshow( "Original", src );

    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    vector< vector<Point> > contorno;

    findContours( src, contours, hierarchy,
        CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE );

    // iterate through all the top-level contours,
    // draw each connected component with its own random color
    for(int idx=0 ; idx >= 0; idx = hierarchy[idx][0] )
    {
  		drawContours( dst, contours, idx, Scalar(255,255,255), 1, 8, hierarchy, 0, Point() );
    }

    guardaFichero(src, contours, params.txt);

    cout<<"NContornos = "<<contours.size()<<endl;
    cout << "Dimensiones = "<< src.rows<<" x "<<src.cols<<endl;

    Stat prueba;

    for (unsigned int i = 0; i < contours.size(); ++i)
    {
      getEstadisticos(contours[i],prueba);
    }
    cout<<"Longitud: "<<prueba.longitud<<endl;
    cout<<"Area: "<<prueba.area<<endl;
 
    namedWindow( "Contorno", 1 );
    imshow( "Contorno", dst );
    waitKey(0);

}	
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}		
