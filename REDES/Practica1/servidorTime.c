#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/*
 * El servidor ofrece el servicio de incrementar un n\ufffdmero recibido de un cliente
 */
 
main ()
{
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int Socket_Servidor;
	struct sockaddr_in Servidor;

	time_t tiempo;
	struct tm * stTm;
	char cadena [80];
	

	
	
	/* -----------------------------------------------------
   		Informaci\ufffdn del Cliente
   	-----------------------------------------------------*/
   struct sockaddr_in Cliente;
	socklen_t Longitud_Cliente;
	
	
	/* --------------------------------------------------
		Se abre el socket Servidor
	---------------------------------------------------*/
	Socket_Servidor = socket (AF_INET, SOCK_DGRAM, 0);
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket servidor\n");
		exit (-1);	
	}

	/* ------------------------------------------------------------------
		Se rellenan los campos de la estructura servidor, necesaria
		para la llamada a la funcion bind().
	-------------------------------------------------------------------*/
	Servidor.sin_family = AF_INET;
	Servidor.sin_port = htons(2000);
	Servidor.sin_addr.s_addr = htonl(INADDR_ANY); 

	if (bind (Socket_Servidor, (struct sockaddr *)&Servidor, sizeof (Servidor)) == -1)
	{
		close (Socket_Servidor);
		exit (-1);
	}
	

  	/*---------------------------------------------------------------------
		Del cliente s\ufffdlo necesitamos el tama\ufffdo de su estructura, el 
		resto de informaci\ufffdn (familia, puerto, ip), la obtendremos 
		nos la proporcionar\ufffd el propio m\ufffdtodo recvfrom, cuando
		recibamos la llamada de un cliente.
   ----------------------------------------------------------------------*/
	Longitud_Cliente = sizeof (Cliente);

   	
	/*-----------------------------------------------------------------------
		El servidor espera continuamente los mensajes de los clientes
	------------------------------------------------------------------------ */
	while (1)
	{


    /* -----------------------------------------------------------------
			Esperamos la llamada de alg\ufffdn cliente
		-------------------------------------------------------------------*/
      	int recibido = recvfrom (Socket_Servidor, &cadena, sizeof(cadena), 0,
			(struct sockaddr *) &Cliente, &Longitud_Cliente);
		/* -----------------------------------------------------------------
			Comprobamos si hemos recibido alguna informaci\ufffdn 
		-------------------------------------------------------------------*/
			tiempo = time(NULL);
		if (recibido > 0)
		{
			printf("Recibido.\n");
			/*-----------------------------------------------------------------
				Incrementamos el valor que nos ha enviado el cliente 
				------------------------------------------------------------------*/
      			if(strcmp(cadena, "DAY")==0){
      					printf("DAY\n");
      					stTm = localtime(&tiempo);
						strftime(cadena,80,"%A, %d of %B", stTm);
      			}else{
      				if(strcmp(cadena, "TIME")==0){
      					printf("TIME\n");
      						stTm = localtime(&tiempo);
							strftime(cadena,80,"%H:%M:%S", stTm);
      				}else{
      					
      					if(strcmp(cadena, "DAYTIME")==0){
      						printf("DAYTIME\n");
	      					stTm = localtime(&tiempo);
							strftime(cadena,80,"%A, %d of %B;%H:%M:%S", stTm);
						}else{
							printf("No coincide\n");
							strcpy(cadena, "No coincide");
						}
      				}
      			}
      	
      			printf("cadena: %s\n", cadena);
      	/* ------------------------------------------------------------------
				Devolvemos el n\ufffdmero incrementado al cliente
				--------------------------------------------------------------------*/
			int enviado = sendto (Socket_Servidor, &cadena, sizeof(cadena), 0,
			(struct sockaddr *) &Cliente, Longitud_Cliente);
			printf("Enviado.\n");

		}

    }
	 
	 close(Socket_Servidor);
}
