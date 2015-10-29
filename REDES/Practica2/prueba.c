#include "bingo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bingo.h"
#include "registro.h"

#define MSG_SIZE 250

int main (){

	srand(time(NULL));
	char* buffer;
	char bufferAux[MSG_SIZE]="";
	int i,j;
	int ** carton;
	int ** carton2;

	carton = generaCarton();
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 9; ++j)
		{
			printf("( %d )", carton[i][j]);
		}
		printf("\n");
	}


	buffer = inttochar(carton);

	strcat(bufferAux, "CARTON ");
	strcat(bufferAux, buffer);

	fflush(stdout);

	printf("<%s>\n", bufferAux);

	buffer=NULL;

	buffer=cortarCadena(bufferAux, 250, ' ');

	strncpy(buffer, bufferAux+strlen(buffer)+1, MSG_SIZE);

	printf("%s\n", buffer);

	carton2 = chartoint(buffer);

	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 9; ++j)
		{
			printf("( %d )", carton2[i][j]);
		}
		printf("\n");
	}

	return 0;
}