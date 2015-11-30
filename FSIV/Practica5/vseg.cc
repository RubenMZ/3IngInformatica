/*!
g++ vseg.cc -o vseg `pkg-config opencv --cflags --libs`
*/

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <cmath>
#include <vector>
#include <cstdio>

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
    : umbral(0),
       videoIn(""),
       videoOut(""),
       flagvideoIn(false),
       flagvideoOut(false)
    {}
  int umbral;
  string videoIn;
  string videoOut;
  bool flagvideoIn;
  bool flagvideoOut;
};

static void mostrarUso (const char * progname) throw ()
{
  cout << endl;
  cout << "Este programa sirve para captura de video y substracción de fondo:" << endl;
  cout << "Uso: " << progname << " vseg [-t <int>] -v <input-pathname> -o <output-pathname>" << endl;
  cout << "Donde: " << endl;
  cout << "-h\t\tMuestra esta ayuda." << endl;
  cout << "-t\t\tSelecciona umbral de deteccion" << endl;
  cout << "-v\t\tVideo de entrada" << endl;
  cout << "-o\t\tVideo de Salida" << endl;
}

static int parseCLI (int argc, char* const* argv, CLIParams& params) throw ()
{

  int opcion;
  while ((opcion = getopt (argc, argv, "t:v:o:h")) != -1)
  {
    switch (opcion)
    {
      case 't':
      		params.umbral=atoi(optarg);
      		break;

      case 'h':
		mostrarUso(argv[0]);
		exit (EXIT_SUCCESS);
		break;
	
      case 'v':
		params.flagvideoIn=true;
		params.videoIn=optarg;
		break;
	
      case 'o':
		params.flagvideoOut= true;
		params.videoOut=optarg;
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
    cout << "-t\t" << params.umbral << endl;
    cout << "-v\t" << '\"' << params.videoIn << '\"' << endl;
    cout << "-o\t" << '\"' << params.videoOut << '\"' << endl;
 
 Mat video,frameVid,frameVidSig,diferencia, frameOut, frameOut2;
 VideoCapture video1, video2;



if(params.flagvideoIn==true){
	video1.open(params.videoIn);
	if(!video1.isOpened())
		return -1;
}else{
	cout<<"Introduce nombre: -v <video>"<<endl;
	exit(EXIT_FAILURE);
}

int ex = static_cast<int>(video1.get(CV_CAP_PROP_FOURCC)); //Get Codec Type- Int form
cv::Size S = cv::Size((int)video1.get(CV_CAP_PROP_FRAME_WIDTH), (int)video1.get(CV_CAP_PROP_FRAME_HEIGHT));

VideoWriter videoSalida;

if(params.flagvideoOut==true)
	videoSalida.open(params.videoOut, ex, 30, S, true);
else
	videoSalida.open("salida.avi", ex, 30, S, true);

//Declaro umbral
int umbral=params.umbral;
int pos=0;

namedWindow("Video",1);
namedWindow("Salida",1);
namedWindow("SalidaByN",1);



createTrackbar("Umbral","Video", &umbral, 255, 0);

video1 >> frameVidSig;

for(;;)
{
	frameVid = frameVidSig.clone();
	video1 >> frameVidSig;
	if(!frameVidSig.empty())
	{
		absdiff(frameVidSig,frameVid,diferencia);
		cvtColor(diferencia,diferencia,CV_BGR2GRAY);
		frameOut=frameVidSig.clone();
		cvtColor(frameVid,frameOut2, CV_BGR2GRAY);
		
		for(int i=0;i<diferencia.rows;i++)
			for(int j=0;j<diferencia.cols;j++){
				if(abs(diferencia.at<uchar>(i,j))<=umbral)
				{
					for(int k = 0; k < frameOut.channels(); k++){
                		frameOut.at<Vec3b>(i, j)[k] = 0;
              		}
					frameOut2.at<uchar>(i,j)=0;
				}else{
					frameOut2.at<uchar>(i,j)=255;
				}
			}
			
			imshow("Video",frameVid);
			imshow("Salida",frameOut);
			imshow("SalidaByN", frameOut2);
			
			int c=waitKey(30);

			if(c==30 || c==1048603)
				return -1;
			else 
				if(c==1179680 || c == 32 || c == 1048608)
				{
					char captura[50];
					Mat cap = frameOut.clone();
					sprintf(captura,"sal_%d.png",pos);
					
					for(int i=0;i<diferencia.rows;i++)
						for(int j=0;j<diferencia.cols;j++)
							if(diferencia.at<uchar>(i,j)<=umbral)
							{
								for(int k = 0; k < cap.channels(); k++)
									cap.at<Vec3b>(i,j)[k]=255;
							}
						imwrite(captura,cap);
						pos++;
				}

			videoSalida << frameOut;
	}
	else
	{
		video1.release();
		waitKey(20);
		return -1;
	}
}

}	
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}		
