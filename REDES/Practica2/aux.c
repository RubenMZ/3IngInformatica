#include "funcionesServidor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	int** matriz;
	int i,j;
	srand(time(NULL));
	char nombre[100];
	char pass[100];

	matriz=generaCarton();

	for ( i = 0; i < 3; ++i)
	{
		printf("|\t");
		for (j = 0; j < 9; ++j)
		{
			printf(" %d \t",matriz[i][j] );
		}
		printf("|\n");
	}

	printf("Introduce tu user:  ");
	gets(nombre);
	printf("Introduce pass: ");
	gets(pass);

	if (aceptaUsuario(nombre)==1)
	{
		printf("Se acepta Usuario :)\n");
	}else{
		printf("Pos no\n");
	}

	if (aceptaPass(nombre, pass)==1)
	{
		printf("Se acepta Pass :)\n");
	}else{
		printf("Pos no\n");
	}

	//registrarUsuario(nombre, pass);

	return 0;
}