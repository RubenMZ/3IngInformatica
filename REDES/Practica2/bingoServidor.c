#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "funcionesServidor.h"
#include "registro.h"
#include "estructuras.h"
#include "bingo.h"

#define MSG_SIZE 250
#define MAX_CLIENTS 40


/*
 * El servidor ofrece el servicio de bingo
 */

void main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    int numUsuariosConectados = 0;
    int numUsuariosJugando = 0;
    int numPartidas=0;

    Usuario usuarios[MAX_CLIENTS];
    Partida partidas[10];
    char* cabecera1, *cabecera2, argumento[MSG_SIZE];
    int opcion;
    //contadores
    int i,j,k;
	int recibidos;
    char identificador[MSG_SIZE];
    
    int on, ret;

    srand(time(NULL));

    
    struct timeval timeout;

    
    //Inicializar las partidas

    for (i = 0; i < 10; ++i)
    {
        partidas[i].comenzada=0;
        partidas[i].numUsuarios=0;
        partidas[i].numBolas=0;
    }
	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}
    
    // Activaremos una propiedad del socket que permitir· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permitir· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on=1;
    ret = setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  INADDR_ANY;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

	if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}
	

   	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
		from_len = sizeof (from);


		if(listen(sd,1) == -1){
			perror("Error en la operación de listen");
			exit(1);
		}
    
    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);
    
   	
    //Capturamos la señal SIGINT (Ctrl+c)
    //signal(SIGINT,manejador);
    
	/*-----------------------------------------------------------------------
		El servidor acepta una petición

	------------------------------------------------------------------------ */
		while(1){
            
            //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)

            auxfds = readfds;
            salida = select(FD_SETSIZE,&auxfds,NULL,NULL,&timeout);
            //printf("FD_SETSIZE: %d\n", FD_SETSIZE);
            if(salida > 0){
                
                for(i=0; i<FD_SETSIZE; i++){
                    
                    //Buscamos el socket por el que se ha establecido la comunicación
                    if(FD_ISSET(i, &auxfds)) {
                        printf("i : %d\n", i);
                        
                        if( i == sd){
                            
                            if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                                perror("Error aceptando peticiones");
                            }
                            else//Acepta la peticion para la informacion
                            {
                                if(numUsuariosConectados < MAX_CLIENTS){
                                    inicializarUsuario(&usuarios[numUsuariosConectados], new_sd);

                                    numUsuariosConectados++;
                                    FD_SET(new_sd,&readfds);
                                    bzero(buffer,sizeof(buffer));
                                    send(new_sd, "\E[32m+0k. Usuario conectado\e[0m\n", strlen("\E[32m+0k. Usuario conectado\e[0m\n"),0);
                                    bzero(buffer,sizeof(buffer));
                                    sprintf(buffer, "Tu id de usuario es: %d\n", new_sd);
                                    send(new_sd, buffer, strlen(buffer),0);
                                    send(new_sd,"Introduce usuario y contraseña:\n",strlen("Introduce usuario y contraseña:\n"),0);


                                    printf("Nuevo jugador conectado: %d\n", new_sd);

                                    for(j=0; j<(numUsuariosConectados-1);j++){
                                        bzero(buffer,sizeof(buffer));
                                        sprintf(buffer, "Nuevo jugador conectado: %d\n",new_sd);
                                        send(usuarios[j+4].id,buffer,strlen(buffer),0);
                                    }
                                }
                                else
                                {
                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"Demasiados clientes conectados\n");
                                    send(new_sd,buffer,strlen(buffer),0);
                                    close(new_sd);
                                }
                            }//Realiza la conexion y guarda el nuevo cliente siempre que este vacio        
                        }
                        else 

                        if (i == 0){//Se desconecta el servidor, el propio servidor introduce informacion
                            //Se ha introducido información de teclado
                            bzero(buffer, sizeof(buffer));
                            fgets(buffer, sizeof(buffer),stdin);
                            
                            //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                            if(strcmp(buffer,"SALIR\n") == 0 || strcmp(buffer,"salir\n") == 0 ||strcmp(buffer,"Salir\n") == 0){
                             
                                for (j = 0; j < numUsuariosConectados; j++){
                                    send(usuarios[j].id, "Desconexion servidor\n", strlen("Desconexion servidor\n"),0);
                                    close(usuarios[j].id);
                                    FD_CLR(usuarios[j].id,&readfds);
                                }
                                    close(sd);
                                    exit(-1);
                            }
                            //Mensajes que se quieran mandar a los clientes (implementar)
                            
                        } 
                        else{//Recibe informacion del cliente, para distribuir y manipular

                            bzero(buffer,sizeof(buffer));
                            recibidos = recv(i,buffer,sizeof(buffer),0);
                            printf("i: %d", i);
                            if(recibidos > 0){
                                
                                if(strcmp(buffer,"SALIR\n") == 0 || strcmp(buffer,"salir\n") == 0 ||strcmp(buffer,"Salir\n") == 0){
                                    salirCliente(i,&readfds,&numUsuariosConectados,usuarios);
                                }
                                else{

                                    cabecera1=cortarCadena(buffer, MSG_SIZE, ' ');
                                    cabecera2=cortarCadena(buffer, MSG_SIZE, '\n');
                                    opcion=comprobarOpcion(cabecera1, cabecera2);

                                    switch(opcion){
                                        case 1: strncpy(argumento, buffer+strlen(cabecera1)+1, MSG_SIZE);
                                                if(argumento[strlen(argumento)-1]=='\n')
                                                    argumento[strlen(argumento)-1]='\0';
                                                printf("argumento: %s\n", argumento);
                                                printf("Peticion de registro usuario: (%s)\n", argumento);
                                                if(usuarios[i].estado==0){
                                                    printf("main\n");
                                                    if(registroComandos(argumento, &usuarios[i])==1){
                                                        printf("nombre %s pass %s\n", usuarios[i].nombre, usuarios[i].pass);
                                                        registrarUsuario(usuarios[i].nombre, usuarios[i].pass);
                                                        printf("\E[32mRegistro aceptada\e[0m\n");
                                                        bzero(buffer,sizeof(buffer));
                                                        send(i,"\E[32m+Ok. Usuario registrado\e[0m", strlen("\E[32m+Ok. Usuario registrado\e[0m"), 0);
                                                    }else{
                                                        printf("\E[31mUsuario no registrado\e[0m\n");
                                                        printf("Parametros -u y -p incorrectos\n");
                                                        bzero(buffer,sizeof(buffer));
                                                        send(i,"\E[31m+Error. Usuario no registrado\n\e[0m", strlen("\E[31m+Error. Usuario no registrado\n\e[0m"),0);
                                                        bzero(buffer,sizeof(buffer));
                                                        strcpy(buffer, "Parametros -u y -p incorrectos\n");
                                                        send(i, buffer, strlen(buffer), 0);
                                                    }
                                                    

                                                }else{
                                                    continuarRegistro(usuarios[i]);
                                                }
                                                
                                                break;
                                        case 2: 
                                                strncpy(argumento, buffer+strlen(cabecera1)+1, MSG_SIZE);
                                                if(argumento[strlen(argumento)-1]=='\n')
                                                    argumento[strlen(argumento)-1]='\0';
                                                printf("Peticion de inicio usuario: (%s)\n", argumento);
                                                if(usuarios[i].estado==0)
                                                    if(aceptaUsuario(argumento)==1){
                                                        strcpy(usuarios[i].nombre,argumento);
                                                        usuarios[i].estado=1;
                                                        bzero(buffer,sizeof(buffer));
                                                        printf("\E[32mUsuario aceptado\e[0m\n");
                                                        send(i,"\E[32m+Ok. Usuario correcto\e[0m", strlen("\E[32m+Ok. Usuario correcto\e[0m"),0);
                                                    }else{
                                                        bzero(buffer,sizeof(buffer));
                                                        printf("\E[31mUsuario denegado\e[0m\n");
                                                        send(i,  "\E[31m–ERR. Usuario incorrecto\e[0m",strlen( "\E[31m–ERR. Usuario incorrecto\e[0m"),0);
                                                    }
                                                else{
                                                    continuarRegistro(usuarios[i]);
                                                }

                                                break;
                                        case 3: strncpy(argumento, buffer+strlen(cabecera1)+1, MSG_SIZE);
                                                if(argumento[strlen(argumento)-1]=='\n')
                                                    argumento[strlen(argumento)-1]='\0';
                                                printf("Peticion de contraseña: (%s)\n", cifrarPass(argumento));
                                                if(usuarios[i].estado==1)
                                                    if(aceptaPass(usuarios[i].nombre,argumento)==1){
                                                        usuarios[i].estado=2;
                                                        strcpy(usuarios[i].pass, argumento);
                                                        bzero(buffer,sizeof(buffer));
                                                        printf("\E[32mContraseña aceptada\e[0m\n");
                                                        send(i,"\E[32m+Ok. Usuario validado\e[0m", strlen("\E[32m+Ok. Usuario validado\e[0m"),0);

                                                    }else{
                                                        bzero(buffer,sizeof(buffer));
                                                        printf("\E[31mUsuario denegado\e[0m\n");
                                                        send(i, "\E[31m–ERR. Error en la validación\e[0m",strlen("\E[31m–ERR. Error en la validación\e[0m"),0);
                                                    }
                                                else{
                                                    continuarRegistro(usuarios[i]);
                                                }
                                                break;
                                        case 4: if(usuarios[i].estado==2){
                                                    printf("Usuario %s ha iniciado partida.\n", usuarios[i].nombre);
                                                    bzero(buffer,sizeof(buffer));
                                                    send(i, "Bienvenido al bingo.\n", strlen("Bienvenido al bingo.\n"),0);
                                                    bzero(buffer,sizeof(buffer));
                                                    send(i, "\E[32m+Ok. Petición Recibida. Quedamos a la espera de más jugadores\e[0m", strlen("\E[32m+Ok. Petición Recibida. Quedamos a la espera de más jugadores\e[0m"),0);
                                                    usuarios[i].estado=3;
                                                    usuarios[i].partida=numPartidas;
                                                    numUsuariosJugando++;
                                                    partidas[numPartidas].usuarios[partidas[numPartidas].numUsuarios]=i;
                                                    partidas[numPartidas].numUsuarios++;

                                                    if (numUsuariosJugando>0 && numUsuariosJugando%2==0)
                                                    {
                                                        partidas[numPartidas].comenzada=1;
                                                        printf("Partida %d iniciada.\n", numPartidas+1);
                                                        for (i = 0; i < partidas[numPartidas].numUsuarios; ++i)
                                                        {
                                                            send(partidas[numPartidas].usuarios[i],"\E[32m+Ok. Empieza la partida\e[0m", strlen("\E[32m+Ok. Empieza la partida\e[0m"),0);
                                                        }
                                                        printf("MANDAR\n");
                                                        mandarCarton(&partidas[numPartidas]);
                                                        printf("fuera\n");
                                                        numPartidas++;
                                                    }
                                                    printf("hola\n");
                                                    
                                                }else{
                                                    continuarRegistro(usuarios[i]);
                                                }

                                                break;
                                        case 5: printf("opcion linea\n");
                                                break;
                                        case 6: printf("opcion doslineas\n");
                                                break;
                                        case 7: printf("opcion bingo\n");
                                                break;
                                        default: bzero(buffer,sizeof(buffer));
                                                send(i,"Opción para cliente incorrecta REGISTER|USUARIO|INICIAR-PARTIDA|...|UNA-LINEA|BINGO",
                                                    strlen("Opción para cliente incorrecta REGISTER|USUARIO|INICIAR-PARTIDA|...|UNA-LINEA|BINGO"),0);
                                                break;
                                    }//switch(opcion)
                                }//if(strcmp(buffer,"SALIR\n") == 0) else 
                            }//if(recibidos > 0)
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0)
                            {
                                printf("El socket %d, ha introducido ctrl+c\n", i);
                                //Eliminar ese socket
                                salirCliente(i,&readfds,&numUsuariosConectados,usuarios);
                            }
                        }//if (i == 0) else
                        printf("if(FD_ISSET(i, &auxfds))\n");
                    }//if(FD_ISSET(i, &auxfds)) 
                    printf("for(i=0; i<FD_SETSIZE; i++)\n");
                }//for(i=0; i<FD_SETSIZE; i++)
                printf("(salida > 0)\n");
            }//(salida > 0)
            if(timeout.tv_sec==0){
                timeout.tv_sec = 10;
                timeout.tv_usec = 0;
                if(numPartidas>0)
                    mandarBola(partidas, numPartidas);
            }
            
		}//while(1)
		close(sd);	
}

