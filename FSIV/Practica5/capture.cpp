/*!
g++ capture.cpp -o capture `pkg-config opencv --cflags --libs`
*/

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include "getStats.hpp"
#include <cmath>
#include <vector>
#include <cstdio>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

//Espacios de nombres
using namespace std;
using namespace cv;


//plantillas

/*!\brief Define los parámetro opcionales de tu programa.

  Redefine esta clase en función de tus necesitados
*/
struct CLIParams
{
  CLIParams ()
    : cadena(""), //Valores por defecto de los argumentos opcionales.
       interactivo(false)
    {}

  const char * cadena;
  bool interactivo;
};

/*!\brief Muestra la ayuda del programa.  
  Redefinir en función de los parámetros utilizados realmente.
  \arg[in] programe es el nombre del programa en la cli.
*/
static void
mostrarUso (const char * progname) throw ()
{
  std::cout << std::endl;
  std::cout << "Este programa sirve para calcular los estadísticos de una imagen" << std::endl;
  std::cout << "Uso: " << progname << " [-h] [-w \"x,y,w,h\"] [-i] img.png [masc.png]" << std::endl;
  std::cout << "Donde: " << std::endl;
  std::cout << "-h\t\tMuestra esta ayuda." << std::endl;
  std::cout << "-w\t\tIndica un área de interés (ROI) que empieza en x,y y tiene un ancho de w y un alto de h." << std::endl;
  std::cout << "-i\t\tEntrar en modo interactivo." << std::endl;
  std::cout << "img.png\t\tImagen a tratar." << std::endl;
  std::cout << "[masc.png]\tMáscara opcional para la imagen a tratar." << std::endl << std::endl;
}

/*!\brief Parsea la linea de comandos.
  \arg[in] argc es el número de argumentos en la línea.
  \arg[in] argv son los argumentos de la línea.
  \arg[out] params son los parámetros opcionales parseados.
  \return El índice del primer argumento no opcional de la línea.
  \warning Esta función no retorna si hay algún error en la cli.
*/
static int
parseCLI (int argc, char* const* argv, CLIParams& params) throw ()
{
  // Esta es una forma habitual de recoger argumentos con getopt
  // se usa una iteracion y cada elemento se pasa por un switch-case
  int opcion;
  while ((opcion = getopt (argc, argv, "hvi:c:f:")) != -1)
  {
    switch (opcion)
    {
      
      case 'h':
	mostrarUso(argv[0]);
	exit (EXIT_SUCCESS);
	break;
	
      case 'w':
	params.cadena = optarg;
	break;
	
      case 'f':
	params.interactivo= true;
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



int
main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    
    CLIParams params;

    int argopt = parseCLI(argc, argv, params);

     std::cout << std::endl;
    std::cout << "Los parámetros opcionales son:" << std::endl;
    std::cout << "-i\t" << ((params.interactivo)?"True":"False") << std::endl;
    std::cout << "-w\t" << '\"' << params.cadena << '\"' << std::endl;

    std::cout << "Hay " << argc-argopt << " parámetros obligados que son: " << std::endl;

   for (int i = argopt; i<argc; ++i)
      std::cout << '\"' << argv[i] << '\"' << std::endl;
    std::cout << std::endl;
    
//Carga de videos

///////////////////////////////////////////////////////////////
//Cargo el video

VideoCapture cap(argv[argopt]);
if(!cap.isOpened())
	return -1;

//Cargo el video de nuevo

VideoCapture cap2(argv[argopt]);
if(!cap2.isOpened())
	return -1;

//////////////////////////////////////////////////////////////////

//Declaro Mats
Mat video,frameC,frameCSig,differ,frameCG;

//Declaro umbral
int umbralT=0;
int cont=0;
int f,c;

namedWindow("Video",1);
namedWindow("VideoINT",1);



createTrackbar("Bar1","Video", &umbralT, 255, 0);

cap >> frameCSig;


for(;;)
{
	cap >> frameCSig;
	cap2 >>frameC;
	if(!frameCSig.empty())
	{
		absdiff(frameCSig,frameC,differ);
		cvtColor(differ,differ,CV_BGR2GRAY);
		cvtColor(frameCSig,frameCG,CV_BGR2GRAY);
		
		for(f=0;f<differ.rows;f++)
			for(c=0;c<differ.cols;c++)
				if(differ.at<uchar>(f,c)<=umbralT)
				{
					//differ.at<uchar>(f,c)=0;
					frameCG.at<uchar>(f,c)=0;
					
				}
			
			imshow("Video",frameC);
			imshow("VideoINT",frameCG);
			
			int teclado=waitKey(30);
			if(teclado==27)
				return -1;
			else if(teclado==32)
			{
				char nombre[50];
				sprintf(nombre,"captura%d.png",cont);
				
				for(f=0;f<differ.rows;f++)
					for(c=0;c<differ.cols;c++)
						if(differ.at<uchar>(f,c)==0)
						{
							frameCSig.at<Vec3b>(f,c)[0]=255;
							frameCSig.at<Vec3b>(f,c)[1]=255;
							frameCSig.at<Vec3b>(f,c)[2]=255;
						}
					imwrite(nombre,frameCSig);
					cont++;
			}
	}
	else
	{
		cap.release();
		cap2.release();
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
