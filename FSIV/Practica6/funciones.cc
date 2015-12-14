#include "funciones.h"


void guardaFichero(const Mat &image, const vector< vector<Point> > & v, string fichero){
	
	ofstream file;

	file.open(fichero.c_str());

	for (unsigned int i = 0; i < v.size(); ++i)
	{
		for (unsigned int j = 0; j < v[i].size(); ++j)
		{
			file<<v[i][j].x<<" "<<image.cols-v[i][j].y<<endl;
		}
		file<<" "<<endl;
	}

	file.close();
}


void getEstadisticos(const vector< Point > &v, Stat &datos){

	Stat prueba;
	prueba.longitud=0;
	prueba.area=0;
	Point pixelAux;

	for (unsigned int i = 1; i < v.size(); ++i)
	{
		pixelAux=v[i];
		if(v[i].x==v[i-1].x || v[i].y == v[i-1].y)
			prueba.longitud+=1;
		else
			prueba.longitud+=sqrt(2);

		for (int j = 0; j < v.size(); ++j)
		{
			if(pixelAux.x==v[j].x)
				prueba.area+=abs(pixelAux.y-v[j].y);
		}
	}

	if (v[0].x == v[v.size()-1].x || v[0].y == v[v.size()-1].y)
	{
		prueba.longitud+=1;
	}else{
		prueba.longitud+=sqrt(2);
	}
	datos=prueba;
}