/*!

    g++ -Wall -o unsharp unsharp.cc funciones.cc `pkg-config opencv --cflags --libs`

*/

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

static int parseCLI (int argc, char* const* argv, CLIParams& params) throw ()
{
  
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
	
      case '?': 
	
              	if (isprint (optopt))
              	  std::cerr << "Error: Opción desconocida \'" << optopt
              	    << "\'" << std::endl;
              	else
              	  std::cerr << "Error: Caracter de opcion desconocido \'x" << std::hex << optopt
              	    << "\'" << std::endl;
              	mostrarUso(argv[0]);    
              	exit (EXIT_FAILURE);
              	
                    default:
              	std::cerr << "Error: línea de comandos errónea." << std::endl;
              	mostrarUso(argv[0]);
              	exit(EXIT_FAILURE);	
    }  
    
  }
  return optind;
}



int main (int argc, char* const* argv)
{
  
  try {    
    CLIParams params;

    parseCLI(argc, argv, params);

    cout << endl;
    cout << "Los parámetros opcionales son:" << endl;
    cout << "-i\t" << ((params.interactivo)?"True":"False") << endl;
    cout << "-s\t" << '\"' << params.space << '\"' << endl;
    cout << "-r\t" << '\"' << params.fcorte << '\"' << endl;
    cout << "-n\t" << '\"' << params.orden << '\"' << endl;
    cout << "-g\t" << '\"' << params.ganancia << '\"' << endl;

	//VARIABLES
	string nombre;
  string destino;
 	string mascara;
	Mat imagen, mask, imagenSalida, filtro, filtroSalida, padded, canal, imagenCompleja, imgGrayScale, temporal, img, spectroFiltro;
	vector <Mat> canales;
	int orden = params.orden;
  float fcorteW = params.fcorte;
  int fcorte = fcorteW*100;
  float gananciaW = params.ganancia;
  int ganancia = gananciaW*10;
  int canalColor;

     if(gananciaW>5.0 || gananciaW<0.0 || orden>10 || orden <0 || fcorteW > 1.0 || fcorteW < 0.0|| params.space > 3 || params.space<0 ){
      mostrarUso(argv[0]);
      exit(EXIT_FAILURE);
     }
	
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

    if (params.interactivo==true){
    	namedWindow(params.imagenIn, WINDOW_AUTOSIZE);
      namedWindow(destino, WINDOW_AUTOSIZE);

      createTrackbar("Orden del filtro", destino, &orden, 10);
      createTrackbar("Frecuencia de corte", destino, &fcorte, 100);
      createTrackbar("Ganancia", destino, &ganancia, 50);
    }

	  int M = getOptimalDFTSize(imagen.rows);
    int N = getOptimalDFTSize(imagen.cols);
     	
  while(true)
  {
    if(params.interactivo==true){
          gananciaW = (ganancia/10.0);
          fcorteW = (fcorte/100.0);
          fcorteW=(fcorteW)*(sqrt(pow((imagen.rows),2.0)+pow((imagen.cols),2.0))/2);
     }
      	const int channels = imagen.channels();
      	if(channels == 3)
      	{
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
            copyMakeBorder(temporal, padded, 0, M - temporal.rows, 0, N - temporal.cols, BORDER_CONSTANT, Scalar::all(0)); 
      	}
      	else if (channels == 1)
      	{
      		imagen.convertTo(img,CV_32F,1.0/255.0);
      		copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));
      	}
            

        Mat planos[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
        merge(planos, 2, imagenCompleja);  

        dft(imagenCompleja, imagenCompleja); 
        filtro = imagenCompleja.clone();
        Mat auxfiltro = imagenCompleja.clone();     


      	centrarDFT(imagenCompleja); 
        crearFiltroButterworth(filtro, fcorteW, orden); 
        crearFiltroButterworth(auxfiltro, fcorteW, 0); 

        Mat auximagenCompleja = imagenCompleja.clone(); 	
  
        mulSpectrums(auximagenCompleja, auxfiltro, auximagenCompleja, 0); 
        centrarDFT(auximagenCompleja); 

        mulSpectrums(imagenCompleja, filtro, imagenCompleja, 0); 
        centrarDFT(imagenCompleja); 

        spectroFiltro = crearEspectro(imagenCompleja);
        Mat spectroImg = crearEspectro(auximagenCompleja);

        idft(imagenCompleja, imagenCompleja, DFT_SCALE);      
        split(imagenCompleja, planos);
        normalize(planos[0], imagenSalida, 0, 1, CV_MINMAX);
        split(filtro, planos);
        normalize(planos[0], filtroSalida, 0, 1, CV_MINMAX); 
      	
      	Mat salida = img.clone(); 

            	if(channels == 3)
            	{  
              		canales[canalColor] = temporal.clone();
              	    	for(int i=0; i < imagen.rows; i++)
              	      		for(int j=0; j < imagen.cols; j++) 
              				      if(mask.empty() || mask.at<unsigned char>(i,j)!=0){
                                  canales[canalColor].at<float>(i,j)=(temporal.at<float>(i,j)*(gananciaW+1)-(imagenSalida.at<float>(i,j)*gananciaW));
                             }
              		canales[canalColor].convertTo(canales[canalColor], CV_8U, 255.0, 0.0); 
                  merge(canales, imgGrayScale); 
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
            	}
            	else
            	{
            		for(int i=0; i < imagen.rows; i++)
            			for(int j=0; j < imagen.cols; j++)			
            				if(mask.empty() || mask.at<unsigned char>(i,j)!=0)
            					salida.at<float>(i,j)=(img.at<float>(i,j)*(gananciaW+1)-(imagenSalida.at<float>(i,j)*gananciaW));
      	         salida.convertTo(salida,CV_8U, 255.0, 0.0);
               }
  
              if(params.verbose==true){
                imshow("Filtro", filtroSalida);
                imshow("Espectro filtro", spectroFiltro);
                imshow("Espectro imagen", spectroImg);
              }
            	imshow(destino, salida);
            	imshow(params.imagenIn, imagen);
            	imwrite(destino, salida);

              filtroSalida.convertTo(filtroSalida,CV_8U, 255.0, 0.0);
              imwrite("filtro.png", filtroSalida);

            	char c = waitKey(10)&0xFF;
            	if (c == '\n')
      		      break;
	}

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  return 0;
}
