/*!
  Miguel Díaz Gil

  Prácticas de Visión Artificial.

  Práctica 5: Análisis granulométrico

  OpenCV

  Para compilar, puedes ejecutar:
    g++ -Wall -o analisis analisis.cc `pkg-config opencv --cflags --libs`

*/

//#include <stdio.h>
//#include <ctype.h>
//#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <vector>
//#include "analisis.hpp"

//Includes para OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define MAX_KERNEL_LENGTH 31;

using namespace cv;

/*!\brief Define los parámetro opcionales de tu programa.

*/
struct CLIParams
{
  CLIParams ()
    : fcorte(0.5), //Valores por defecto de los argumentos opcionales.
      blur(3),
      ecualizacion(false),
      orden(2),
      ganancia(1.0)
    {}
  float fcorte;
  int blur;
  bool ecualizacion;
  int orden;
  float ganancia;
};

/*!\brief Muestra la ayuda del programa.  
  \arg[in] progname es el nombre del programa en la cli.
*/
static void
mostrarUso (const char * progname) throw ()
{
  std::cout << std::endl;
  std::cout << "Este programa aplica un método de segmentación a una imagen y realiza un análisis granulométrico" << std::endl;
  std::cout << "Uso: " << progname << " [-i] [-s <int>] [-r <float>] [-n <int>] [-g <float>] input.png output.png [masc.png]" << std::endl;
  std::cout << "Donde: " << std::endl;
  std::cout << "-h\t\tMuestra esta ayuda." << std::endl;
  std::cout << "-b\t\tEspecifica el filtro a utilizar: 0 - Blur homogéneo, 1 - Gaussian blur, 2 - Median blur." << std::endl;
  std::cout << "-e\t\tActiva la ecualización." << std::endl;
  std::cout << "input.png\tImagen a tratar." << std::endl;
  std::cout << "output.png\tImagen de salida." << std::endl << std::endl;
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
  while ((opcion = getopt (argc, argv, "hn:b:er:g:")) != -1)
  {
    switch (opcion)
    {
      
      case 'h':
	mostrarUso(argv[0]);
	exit (EXIT_SUCCESS);
	break;

      case 'n':
	params.orden = atoi(optarg);
	break;

      case 'b':
        params.blur = atoi(optarg);
        break;

      case 'e':
        params.ecualizacion = true;
        break;
        
      case 'r':
      	params.fcorte = atof(optarg);
      	break;
      	
      case 'g':
      	params.ganancia = atof(optarg);
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

void aplicarMascara(Mat &imagen, Mat &canalIluminacion);
void calcularHistograma(vector <int> &histograma, const Mat imagen, const Mat mask);
void normalizarHistograma(vector <int> &histograma);
void ecualizacion(Mat &imagen, vector<int> histograma, Mat mask);

int
main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    
    CLIParams params;

    int argOpt = parseCLI(argc, argv, params);

    std::cout << std::endl;
    std::cout << "Los parámetros opcionales son:" << std::endl;
    std::cout << "-e\t" << ((params.ecualizacion)?"True":"False") << std::endl;
    std::cout << "-b\t" << '\"' << params.blur << '\"' << std::endl;

    std::cout << "Hay " << argc-argOpt << " parámetros obligados que son: " << std::endl;

    for (int i = argOpt; i<argc; ++i)
      std::cout << '\"' << argv[i] << '\"' << std::endl;
    std::cout << std::endl;

	using namespace std;
	using namespace cv;

	//Inicialización de variables
	char *nombre;
	Mat imagen, imagenHSV, canalIluminacion, mask;
	vector <Mat> canales; //Vector para almacenar canales
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<int> histograma(256);
	
	nombre=argv[argOpt];
    	
	//Lectura de la imagen
	imagen = imread(nombre,-1);
	
	//Comprobamos que la imagen se ha leído de manera correcta
	if (!imagen.data)
	{
		cout << "Error al leer la imagen" << endl;
		exit(EXIT_FAILURE);
	}
     	
	//Convertimos la imagen al espacio de color indicado si la imagen tiene 3 canales
	const int channels = imagen.channels();
	if(channels == 3)
	{
			cvtColor(imagen, imagenHSV, CV_BGR2HSV);
			split(imagenHSV, canales);
      			canales[2].copyTo(canalIluminacion);
      	}
	else if (channels == 1)
		imagen.copyTo(canalIluminacion);
      	
	switch(params.blur)
	{
		case 0: 
       			blur( canalIluminacion, canalIluminacion, Size( 3, 3 ), Point(-1,-1) );
			break;
			
		case 1:    
			GaussianBlur( canalIluminacion, canalIluminacion, Size( 3, 3 ),0,0);
        		break;
        		
        	case 2: 
         		medianBlur ( canalIluminacion, canalIluminacion, 3 );
         		break;
         		
         	default: cout << "Ningún filtro válido seleccionado." << endl;
       			//blur( canalIluminacion, canalIluminacion, Size( 3, 3 ), Point(-1,-1) );
			break;
	}   
	
	if(params.ecualizacion)
	{
		//Calculamos el histograma de la imagen de entrada
		cout << "Calculando histograma..." << endl;
		calcularHistograma(histograma,canalIluminacion,mask);
		cout << "Normalizando histograma..." << endl;
		normalizarHistograma(histograma);
		cout << "Ecualizando imagen..." << endl;
		ecualizacion(canalIluminacion,histograma,mask);
	}
	
/*										SEGMENTACIÓN
	Los métodos del valor umbral separan los objetos de la imagen que nos interesan del resto. Como todos los métodos de segmentación, se trata de asignar cada píxel a un cierto 		grupo (segmento). La pertenencia de un píxel a dicho grupo se basa en su nivel de gris.	
	
 										OTSU
	El filtro Otsu utiliza técnicas estadísticas. En concreto, se utiliza la variancia, que es una medida de la dispersión de los niveles de gris. 
   	El método de Otsu calcula el valor umbral de forma que la dispersión dentro de cada segmento sea lo más pequeña posible, pero al mismo tiempo la dispersión sea lo más alta 		posible entre segmentos diferentes. Para ello se calcula el cociente entre ambas variancias y se busca un valor umbral para el que este cociente sea máximo.
   	
   										OPENING
   	La operación morfológica Opening realiza una erosión y posteriormente una dilatación. De esta manera conseguimos quitar los claros menos significativos alrededor de los oscuros 		y conseguimos separar granos.
   	
*/
	
	threshold(canalIluminacion, canalIluminacion,0 , 255, THRESH_OTSU+THRESH_BINARY_INV); //Aplico la técnica de umbralización Otsu
	
	imshow("OTSU", canalIluminacion);
	waitKey(0);
	
	Mat element = Mat::ones(3, 3, CV_8UC1); //Creo un elemento estructural
	
	morphologyEx(canalIluminacion, canalIluminacion, MORPH_OPEN, element ); //Operación morfológica opening (erosión + dilatación)
	//morphologyEx(canalIluminacion, canalIluminacion, MORPH_BLACKHAT, element ); //Operación blackhat
	erode(canalIluminacion, canalIluminacion, element); //Operación morfológica erosión
	imshow("Imagen procesada", canalIluminacion);
	waitKey(0);
			
	findContours(canalIluminacion, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0)); //Busca contornos (vector de puntos) en la imagen procesada generada
	
	cout << "El número de 'granos' es " << hierarchy.size() << endl;
		
	aplicarMascara(imagen, canalIluminacion);
		
	imshow("Imagen", imagen);
	waitKey(0);
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}

void aplicarMascara(Mat &imagen, Mat &canalIluminacion)
{
	int i, j;
	
	for(i=0; i<imagen.rows; i++)
	{
		for(j=0; j<imagen.cols; j++)
		{
			if(canalIluminacion.at<uchar>(i, j) != 0)
			{
				imagen.at<Vec3b>(i, j)[2]=255;
			}
		}
	}
}

//Función que calcula el histograma de una imagen considerando la máscara, si la hubiera, y lo almacena en un vector.
void calcularHistograma(vector <int> &histograma, const Mat imagen, const Mat mask)
{
	const int channels = imagen.channels();

	for(size_t i=0; i<histograma.size();i++)
		histograma[i]=0;
		
	switch(channels)
	{
	case 1:{
		for(int x=0; x<imagen.rows; x++)
			for(int y=0; y<imagen.cols; y++)
				if(mask.data)
				{
					if(mask.at<uchar>(x,y)!= 0)
					{
						int valor = imagen.at<uchar>(x,y);
						histograma[valor]++;
					}
				}
				else
				{
					int valor = imagen.at<uchar>(x,y);
					histograma[valor]++;
				}
		break;
		}
	case 3:{
		//MatConstIterator_<Vec3b> it = imagen.begin<Vec3b>();		ITERADORES PARA RECORRER! ACCEDER CON (*it)[2]. SOLO LECTURA.
		//MatConstIterator_<Vec3b> end = imagen.end<Vec3b>();
		
		for(int x=0; x<imagen.rows; x++)
			for(int y=0; y<imagen.cols; y++)
				if(mask.data)
				{
					if(mask.at<uchar>(x,y) != 0)
					{
						int valor = imagen.at<Vec3b>(x,y)[2];
						histograma[valor]++;
					}
				}
				else
				{
					int valor = imagen.at<Vec3b>(x,y)[2];
					histograma[valor]++;
				}
		break;
		}
	}
}

//Función que realiza la ecualización del histograma obteniendo primero el histograma acumulativo y dividiéndolo posteriormente por el número de píxeles totales
void normalizarHistograma(vector <int> &histograma)
{	
	int pixels = histograma[0]; //Contador de píxeles totales que comienza con el número de píxeles que hay en histograma[0]
	
	//Calculamos el histograma acumulado
	for(size_t i = 1; i < histograma.size(); ++i)
	{
		pixels = pixels + histograma[i];
		histograma[i] = histograma[i] + histograma[i-1];
	}

	//Normalizamos el histograma acumulado
	for(size_t j = 0; j < histograma.size(); ++j)
		histograma[j] = 255*histograma[j]/pixels; //Podemos realizar también la operación de manera vectorial con histograma = 255*histograma;
}

//Función que realiza la ecualización de la imagen utilizando para ello el histograma normalizado obtenido
void ecualizacion(Mat &imagen, vector<int> histograma, Mat mask)
{
	const int channels = imagen.channels();

	switch(channels)
	{
	case 1:{
		for(int x=0; x<imagen.rows; x++)
			for(int y=0; y<imagen.cols; y++)
				if(mask.data)
				{
					if(mask.at<uchar>(x,y) != 0)
					{
						int valor = imagen.at<uchar>(x,y);
						imagen.at<uchar>(x,y) = histograma[valor];
					}
				}
				else
				{
					int valor = imagen.at<uchar>(x,y);
					imagen.at<uchar>(x,y) = histograma[valor];
				}
		break;
		}
	case 3:{
		for(int x=0; x<imagen.rows; x++)
			for(int y=0; y<imagen.cols; y++)
				if(mask.data)
				{
					if(mask.at<uchar>(x,y) != 0)
					{
						int valor = imagen.at<Vec3b>(x,y)[2];
						imagen.at<Vec3b>(x,y)[2] = histograma[valor];
					}
				}
				else
				{
					int valor = imagen.at<Vec3b>(x,y)[2];
					imagen.at<Vec3b>(x,y)[2] = histograma[valor];
				}
		break;
		}
	}
}
