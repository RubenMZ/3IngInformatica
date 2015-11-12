#include "bingo.h"

	int ** generaCarton(){
		int **carton;
		int num=0, aux=0, fila=0, i,j;

		carton =(int **)malloc(3*sizeof(int *));

		for ( i = 0; i < 3; ++i)
			carton[i]=(int *)malloc(9*sizeof(int));

		for ( i = 0; i < 3; ++i)
			for (j = 0; j< 5; ++j)
				carton[i][j]=0;

		while(num<15){
			aux=rand()%90+1;
			if(compruebaRepetido(carton, 3, 9, aux)==0){

				if (aux==90){
					if (carton[fila][8]==0)
						carton[fila][8]=aux;
				}else{
					if (carton[fila][aux/10]==0)
						carton[fila][aux/10]=aux;
				}

				if(compruebaRepetido(carton, 3, 9, aux)==1 && aux){
					//Quiere decir que lo ha metido, porque no estaba antes y era posicion valida =0
					num++;
					if (num%5==0 && num > 1)
						fila++;
				}
			}//if(compruebaRepetido(carton, 3, 9, aux)==0)	
		}//while(num<15)

		ordenarCarton(carton, 3, 9);
		return carton;
	}

	int compruebaRepetido(int ** carton, int fil, int col, int n){
		int i, j;

		for ( i = 0; i < fil; ++i)
		{
			for ( j = 0; j < col; ++j)
			{
				if(carton[i][j]==n)
					return 1;
			}
		}
		return 0;
	}

	void ordenarCarton(int ** carton, int fil, int col){
		int i, j;
		int aux;

		for (j = 0; j < col; ++j)
		{
			for (i = 1; i < fil; ++i)
			{				
				if(carton[i][j]!=0 && carton[i][j]<carton[i-1][j] && carton[i-1][j]!=0){
					aux=carton[i][j];
					carton[i][j]=carton[i-1][j];
					carton[i-1][j]=aux;
				}
				if (carton[0][j]!=0 && carton[2][j]!=0 && carton[2][j]<carton[0][j])
				{
					aux=carton[0][j];
					carton[0][j]=carton[2][j];
					carton[2][j]=aux;
				}
			}
		}
	}

 void mandarBola(Partida * partidas, int n){
    int i,j, bola;
    char buffer[MSG_SIZE];

    for (i = 0; i < n; ++i)
    {
        bola=rand()%90+1;
        if(partidas[i].comenzada==1 && partidas[i].numBolas!=90)
	        if (compruebaBola(partidas[i].bolas, partidas[i].numBolas, bola)==0)
	        {
	            partidas[i].bolas[partidas[i].numBolas]=bola;
	            partidas[i].numBolas++;
	            for (j = 0; j < partidas[i].numUsuarios; ++j)
	            {
	                bzero(buffer,sizeof(buffer));
	                sprintf(buffer,"NUMERO-OBTENIDO %d", bola);
	                send(partidas[i].usuarios[j],buffer,strlen(buffer),0);
	            }
	        }else
	        {
	            i--;
	        }

    }
 }

 	int compruebaBola(int * vector,int n, int bola){
		int i;
		for (i = 0; i < n; ++i)
		{
			if (vector[i]==bola)
			{

				return 1;
			}
		}

		return 0;
	}


 void mandarCarton(Partida * partida, Usuario usuarios[], int n){
 		char buffer[MSG_SIZE];
 		int i, j;
 		int ** carton;

 		for (i = 0; i < partida->numUsuarios; ++i)
 		{
 			bzero(buffer,sizeof(buffer));
 			strcpy(buffer, "CARTON ");
 			carton = generaCarton();
 			strcat(buffer, inttochar(carton));
 			send(partida->usuarios[i], buffer, strlen(buffer), 0);
 			for (j = 0; j < n; ++j)
 			{
 				if (usuarios[j].id==partida->usuarios[i])
 				{
 					usuarios[j].carton=carton;
 				}
 			}
 		}
 }

 int comprobarBingo(Usuario u, int opcion, Partida partida){

 	int i,j,k=0;
 	int lineas=0;

 	printf("hola\n");
 	if(opcion>partida.estado){

	 	for (i = 0; i < 3; ++i)
	 	{
	 		k=0;
	 		for (j=0; j < 9; ++j)
	 		{	
	 			if(compruebaBola(partida.bolas, partida.numBolas, u.carton[i][j])==1)
	 				k++;
	 		}
	 		if(k==5)
	 			lineas++;
	 	}

	 	printf("adios\n");

 	if(lineas>=opcion)
 		return 1;
 	else
 		return 0;

 	}else{
 		return -1;
 	}
 }


 	char * inttochar(int ** matriz){
 		char * cadena;
 		int i=0, j=0, k=0;
 		int aux;

 		cadena = (char * )malloc(MSG_SIZE*sizeof(char));

 		cadena[k]='|';
 		k++;
 		for (i = 0; i < 3; ++i)
 		{
 			for (j = 0; j < 9; ++j)
 			{
 				if(matriz[i][j]==0)
 					cadena[k]='X';
 				else{
 					if(matriz[i][j]/10>0){
 						aux=matriz[i][j]/10 +48;
 						cadena[k]=aux;
 						k++;
 						aux=matriz[i][j]%10 +48;
 						cadena[k]=aux;
 					}else{
 						cadena[k]=matriz[i][j]+48;
 					}
				}
 				k++;
 				if(j<8){
 					cadena[k]=',';
 					k++;
 				}
 			}
 			if(i<2){
 				cadena[k]=';';
 				k++;
 			}	
 		}
 		cadena[k]='|';
 		k++;
 		cadena[k]='\0';

 		return cadena;
 	}

	int ** chartoint(char * cadena){
		int ** carton;
		int i, j;
		char* caracter;
		char buffer[MSG_SIZE];

		carton =(int **)malloc(3*sizeof(int *));

		for ( i = 0; i < 3; ++i)
			carton[i]=(int *)malloc(9*sizeof(int));

		strncpy(buffer, cadena+1, MSG_SIZE);
		for (i = 0; i < 3; ++i)
		{
			for (j = 0; j < 9; ++j)
			{
				if(j<8){
					caracter=cortarCadena(buffer, 2,',');
					strncpy(buffer, buffer+strlen(caracter)+1, MSG_SIZE);
				}else{
					if(i<2){
						caracter=cortarCadena(buffer, 2,';');
						strncpy(buffer, buffer+strlen(caracter)+1, MSG_SIZE);
					}else{
						caracter=cortarCadena(buffer, 2,'|');
					}
				}
				if(*caracter=='X')
					carton[i][j]=0;
				else
					carton[i][j]=atoi(caracter);
			}

		}
		return carton;
	}

	void actualizarPartidas(int numPartidas, Partida partidas[]){
		int i;
		for (i = 0; i < numPartidas; ++i)
		{
			if (partidas[i].bandera!=0)
			{
				partidas[i].estado=partidas[i].bandera;
				partidas[i].bandera=0;
			}
		}

	}