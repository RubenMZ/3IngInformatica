#include "funciones.h"


void guardaFichero(const Mat &image, const vector< Point > & v, string fichero){
	
	ofstream file;

	file.open(fichero.c_str());

	for (unsigned int i = 0; i < v.size(); ++i)
	{
			file<<v[i].x<<" "<<image.cols-v[i].y<<endl;
	}

	file.close();
}


void getEstadisticos(const Mat &dst, const vector< Point > &v, Stat &datos){

	Stat prueba;
	Rect aux;
	float aux1;
	vector< Point > aux2;
	Point2f center;
	Point punto, puntoAux;
	Mat out, auxMat;

	aux= boundingRect(v);

	prueba.longitud=arcLength(v,true);
	prueba.area=contourArea(v,false);
	prueba.compacidad= prueba.area/ pow( prueba.longitud,2 );
	prueba.rectangulo= minAreaRect(v);

	if (prueba.rectangulo.size.width<prueba.rectangulo.size.height)
	{
		prueba.excentricidad = prueba.rectangulo.size.height /prueba.rectangulo.size.width;
	}else{
		prueba.excentricidad = prueba.rectangulo.size.width / prueba.rectangulo.size.height;
	}

	prueba.diametro= getDiametro(v);

	convexHull(v , aux2);
	aux1= contourArea(aux2);
	prueba.ocupacion=prueba.area/(aux.width*aux.height);
	prueba.ocupacion_convexa=aux1/(aux.width*aux.height);
	prueba.solidez = float(prueba.area)/aux1;

	getFourier(v, prueba.fourier);

	datos=prueba;
}


void getFourier(const vector< Point> &v, vector< float > &fourier)   
{   
	int M = getOptimalDFTSize(v.size());
	vector< Point2f > contorno;
	int aux=0;

	 for(int i = 0; i<M; i++){
	 	contorno.push_back(v[i%v.size()]);
	 }

	dft(contorno, contorno);
       
	for (int i = 0; i < contorno.size(); ++i)
	{
		fourier.push_back(sqrt( pow(contorno[i].x,2)+ pow(contorno[i].y,2) ));
		if(fourier[i]>aux)
			aux=fourier[i];
	}

 	for (int i = 0; i < contorno.size()-1; ++i)
 	{
 		fourier[i]=fourier[i+1];
 	}

	for (int i = 0; i < contorno.size(); ++i)
	{
		fourier[i]/=aux;
	}

} 


float getDiametro(const vector< Point > & v){
	float diametro=0;
	Point punto;

	for (int i = 0; i < v.size()-1; ++i)
	{
		punto = v[i];
		for (int j = i+1; j < v.size(); ++j)
		{
			float comp = sqrt( pow(punto.x-v[j].x,2)+pow(punto.y-v[j].y, 2) );
			if (comp>diametro)
			{
				diametro=comp;
			}
		}
	}

	return diametro;
}