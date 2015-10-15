/*!

    g++ -Wall -o ecuImg ecuImg.cc funciones.cc `pkg-config opencv --cflags --libs`

	José Enrique Ortega Ortega OPC2
*/


#include "ecuImg.hpp"

//Caclculo el histograma sin la mascara o con la mascara si la hubiera
void calcularHistograma(vector <long> &histograma, const Mat imagen, const Mat mask)
{

	//La inicializo a 0
	for(size_t i=0; i<histograma.size();i++)
		histograma[i]=0;
		
		
	//Trabajo con 1 o con 3 canales
	switch(imagen.channels())
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
void normalizarHistograma(vector <long> &histograma)
{	
	int pixels = histograma[0]; //Contador de píxeles totales que comienza con el número de píxeles que hay en histograma[0]
	
	//Calculamos el histograma acumulado
	for(unsigned int i = 1; i < histograma.size(); ++i)
	{
		pixels = pixels + histograma[i];
		histograma[i] = histograma[i] + histograma[i-1];
	}

	//Normalizamos el histograma acumulado
	for(unsigned int j = 0; j < histograma.size(); ++j)
		histograma[j] = 255*histograma[j] /pixels; //Podemos realizar también la operación de manera vectorial con histograma = 255*histograma;
}

//Ecualización de la imagen utilizando para ello el histograma por normalizacion
void ecualizacion(Mat &imagen, vector<long> histograma, Mat mask)
{

	switch(imagen.channels())
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

//MIRAR https://es.scribd.com/doc/94351721/2/Histograma-y-Ecualizacion-del-Histograma
