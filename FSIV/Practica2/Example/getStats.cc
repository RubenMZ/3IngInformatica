/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o getStats getStats.cc `pkg-config opencv --cflags --libs`

*/

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include "getStats.h"
#include <cmath>
#include <vector>
#include <cstdio>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp>
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



int main (int argc, char* const* argv){
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

    /*Ahora toca que tu rellenes con lo que hay que hacer ...*/

//Creo la matriz A donde ira la imagen

Mat A;

//Cargo la imagen


A=imread(argv[argopt],-1);


if(A.empty())
	cout<<"Error, esta vacio"<<endl;
else
	cout<<"Bien cargada"<<endl;		
 
//Muestro la imagen
imshow("IMAGEN", A);
waitKey();  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Redimension de la imagen por si se ha usado el Área de Interés

if(strcmp("",params.cadena)!=0)
	{
		int x;
		int y;
		int wide;
		int height;

		sscanf(params.cadena, "%i,%i,%i,%i", &x, &y, &wide, &height);

//Se obtienen los datos necesarios para calcular el ROI en base a la cadena introducida

if(wide > A.cols-x || height > A.rows-y)
		{
			cout << "Error: ROI especificado fuera de rango de la imagen" << endl;
			exit(EXIT_FAILURE);
		}

		Mat aux(A,Rect(x,y,wide,height));
		A = aux;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int canales;
int ancho;
int alto;

vector<Mat> capas;

//Uso del SPLIT

split(A,capas);
   
canales=capas.size();
ancho=A.cols;
alto=A.rows;

//Declaracion de variables utiles	

//Vector de estructuras

vector<Stat> Stats(canales);
//Con Mascara
if(argc>=3)
{

   Mat Mascara;
   Mascara= imread(argv[argopt+1],0);
   
   if(!Mascara.data)
   {
	cout<<"Error al leer la mascara"<<endl;
	exit(-1);
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //Redimensionado de la Mascara de acuerdo al ROI
   if(strcmp("",params.cadena)!=0)
			{
				int x;
				int y;
				int wide;
				int height;

				sscanf(params.cadena, "%i,%i,%i,%i", &x, &y, &wide, &height); //Obtenemos los datos necesarios para calcular el ROI a partir de la cadena introducida por línea de comandos

				if(wide > Mascara.cols-x || height > Mascara.rows-y)
				{
					cout << "Error: ROI especificado fuera de rango de la imagen" << endl;
					exit(EXIT_FAILURE);
				}

				Mat aux(Mascara,Rect(x,y,wide,height));
				Mascara = aux;
			}
			
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
for(int i=0;i<canales;i++)
{
	Stats[i].min=256.0;
	Stats[i].max=0.0;
	Stats[i].media=0.0;
	Stats[i].varianza=0.0;
	Stats[i].suma=0.0;
	Stats[i].suma_de_cuadrados=0.0;
	Stats[i].area_positiva=0.0;
	Stats[i].area_negativa=0.0;
	Stats[i].num_ceros=0.0;
	Stats[i].coef_asimetria=0.0;
	Stats[i].desviacion_tipica=0.0;
	float cont=0;
	for(int k=0;k<alto;k++)
		{
		for(int j=0;j<ancho;j++)
			{
		
			//capas
			const float aux=capas[i].at <uchar> (k,j);
			const float auxM=Mascara.at <uchar> (k,j);
			if(auxM!=0)
			{
			  //Minimo y maximo
		
			if(aux<Stats[i].min)
				Stats[i].min=aux;
			if(aux>Stats[i].max)
				Stats[i].max=aux;
		
			//Comprobar el numero de ceros
		
			if(aux==0)
				Stats[i].num_ceros++;
			
			//Areas
		
			if(aux>=0)
				Stats[i].area_positiva=Stats[i].area_positiva+aux;
			else
				Stats[i].area_negativa=Stats[i].area_negativa+aux;
		
			
			//Sumatorios
			Stats[i].suma=Stats[i].suma+aux;
			Stats[i].suma_de_cuadrados=Stats[i].suma_de_cuadrados+pow(aux,2);
			
			cont++;
			}
		}
		}
		//Media
		float filas=A.rows;
		float columnas=A.cols;
		Stats[i].media=Stats[i].suma/cont++;
		
		//varianza
		
		Stats[i].varianza=(Stats[i].suma_de_cuadrados)/((filas*columnas)-pow(Stats[i].media,2));
		Stats[i].desviacion_tipica=sqrt(Stats[i].varianza);
		
		//Coeficiente de Asimetria
		Stats[i].coef_asimetria=((Stats[i].suma_de_cuadrados*Stats[i].suma)*pow(Stats[i].media,3))/((filas*columnas)*pow(sqrt(Stats[i].varianza),3));
		 
}  }

else
for(int i=0;i<canales;i++)
{
	Stats[i].min=256.0;
	Stats[i].max=0.0;
	Stats[i].media=0.0;
	Stats[i].varianza=0.0;
	Stats[i].suma=0.0;
	Stats[i].suma_de_cuadrados=0.0;
	Stats[i].area_positiva=0.0;
	Stats[i].area_negativa=0.0;
	Stats[i].num_ceros=0.0;
	Stats[i].coef_asimetria=0.0;
	Stats[i].desviacion_tipica=0.0;
	
	for(int k=0;k<alto;k++)
		{
		for(int j=0;j<ancho;j++)
			{
		
			//capas
			const float aux=capas[i].at <uchar> (k,j);
			
			  //Minimo y maximo
		
			if(aux<Stats[i].min)
				Stats[i].min=aux;
			if(aux>Stats[i].max)
				Stats[i].max=aux;
		
			//Comprobar el numero de ceros
		
			if(aux==0)
				Stats[i].num_ceros++;
			
			//Areas
		
			if(aux>=0)
				Stats[i].area_positiva=Stats[i].area_positiva+aux;
			else
				Stats[i].area_negativa=Stats[i].area_negativa+aux;
		
			
			//Sumatorios
			Stats[i].suma=Stats[i].suma+aux;
			Stats[i].suma_de_cuadrados=Stats[i].suma_de_cuadrados+pow(aux,2);
			}
		}

		//Media
		float filas=A.rows;
		float columnas=A.cols;
		Stats[i].media=Stats[i].suma/(filas*columnas);
		
		//varianza
		
		Stats[i].varianza=(Stats[i].suma_de_cuadrados)/((filas*columnas)-pow(Stats[i].media,2));
		Stats[i].desviacion_tipica=sqrt(Stats[i].varianza);
		
		//Coeficiente de Asimetria
		/*
		long sumaCoef = 0;
		long elementos =0
		for(int x=0; x < capas[i].rows; x++)
			for(int y=0; y <capas[i].cols; y++)
			{
				int valor = (capas[i]).at<uchar>(x,y);

				sumaCoef = sumaCoef+ pow((Stats[i].media),3);
			}
		Stats[i].coef_asimetria= sumaCoef/(elementos*pow(Stats[i].desviacion_tipica,3));
		 */
}



	//Impresion de resultados	
	cout<<"RESULTADOS"<<endl;
	cout<<"-----------------------------------------------------------"<<endl;
	cout<<"Capas --->" << A.channels()<<endl;
	cout<<"Ancho --->" <<A.cols<<endl;
	cout<<"Alto --->"<<A.rows<<endl;
	cout<<"-----------------------------------------------------------"<<endl;
	
		for(int i=0;i<canales;i++)	
			{	
			cout<<"CAPA Nº"<<i<<endl;
			cout<<"El valor minimo es ->"<<Stats[i].min<<endl;
			cout<<"El valor maximo es ->"<<Stats[i].max<<endl;
			cout<<"La media es -->"<<Stats[i].media<<endl;
			cout<<"La varianza es -->"<<Stats[i].varianza<<endl;
			cout<<"La suma es -->"<<Stats[i].suma<<endl;
			cout<<"La suma de cuadrados es -->"<<Stats[i].suma_de_cuadrados<<endl;
			cout<<"El area positiva es -->"<<Stats[i].area_positiva<<endl;
			cout<<"El area negatia es -->"<<Stats[i].area_negativa<<endl;
			cout<<"El numero de ceros es -->"<<Stats[i].num_ceros<<endl;
			cout<<"La desviaciacion tipica es -->"<<Stats[i].desviacion_tipica<<endl;
			cout<<"-----------------------------------------------------------"<<endl;
			//cout<<"El coeficiente de asimetria es -->"<<Stats[i].coef_asimetria<<endl;
			}
}	
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}		
