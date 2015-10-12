/*!

    g++ -Wall -o ecuImg ecuImg.cc funciones.cc `pkg-config opencv --cflags --libs`

	José Enrique Ortega Ortega OPC2
*/

//#include <stdio.h>
//#include <ctype.h>
//#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <vector>
#include "ecuImg.hpp"

//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/*!\brief Define los parámetro opcionales de tu programa.

*/
struct CLIParams
{
  CLIParams ()
    : radio(0), //Valores por defecto de los argumentos opcionales.
      space(0),
      biparticion(false)
    {}
  int radio;
  int space;
  bool biparticion;
};

/*!\brief Muestra la ayuda del programa.  
  \arg[in] progname es el nombre del programa en la cli.
*/
static void
mostrarUso (const char * progname) throw ()
{
  std::cout << std::endl;
  std::cout << "Este programa sirve para mejorar una imagen aplicando la técnica de ecualización del histograma" << std::endl;
  std::cout << "Uso: " << progname << " [-h] [-r r] [-i] input.png output.png [masc.png]" << std::endl;
  std::cout << "Donde: " << std::endl;
  std::cout << "-h\t\tMuestra esta ayuda." << std::endl;
  std::cout << "-r\t\tIndica el radio de ventana que se quiere utilizar mediante (2r+1, 2r+1)." << std::endl;
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
static int
parseCLI (int argc, char* const* argv, CLIParams& params) throw ()
{
  // Esta es una forma habitual de recoger argumentos con getopt
  // se usa una iteracion y cada elemento se pasa por un switch-case
  int opcion;
  while ((opcion = getopt (argc, argv, "hr:s:b")) != -1)
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
        break;

      case 'b':
        params.biparticion = true;
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

    int argOpt = parseCLI(argc, argv, params);

    std::cout << std::endl;
    std::cout << "Los parámetros opcionales son:" << std::endl;
    std::cout << "-r\t" << '\"' << params.radio << '\"' << std::endl;
    std::cout << "-s\t" << '\"' << params.space << '\"' << std::endl;
    std::cout << "-b\t" << ((params.biparticion)?"True":"False") << std::endl;

    std::cout << "Hay " << argc-argOpt << " parámetros obligados que son: " << std::endl;

    for (int i = argOpt; i<argc; ++i)
      std::cout << '\"' << argv[i] << '\"' << std::endl;
    std::cout << std::endl;

	using namespace std;
	using namespace cv;

	//Inicialización de variables
	Mat imagen, mask, salida;
	int radio = params.radio;
	vector<int> histograma(256);

	//Lectura de la imagen
	imagen = imread(argv[argOpt],-1);
	
	//Comprobamos que la imagen se ha leído de manera correcta
	if (!imagen.data)
	{
		cout << "Error al leer la imagen" << endl;
		exit(EXIT_FAILURE);
	}
	
	//Leemos la máscara si se ha especificado por la terminal
	if ( argc == 3 || argc == 5)
	{
		mask = imread(argv[argOpt+1], 0);
		
		if (!mask.data)
		{
			cout << "Error al leer la máscara" << endl;
			exit(EXIT_FAILURE);
		}
	}
	
	//Convertimos la imagen al espacio de color HSV si la imagen tiene 3 canales
	const int channels = imagen.channels();
	if(channels == 3)
		cvtColor(imagen, imagen, CV_BGR2HSV);
	//Radio = 0
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
					//Calcular el histograma con la venta na y las mascara
					calcularHistograma(histograma,ventana,ventMask);
				}
				else
				{
					//Calcular hisograma sin mascara
					calcularHistograma(histograma,ventana,mask);
				}	

				normalizarHistograma(histograma);
				//Ecualizacion
				if(channels == 3)
				{
					int valor = salida.at<Vec3b>(x,y)[2];
					salida.at<Vec3b>(x,y)[2] = histograma[valor];
				}
				else if(channels == 1)
				{
					int valor = salida.at<uchar>(x,y);
					salida.at<uchar>(x,y) = histograma[valor];
				}
			}
				
	}
	
	//Deshacemos el cambio de espacio de color si lo hemos hecho
	if(radio == 0)
	{	if(channels == 3)
			cvtColor(imagen,imagen,CV_HSV2BGR);
		
		imwrite("prueba.png",imagen);
	}
	else
	{
		if(channels == 3)
			cvtColor(salida,salida,CV_HSV2BGR);
			
		imwrite("prueba.png",salida);
	}
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
