#include "funcionesServidor.h"


void salirCliente(int socket, fd_set * readfds, int * numUsuarios, Usuario usuarios[]){
  
    char buffer[MSG_SIZE];
    int j;
    
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de clientes
    for (j = 4; j < (*numUsuarios) - 1; j++)
        if (usuarios[j].id == socket)
            break;
    for (; j < (*numUsuarios) - 1; j++)
        (usuarios[j] = usuarios[j+1]);
    
    (*numUsuarios)--;
    
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);
    
    for(j=4; j<(*numUsuarios); j++)
        if(usuarios[j].id != socket)
            send(usuarios[j].id,buffer,strlen(buffer),0);


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

       	return opcion;
	}

