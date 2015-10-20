/*!

    g++ -Wall -o ecuImg ecuImg.cc funciones.cc `pkg-config opencv --cflags --libs`
*/


#include "funciones.hpp"

//Caclculo el histograma sin la mascara o con la mascara si la hubiera
void crearHistograma(vector <double> &histograma, const Mat imagen, const Mat mask)
{
	int valor;

	//La inicializo a 0
	for(size_t i=0; i<histograma.size();i++)
		histograma[i]=0;
			
	//Trabajo con 1 o con 3 canales
		for(int x=0; x<imagen.rows; x++)
			for(int y=0; y<imagen.cols; y++){
				if(imagen.channels()==1)
					valor = imagen.at<uchar>(x,y);
				else
					valor = imagen.at<Vec3b>(x,y)[2];
				if(mask.data)
				{
					if(mask.at<uchar>(x,y)!= 0)
					{
						histograma[valor]++;
					}
				}
				else
				{
					histograma[valor]++;
				}
			}
	
}

//Función que realiza la ecualización del histograma obteniendo primero el histograma acumulativo y dividiéndolo posteriormente por el número de píxeles totales
void normalizar(vector <double> &histograma)
{	
	int pixels = histograma[0]; //Pixeles totales
	
	//Calculamos el histograma acumulado
	for(unsigned int i = 1; i < histograma.size(); ++i)
	{
		pixels = pixels + histograma[i];
		histograma[i] = histograma[i] + histograma[i-1];
	}

	//Normalizamos el histograma acumulado
	for(unsigned int j = 0; j < histograma.size(); ++j){
		if(pixels!=0)
			histograma[j] = 255*histograma[j] /pixels;
		else
			histograma[j] = 255*histograma[j];
	}
}

//Ecualización de la imagen utilizando para ello el histograma por normalizacion
void ecualizar(vector<double> histograma, Mat &imagen, Mat mask)
{

	if(imagen.channels()==1){
		for(int x=0; x<imagen.rows; x++)
			for(int y=0; y<imagen.cols; y++)
				if(mask.data)
				{
					if(mask.at<uchar>(x,y) != 0)
					{
						int pixel = imagen.at<uchar>(x,y);
						imagen.at<uchar>(x,y) = histograma[pixel];
					}
				}
				else
				{
					int pixel = imagen.at<uchar>(x,y);
					imagen.at<uchar>(x,y) = histograma[pixel];
				}
		}
	if(imagen.channels()==3){
		for(int x=0; x<imagen.rows; x++)
			for(int y=0; y<imagen.cols; y++)
				if(mask.data)
				{
					if(mask.at<uchar>(x,y) != 0)
					{
						int pixel = imagen.at<Vec3b>(x,y)[2];
						imagen.at<Vec3b>(x,y)[2] = histograma[pixel];
					}
				}
				else
				{
					int pixel = imagen.at<Vec3b>(x,y)[2];
					imagen.at<Vec3b>(x,y)[2] = histograma[pixel];
				}
		}
	
}

