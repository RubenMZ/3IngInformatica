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

/*!\brief Define los parámetro opcionales de tu programa.

*/
struct CLIParams
{
  CLIParams ()
    : fcorte(0.5), //Valores por defecto de los argumentos opcionales.
      space(0),
      interactivo(false),
      orden(2),
      ganancia(1.0),
      imagenInFlag(false),
      imagenOutFlag(false),
      maskFlag(false),
      imagenIn(""),
      imagenOut(""),
      mask(""),
      verbose(false)
    {}
  float fcorte;
  int space;
  bool interactivo;
  int orden;
  float ganancia;
  bool imagenInFlag;
  bool imagenOutFlag;
  bool maskFlag;
  string imagenIn;
  string imagenOut;
  string mask;
  bool verbose;
};

/*!\brief Muestra la ayuda del programa.  
  \arg[in] progname es el nombre del programa en la cli.
*/
static void
mostrarUso (const char * progname) throw ()
{
  std::cout << std::endl;
  std::cout << "Este programa sirve para realzar una imagen utilizando para ello una máscara de desenfoque" << std::endl;
  std::cout << "Uso: " << progname << " [-i] [-s <int>] [-r <float>] [-n <int>] [-g <float>] -f input.png -o output.png [-m masc.png]" << std::endl;
  std::cout << "Donde: " << std::endl;
  std::cout << "-h\t\tMuestra esta ayuda." << std::endl;
  std::cout << "-i\t\tActiva el modo interactivo." << std::endl;
  std::cout << "-s\t\tEspacio de color. Valor por defecto 0 (HSV)." << std::endl;
  std::cout << "-r\t\tFrecuencia de corte del filtro. Intervalo [0-1], defecto 0.5" << std::endl;
  std::cout << "-n\t\tOrden del filtro Butterworth paso baja. Intervalo [1-10], defecto 2" << std::endl;
  std::cout << "-g\t\tGanancia del realce. Intervalo [0.0-5.0], defecto 1.0" << std::endl;
  std::cout << "-f input.png\tImagen a tratar." << std::endl;
  std::cout << "-o output.png\tImagen de salida." << std::endl;
  std::cout << "[-m masc.png]\tMáscara opcional" << std::endl << std::endl;
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
  while ((opcion = getopt (argc, argv, "hn:s:ir:g:f:o:m:v")) != -1)
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

      case 's':
        params.space = atoi(optarg);
        break;

      case 'i':
        params.interactivo = true;
        break;
        
      case 'r':
      	params.fcorte = atof(optarg);
      	break;
      	
      case 'g':
      	params.ganancia = atof(optarg);
      	break;

        case 'f': params.imagenInFlag=true;
                  params.imagenIn=optarg;
                  break;

        case 'o':
                  params.imagenOutFlag=true;
                  params.imagenOut=optarg;
                  break;

        case 'm': params.maskFlag=true;
                  params.mask=optarg;
                  break;

        case 'v': params.verbose=true;
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

    std::cout << std::endl;
    std::cout << "Los parámetros opcionales son:" << std::endl;
    std::cout << "-i\t" << ((params.interactivo)?"True":"False") << std::endl;
    std::cout << "-s\t" << '\"' << params.space << '\"' << std::endl;
    std::cout << "-r\t" << '\"' << params.fcorte << '\"' << std::endl;
    std::cout << "-n\t" << '\"' << params.orden << '\"' << std::endl;
    std::cout << "-g\t" << '\"' << params.ganancia << '\"' << std::endl;

	//Inicialización de variables
	string nombre;
  string destino;
 	string mascara;
	Mat imagen, mask, imgOutput, filter, filterOutput, padded, canal, complex, imgGrayScale, temporal, img, spectroFilter;
	vector <Mat> canales; //Vector para almacenar canales
	int orden = params.orden;
  float fcorteW = params.fcorte;
  int fcorte = fcorteW*100;
  float gananciaW = params.ganancia;
  int ganancia = gananciaW*10;
  int canalColor;
	
  if(params.imagenInFlag){
	   imagen = imread(params.imagenIn,-1);
	}else{
    mostrarUso(argv[0]);
    exit(EXIT_FAILURE);
  }

  if (params.imagenOutFlag==true)
      destino=params.imagenOut;
  else
      destino="salida.png";

	if (!imagen.data)
	{
		cout << "Error al leer la imagen" << endl;
		exit(EXIT_FAILURE);
	}
	
	if (params.maskFlag)
	{
		mask = imread(params.mask, 0);
		
		if (!mask.data)
		{
			cout << "Error al leer la máscara" << endl;
			exit(EXIT_FAILURE);
		}
	}
	
  fcorteW=fcorteW*(sqrt(pow((imagen.rows),2.0)+pow((imagen.cols),2.0))/2);
  //maxfcorte=1.0*(sqrt(pow((imagen.rows),2.0)+pow((imagen.cols),2.0))/2);

    if (params.interactivo==true){

      //Crear las barras para el modo interactivo
    	namedWindow(params.imagenIn, WINDOW_AUTOSIZE);
      namedWindow(destino, WINDOW_AUTOSIZE);
      moveWindow("Imagen original",500,200);

      createTrackbar("Orden del filtro", destino, &orden, 10);
      createTrackbar("Frecuencia de corte", destino, &fcorte, 100);
      createTrackbar("Ganancia", destino, &ganancia, 50);
    }

        
	//Obtengo el tamaño óptimo para realizar la transformada de Fourier sobre la imagen
	  int M = getOptimalDFTSize(imagen.rows);
    int N = getOptimalDFTSize(imagen.cols);
     	
  while(true)
  {
      	//Convertimos la imagen al espacio de color indicado si la imagen tiene 3 canales
    if(params.interactivo==true){
          gananciaW = (ganancia/10.0);
          fcorteW = (fcorte/100.0);
          fcorteW=(fcorteW)*(sqrt(pow((imagen.rows),2.0)+pow((imagen.cols),2.0))/2);
     }

      	const int channels = imagen.channels();
      	if(channels == 3)
      	{
      			//En cada caso convierto al espacio de color indicado, divido la imagen en 3 canales y escojo el canal que contiene la intensidad para tratarlo
      			//cvtColor(imagen, imgGrayScale, CV_BGR2HSV);

                    switch(params.space){
                    
                      case 0:
                        cvtColor(imagen, imgGrayScale, CV_BGR2HSV);
                        canalColor=2;
                        break;
                      
                      case 1:
                        cvtColor(imagen, imgGrayScale, CV_BGR2HLS);
                        canalColor=1;
                        break;
                        
                      case 2:
                        cvtColor(imagen, imgGrayScale, CV_BGR2YCrCb);
                        canalColor=0;
                        break;
                        
                      case 3:
                        cvtColor(imagen, imgGrayScale, CV_BGR2Lab);
                        canalColor=0;
                        break;
                    }
      			split(imgGrayScale, canales);
              canales[canalColor].convertTo(temporal,CV_32F,1.0/255.0);
            copyMakeBorder(temporal, padded, 0, M - temporal.rows, 0, N - temporal.cols, BORDER_CONSTANT, Scalar::all(0)); //Le añado borde a la imagen
      	}
      	else if (channels == 1)
      	{
      		imagen.convertTo(img,CV_32F,1.0/255.0); //Convierto la imagen a flotante (de 1 a 255 valores posibles)
      		copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0)); //Le añado borde a la imagen
      	}
            
      //Configuracion de la imagen
        Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)}; //Configuro imagen para aplicar transformada de fourier, la paso a flotante
        merge(planes, 2, complex); //Creo la imagen compleja con la que voy a trabajar
      		
      //Transformada Fourier		
          	dft(complex, complex); 
            filter = complex.clone(); //Filtro
            Mat auxfilter = complex.clone(); 
            

      //Reordenacion, convolucion del dominio frecuencial, aplico filtro butterworth y reordenar
      	shiftDFT(complex); 
        create_butterworth_lowpass_filter(filter, fcorteW, orden); 
        create_butterworth_lowpass_filter(auxfilter, fcorteW, 0); 

        Mat auxComplex = complex.clone(); 	
  
        mulSpectrums(auxComplex, auxfilter, auxComplex, 0); 
        shiftDFT(auxComplex); 

        mulSpectrums(complex, filter, complex, 0); 
        shiftDFT(complex); 

        //Calculo el espectro
        spectroFilter = crearEspectro(complex);
        Mat spectroImg = crearEspectro(auxComplex);
        //Calculo de la inversa transformada y normalizar

        idft(complex, complex, DFT_SCALE);      
        split(complex, planes);
        normalize(planes[0], imgOutput, 0, 1, CV_MINMAX); //PLANO REAL
        split(filter, planes);
        normalize(planes[0], filterOutput, 0, 1, CV_MINMAX); //Normalizo el plano real
      	
      	Mat salida = img.clone(); //Copio la imagen de entrada en la de salida para que tenga las mismas características

      	//Aplicar Ganancia

      	//Ahora aplico la ganancia a cada píxel de la imagen en el canal indicado y teniendo en cuenta la máscara, en caso de haberla
            	if(channels == 3)
            	{  
              		canales[canalColor] = temporal.clone();


              	    	for(int i=0; i < imagen.rows; i++)
              	      		for(int j=0; j < imagen.cols; j++) 
              				      if(mask.empty() || mask.at<unsigned char>(i,j)!=0){
                                  canales[canalColor].at<float>(i,j)=(temporal.at<float>(i,j)*(gananciaW+1)-(imgOutput.at<float>(i,j)*gananciaW));
                             }

              		  canales[canalColor].convertTo(canales[canalColor], CV_8U, 255.0, 0.0); //Convierto la imagen a uchar para que se pueda visualizar de manera correcta

                  merge(canales, imgGrayScale); //Uno los canales
              	         switch(params.space){
      
                            case 0:
                              cvtColor(imgGrayScale, salida, CV_HSV2BGR);
                              break;
                            
                            case 1:
                              cvtColor(imgGrayScale, salida, CV_HLS2BGR);
                              break;
                              
                            case 2:
                              cvtColor(imgGrayScale, salida, CV_YCrCb2BGR);
                              break;
                              
                            case 3:
                              cvtColor(imgGrayScale, salida, CV_Lab2BGR);
                              break;
                          }

                   //cvtColor(imgGrayScale, salida, CV_HSV2BGR); //Deshago el cambio del espacio de color pasando la imagen a BGR
            	}
            	else //Si es en blanco y negro la imagen, debemos tener en cuenta los pixeles de la mascara (si la hay)
            	{
            		for(int i=0; i < imagen.rows; i++)
            			for(int j=0; j < imagen.cols; j++)			
            				if(mask.empty() || mask.at<unsigned char>(i,j)!=0)
            					salida.at<float>(i,j)=(img.at<float>(i,j)*(gananciaW+1)-(imgOutput.at<float>(i,j)*gananciaW));
      	         salida.convertTo(salida,CV_8U, 255.0, 0.0);
               }
  

          //Mostrar las imagenes
              if(params.verbose==true){
                imshow("Filtro", filterOutput);
                imshow("Espectro filtro", spectroFilter);
                imshow("Espectro imagen", spectroImg);
              }
            	imshow(destino, salida);
            	imshow(params.imagenIn, imagen);
            	imwrite(destino, salida);

              filterOutput.convertTo(filterOutput,CV_8U, 255.0, 0.0);
              imwrite("filtro.png", filterOutput);
            
          //Esperar para pulsar enter
            	char c = waitKey(10)&0xFF;
            	if (c == '\n')
      		      break;
	}

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
