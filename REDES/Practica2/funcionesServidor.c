#include "funcionesServidor.h"


void salirCliente(int socket, fd_set * readfds, int * numUsuarios, Usuario usuarios[], int numPartidas, Partida partidas[]){
  
    char buffer[MSG_SIZE];
    int j;
    int i;
    
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de clientes
    for (j = 0; j < (*numUsuarios) - 1; j++)
        if (usuarios[j].id == socket)
            break;
    for (; j < (*numUsuarios) - 1; j++)
        (usuarios[j] = usuarios[j+1]);
    
    (*numUsuarios)--;

    for (i = 0; i < numPartidas; ++i)
    {
        for (j = 0; j < partidas[i].numUsuarios; ++j){
            if(socket == partidas[i].usuarios[j]){
              for (;j < partidas[i].numUsuarios -1; ++j)
                  partidas[i].usuarios[j]=partidas[i].usuarios[j+1];
              partidas[i].numUsuarios--;
              break;
            }    
        }
    }
    
    printf("Desconexión  del cliente: %d\n", socket);
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);
    
    for(j=0; j<(*numUsuarios); j++)
        if(usuarios[j].id != socket)
            send(usuarios[j].id,buffer,strlen(buffer),0);
}


void salirPartida(int socket, int numPartidas, Partida partidas[]){
  
    char buffer[MSG_SIZE];
    int j;
    int i;
    int k;

    for (i = 0; i < numPartidas; ++i)
    {
        for (j = 0; j < partidas[i].numUsuarios; ++j){
            if(socket == partidas[i].usuarios[j]){
              for (;j < partidas[i].numUsuarios -1; ++j)
                  partidas[i].usuarios[j]=partidas[i].usuarios[j+1];
              partidas[i].numUsuarios--;
              break;
            }    
        }
    }
    printf("Salida de partida del cliente: %d\n",socket);
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Salida del cliente: %d\n",socket);

    for (i=0; i < numPartidas; ++i){
      for(j=0; j<partidas[i].numUsuarios; j++){
                send(partidas[i].usuarios[j],buffer,strlen(buffer),0);
        }
    }

}


void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);
    
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
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
        if(strcmp(cabecera1, "SALIR-PARTIDA")==0 || strcmp(cabecera2, "SALIR-PARTIDA")==0)
          opcion=8;

       	return opcion;
	}

 void continuarJugando(Usuario u, int estado){
        switch(estado){
          case 0: send(u.id, "+ERR. La partida no ha empezado", sizeof("+ERR. La partida no ha empezado"),0);
                break;

          case 1: send(u.id, "+ERR. Ya se ha cantado linea", sizeof("+ERR. Ya se ha cantado linea"),0);
                break;

          case 2: send(u.id, "+ERR. Ya se han cantado dos lineas", sizeof("+ERR. Ya se han cantado dos lineas"),0);
                break;

          case 3: send(u.id, "+ERR. Ya se ha cantando bingo", sizeof("+ERR. Ya se ha cantando bingo"),0);
                break;

        }
 }

