/*!
	@file ecuImg.cc
    g++ -Wall -o ecuImg ecuImg.cc funciones.cc `pkg-config opencv --cflags --libs`
*/


#include <unistd.h>
#include <iostream>
#include <exception>
#include <vector>
#include "ecuImg.hpp"

//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

/*!\brief Define los parámetro opcionales de tu programa.

*/
struct CLIParams
{
  CLIParams ()
    : radio(0), //Valores por defecto de los argumentos opcionales.
      space(0),
      biparticionFlag(false),
      imageInFlag(false),
      maskFlag(false),
      imageOutFlag(false),
      imageIn(""),
      mask(""),
      imageOut("")
    {}
  int radio;
  int space;
  bool biparticionFlag;
  bool imageInFlag;
  bool maskFlag;
  bool imageOutFlag;
  string imageIn;
  string mask;
  string imageOut;
};

/*!\brief Muestra la ayuda del programa.  
  \arg[in] progname es el nombre del programa en la cli.
*/
static void
mostrarUso (const char * progname) throw ()
{
  std::cout << std::endl;
  std::cout << "Este programa sirve para mejorar una imagen aplicando la técnica de ecualización del histograma" << std::endl;
  std::cout << "Uso: " << progname << " [-h] [-r radio] [-b] input.png output.png [masc.png]" << std::endl;
  std::cout << "Donde: " << std::endl;
  std::cout << "-h\t\tMuestra esta ayuda." << std::endl;
  std::cout << "-r\t\tIndica el radio de ventana (2r+1, 2r+1)." << std::endl;
  std::cout << "-s\t\tEspecifica el espacio de color." << std::endl;
  std::cout << "-b\t\tActiva la ecualización por bipartición del histograma." << std::endl;
  std::cout << "input.png\t\tImagen a tratar." << std::endl;
  std::cout << "output.png\t\tImagen de salida." << std::endl;
  std::cout << "[masc.png]\tMáscara opcional para la imagen a tratar." << std::endl << std::endl;
}

/*!\brief Parsea la linea de comandos.
  \arg[in] argc es el número de argumentos en la línea.
  \arg[in] argv son los argumentos de la línea.
  \arg[out] params son los parámetros opcionales parseados.
  \return El índice del primer argumento no opcional de la línea.
  \warning Esta función no retorna si hay algún error en la cli.
*/
static int parseCLI (int argc, char* const* argv, CLIParams& params) throw ()
{
  // Esta es una forma habitual de recoger argumentos con getopt
  // se usa una iteracion y cada elemento se pasa por un switch-case
  int opcion;
  while ((opcion = getopt (argc, argv, "hr:s:bm:i:o:")) != -1)
  {
    switch (opcion)
    {
      
      case 'h':
		mostrarUso(argv[0]);
		exit (EXIT_SUCCESS);
		break;

      case 'r':
		params.radio = atoi(optarg);
		break;

      case 's':
        params.space = atoi(optarg);
        cout<<"Funcion espacio no implementada."<<endl;
        break;

       case 'i':
        params.imageInFlag = true;
        params.imageIn=optarg;
        break;

       case 'm':
        params.maskFlag = true;
        params.mask=optarg;
        break;

       case 'o':
        params.imageOutFlag = true;
        params.imageOut=optarg;
        break;

      case 'b':
        params.biparticionFlag = true;
        cout<<"Funcion biparticion no implementada."<<endl;
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
    cout << "Los parámetros opcionales son:" << endl;
    cout << "-r\tRadio: " <<  params.radio << endl;
    cout << "-s\tEspacio: " << params.space << endl;
    cout << "-b\t" << ((params.biparticionFlag)?"True":"False") << endl;
    cout << "-i\t" << "\"" << params.imageIn<<"\""<<endl;
    if(params.maskFlag==true)
   		cout << "-m\t" << "\"" << params.mask<< "\""<< endl;
   	if(params.imageOutFlag==true)
    	cout << "-o\t" << "\"" << params.imageOut<< "\"" <<endl;


	//Inicialización de variables
	Mat imagen, mask, salida;
	int radio = params.radio;
	vector<long> histograma(257);

	//Lectura de la imagen
	imagen = imread(params.imageIn,-1);
	
	//Comprobamos que la imagen se ha leído de manera correcta
	if (!imagen.data)
	{
		cout << "Error al leer la imagen" << endl;
		exit(EXIT_FAILURE);
	}
	
	//Leemos la máscara si se ha especificado por la terminal
	if ( params.maskFlag==true)
	{
		mask = imread(params.mask, 0);
		
		if (!mask.data)
		{
			cout << "Error al leer la máscara" << endl;
			exit(EXIT_FAILURE);
		}
	}
	
	//Convertimos la imagen al espacio de color HSV si la imagen tiene 3 canales
	if(imagen.channels() == 3)
		cvtColor(imagen, imagen, CV_BGR2YCrCb);
	//Radio = 0

	imshow(params.imageIn, imagen);
	waitKey();

	if(radio == 0)
	{
		//Calculamos el histograma de la imagen de entrada
		cout << "Calculando histograma..." << endl;
		calcularHistograma(histograma,imagen,mask);
		cout << "Normalizando histograma..." << endl;
		normalizarHistograma(histograma);
		cout << "Ecualizando imagen..." << endl;
		ecualizacion(imagen,histograma,mask);
	}
	else //Radio > 0
	{
		salida=imagen.clone();
		
		for(int x = radio; x < imagen.rows - radio; x++)
			for(int y = radio; y < imagen.cols - radio; y++)
			{
				//Creo ventana para la imagen
				Mat ventana(imagen,Rect(y-radio,x-radio,2*radio+1,2*radio+1));
				
				if(mask.data)
				{
					
					//Creo ventana para la mascara
					Mat ventMask(mask,Rect(y-radio,x-radio,2*radio+1,2*radio+1));
					//Calcular el histograma con la ventana y las mascara

					calcularHistograma(histograma,ventana,ventMask);

				}
				else
				{
					//Calcular hisograma sin mascara
					calcularHistograma(histograma,ventana,mask);
				}	
				cout<<"antes"<<endl;
				normalizarHistograma(histograma);
				//Ecualizacion

				cout<<"despues"<<endl;

				if(imagen.channels() == 3)
				{
					int valor = salida.at<Vec3b>(x,y)[2];
					salida.at<Vec3b>(x,y)[2] = histograma[valor];
				}
				else if(imagen.channels() == 1)
				{
					int valor = salida.at<uchar>(x,y);
					salida.at<uchar>(x,y) = histograma[valor];
				}
			}
				
	}
	
	if(params.imageOutFlag==false)
		params.imageOut="salida.png";

	//Deshacemos el cambio de espacio de color si lo hemos hecho
	if(radio == 0)
	{	if(imagen.channels() == 3)
			cvtColor(imagen,imagen,CV_YCrCb2BGR);
			
		imwrite(params.imageOut,imagen);
	}
	else
	{
		if(imagen.channels() == 3)
			cvtColor(salida,salida,CV_YCrCb2BGR);
			
		imwrite(params.imageOut,salida);
	}
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}