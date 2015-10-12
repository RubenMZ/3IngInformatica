

/*!

  @file getStats.cc
  @brief Esto es un esqueleto de programa para usar en las prácticas de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o getStats getStats.cc `pkg-config opencv --cflags --libs`

*/

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <iostream>


//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

#include "stats.hpp"

using namespace std;
using namespace cv;

/*!
  \brief Define los parámetro opcionales de tu programa.

  Redefine esta clase en función de tus necesitados
*/

struct CLIParams
{
  CLIParams ()
    : iFlag(false),
      wFlag(false),
      mFlag(false),
      fFlag(false),
      imagen(""),
      mascara(""),
      x(0.0),
      y(0.0),
      w(0.0),
      h(0.0)
    {}
    bool iFlag;
    bool wFlag;
    bool mFlag;
    bool fFlag;
    string imagen;
    string mascara;
    double x;
    double y;
    double w;
    double h;

};


/*!\brief Muestra la ayuda del programa.  
  Redefinir en función de los parámetros utilizados realmente.
  \arg[in] programe es el nombre del programa en la cli.
*/
static void mostrarUso (const char * progname) throw ()
{
  std::cout << "Esto programa sirve para ...." << std::endl;
  std::cout << "Uso: " << progname << " [-h] [-w x1,y1,x2,y2] [-i] -v img1.png [-m masc.png]" << std::endl;
  std::cout << "Donde: " << std::endl;
  std::cout << "-h\tMuestra  esta la ayuda." << std::endl;
  std::cout << "-w x1,y1,x2,y2\tMete valores ROI" << std::endl;
  std::cout << "-i\tModo interactivo" << std::endl;
  std::cout << "-f img\tPermite especificar la foto o imagen." << std::endl;
  std::cout << "-m img\tPermite especificar la mascara" << std::endl;
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
  string cadena;
  string valor;

  while ((opcion = getopt (argc, argv, "hiw:f:m:")) != -1)
  {
    switch (opcion)
    {
      
      case 'h':
        mostrarUso(argv[0]);
        exit (EXIT_SUCCESS);
      break;
  
      case 'i':
        params.iFlag=true;
        cout<<"Sin implementar interactivo"<<endl;
        exit(EXIT_FAILURE);
      break;
  
      case 'w':
        params.wFlag = true;
        cadena = optarg;
          valor = cadena.substr(0, cadena.find(","));
          params.x = strtod(valor.c_str(),NULL);
          
          cadena.erase(0, cadena.find(",")+1);
          valor = cadena.substr(0, cadena.find(","));
          params.y = strtod(valor.c_str(),NULL);

          cadena.erase(0, cadena.find(",") + 1);
          valor = cadena.substr(0, cadena.find(","));
          params.w = strtod(valor.c_str(),NULL);
          
          cadena.erase(0, cadena.find(",") + 1);
          valor = cadena.substr(0, cadena.find(","));         
          params.h = strtod(valor.c_str(),NULL);

      break;

      case 'm':
        params.mFlag = true;
        params.mascara=optarg;
      break;
  
      case 'f':
        params.fFlag = true;
        params.imagen=optarg;
      break;
  
  
      case '?': // en caso de error getopt devuelve el caracter ?
  
              if (isprint (optopt)){
                  std::cerr << "Error: Opción desconocida \'" << optopt<< "\'" << std::endl;
                  mostrarUso(argv[0]);
              }else{
                  std::cerr << "Error: Caracter de opcion desconocido \'x" << std::hex << optopt<< "\'" << std::endl;
                  mostrarUso(argv[0]);    
                  exit (EXIT_FAILURE);
              }
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

/*  if(argc!=2&&argc!=3){
      cout<<"Error argumentos: <programa><nombre imag>"<<endl;
      exit(-1);
  }
*/  
  try {    
    CLIParams params;

    parseCLI(argc, argv, params);

  //LEEMOS LA IMAGEN
 
    std::vector<Mat> capas;
    Mat mtx;
    Mat mask;
    Mat submask;
    Mat submtx;

    if(params.fFlag==true){
      mtx= imread(params.imagen,-1);
    }else{
      cout<<"Comandos para imagen incorrectos"<<endl;
      mostrarUso(argv[0]);
      exit(EXIT_FAILURE);
    }

    
    if(params.mFlag==true)
      mask=imread(params.mascara,0);

     if(params.wFlag==true){
      //Hacemos el roi manual
      //Y creamos las subimagenes
      if(params.x<0 || params.y<0 || params.w <0 || params.h<0 || params.x>mtx.cols || params.y>mtx.rows || params.x+params.w>mtx.cols || params.y+params.h>mtx.rows){

        cout << "No concuerdan los pixeles" << endl;
        exit(-1);
      }else{
          cv::Rect roi1(params.x,params.y,params.w,params.h);
          submtx = mtx(roi1);
          if(params.mFlag==true){
            cv::Rect roi2(params.x,params.y,params.w,params.h);
            submask = mask(roi2);
          }
      }
    }

    imshow(params.imagen, mtx);
    waitKey();

    imshow(params.imagen, mask);
    waitKey();

    if(params.wFlag==true)
      split(submtx, capas);
    else
      split(mtx, capas);

    cout<<"Canales: "<<mtx.channels()<<endl;
    cout<<"Ancho: "<<mtx.cols<<endl;
    cout<<"Alto: "<<mtx.rows<<endl;

 
    if( (mtx.cols == mask.cols && mtx.rows ==mask.rows) || mask.empty() )
      for (unsigned int i = 0; i < capas.size(); ++i)
      {
        cout<< "CANAL "<<i<<endl;
        cout<< "----------"<<endl;
        Stats results;
        if(params.wFlag==true)
          results.calculateStats(capas[i], submask, submtx.cols, submtx.rows);
        else
          results.calculateStats(capas[i], mask, mtx.cols, mtx.rows);
        cout<<"min. v= "<< results.getMin()<<endl;
        cout<<"max. v= "<< results.getMax()<<endl;
        cout<<"media= "<< results.getMedia()<<endl;
        cout<<"varianza= "<< results.getVarianza()<<endl;
        cout<<"suma= "<< results.getSuma()<<endl;
        cout<<"suma de cuadrados= "<< results.getSumaCuadrados()<<endl;
        cout<<"Area positiva= "<< results.getAreaPos()<<endl;
        cout<<"Area negativa= "<< results.getAreaNeg()<<endl;
        cout<<"Num ceros= "<< results.getCeros()<<endl;
        cout<<"Coef. asimetría= "<< results.getCoefAsim()<<endl;
    }
    else
      cout<<"No cuadran las matrices de..."<<argv[1]<<" y "<<argv[2]<<endl;

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}