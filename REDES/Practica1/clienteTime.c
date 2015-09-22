#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* --------------------------------------------------------------------------------------
 
 Envía un número aleatorio al servidor, quien el devuelve el número incremetnado

---------------------------------------------------------------------------------------- */
 
main (int argc, char* argv[])
{

		/*---------------------------------------------------- 
			Descriptor del socket y buffer para datos 
		-----------------------------------------------------*/
		int Socket_Cliente;
		char argumento[100];
   
   	/* -----------------------------------------------------
   		Informaci\ufffdn del Servidor
   	-----------------------------------------------------*/
   	struct sockaddr_in Servidor;  
   	socklen_t Longitud_Servidor;

   	struct timeval timeout;
	fd_set lectura;
	int salida;

	int recibido=0;
	int enviado=-1;
	int reenvio=0;
  
 
	if(argc!=3){
		printf("Error en argumentos: <programa><IP><port>\n");
		exit(-1);
	}

   	/* --------------------------------------------------
			Se abre el socket cliente
		---------------------------------------------------*/
		Socket_Cliente = socket (AF_INET, SOCK_DGRAM, 0);
		if (Socket_Cliente == -1)
		{
			printf ("No se puede abrir el socket cliente\n");
    		exit (-1);	
		}

 		/*---------------------------------------------------------------------
			Necesitamos una estructura con la informaci\ufffdn del Servidor
			para poder solicitarle un servicio.
   		----------------------------------------------------------------------*/
		Servidor.sin_family = AF_INET;
		Servidor.sin_port = htons(atoi(argv[2]));//2000
		Servidor.sin_addr.s_addr =  inet_addr(argv[1]);//127.0.0.1
  	 	Longitud_Servidor = sizeof(Servidor);
   	
  	 	printf("Introduce DAY|TIME|DAYTIME: ");
  	 	scanf("%s", argumento);

  	 do{
  	 	printf("Enviado: %s\n", argumento);
		/*-----------------------------------------------------------------------
			Se env\ufffda mensaje al Servidor
		-----------------------------------------------------------------------*/
		enviado = sendto (Socket_Cliente, (char *) &argumento, sizeof(argumento), 0,
			(struct sockaddr *) &Servidor, Longitud_Servidor);
   
   	if (enviado < 0)
    	{
			printf("Error al solicitar el servicio\n");
		}
    	else
		{
   

	//Inicializar la estructua timeval
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
				//Inicializar los conjuntos fd_set
	FD_ZERO(&lectura);
	FD_SET( Socket_Cliente,&lectura);

	   	salida = select(Socket_Cliente+1,&lectura,NULL,NULL,&timeout);
		
		if(salida == -1)
		{
			printf("Se ha producido un error en select\n");
		}
		else if(salida == 0)
		{
			printf("Se ha agotado el tiempo\n");
			reenvio++;
		}else
			recibido = recvfrom (Socket_Cliente, (char *)&argumento, sizeof(argumento), 0,(struct sockaddr *) &Servidor, &Longitud_Servidor);	
		/*----------------------------------------------------------------------
			Esperamos la respuesta del Servidor
			----------------------------------------------------------------------- */ 

	


   		if (recibido > 0){
   			printf("Leido.\n");
      		printf ("%s\n", argumento);
   		}else
      		printf ("Error al leer del servidor\n");
		}

	}while(salida==0 && reenvio<3);//No conecta y reintenta 3 veces


		if (reenvio==3)
		{
			printf("Retry 3... Not connection\n");
		}
		
		close(Socket_Cliente);
}
