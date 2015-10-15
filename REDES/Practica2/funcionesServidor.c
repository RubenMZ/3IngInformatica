#include "funcionesServidor.h"

void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]){
  
    char buffer[MSG_SIZE];
    int j;
    
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j] == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j] = arrayClientes[j+1]);
    
    (*numClientes)--;
    
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);
    
    for(j=0; j<(*numClientes); j++)
        if(arrayClientes[j] != socket)
            send(arrayClientes[j],buffer,strlen(buffer),0);


}


void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);
    
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}


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

	int aceptaUsuario(char * nombre){
		FILE* f;
		char linea[MSG_SIZE];
		char * nombre2;

		if ((f=fopen("usuarios.txt", "r"))==NULL)
		{
			printf("No se puede abrir el fichero.\n");
			exit(-1);
		}

		while(fgets(linea, MSG_SIZE, f)!=NULL){
			linea[strlen(linea)-1]='\0';
			nombre2 = cortarCadena(linea, MSG_SIZE, ' ');
			if (strcmp(nombre2,nombre)==0)
				return 1;
		}
		close(f);
		return 0;
	}

	char * cortarCadena(char * cadena, int n, char c){
		int i=0;
		char * cortada;

		cortada = (char * )malloc(MSG_SIZE*sizeof(char));

		while(i<n && cadena[i]!=c){
			cortada[i]=cadena[i];
			++i;
		}
		return cortada;
	}

	int aceptaPass(char * nombre, char* pass){
		FILE* f;
		char linea[MSG_SIZE];
		char * nombre2;
		char * pass2;

		pass2 = (char * )malloc(MSG_SIZE*sizeof(char));

		if ((f=fopen("usuarios.txt", "r"))==NULL)
		{
			printf("No se puede abrir el fichero.\n");
			exit(-1);
		}

		while(fgets(linea, MSG_SIZE, f)!=NULL){
			linea[strlen(linea)-1]='\0';
			nombre2 = cortarCadena(linea, MSG_SIZE, ' ');
			strncpy(pass2, linea+strlen(nombre2)+1, MSG_SIZE);
			if (strcmp(nombre2,nombre)==0 && strcmp(pass2,pass)==0)
			{
				return 1;
			}
		}
		close(f);
		return 0;
	}


	int registrarUsuario(char * nombre, char * pass){
		FILE* f;
		char linea[MSG_SIZE];

		if ((f=fopen("usuarios.txt", "a"))==NULL)
		{
			printf("No se puede abrir el fichero.\n");
			exit(-1);
		}

		fprintf(f, "%s %s\n", nombre, pass);
		close(f);
		return 0;
	}

	int comprobarOpcion(char * cabecera1, char * cabecera2){
		int opcion=0;

		if(strcmp(cabecera1, "REGISTER")==0 || strcmp(cabecera2, "REGISTER")==0)
       	    opcion=1;
       	if(strcmp(cabecera1, "USUARIO")==0 || strcmp(cabecera2, "USUARIO")==0)
       	    opcion=2;
       	if(strcmp(cabecera1, "PASSWORD")==0 || strcmp(cabecera2, "PASSWORD")==0)
       	    opcion=3;
       	if(strcmp(cabecera1, "INICIAR-PARTIDA")==0 || strcmp(cabecera2, "INICIAR-PARTIDA")==0)
       		opcion=4;
       	if(strcmp(cabecera1, "UNA-LINEA")==0 || strcmp(cabecera2, "UNA-LINEA")==0)
       		opcion=5;
       	if(strcmp(cabecera1, "DOS-LINEAS")==0 || strcmp(cabecera2, "DOS-LINEAS")==0)
       		opcion=6;
       	if(strcmp(cabecera1, "BINGO")==0 || strcmp(cabecera2, "BINGO")==0)
       		opcion=7;

       	return opcion;
	}