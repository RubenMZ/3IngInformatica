#include <stdlib.h> 
#include <stdio.h>
#include <signal.h>  



/* Variable entera para controlar fin de un bucle */
int bucle = 1;           

void finalizar_bucle ();  

int main () {
    
	 /* Asociamos la señal SIGALRM con la función finalizar_bucle(). */
	
	 signal (SIGALRM, finalizar_bucle);      
	 
	 /* Configuramos la alarma a los 5 segundos.*/  
	 /* Pasados los 5 segundos se recibirá una señal de alarma */
	 alarm (5);       
	
	/* Estaremos en el bucle while, hasta que la alarma cambie el valor de la variable
	bucle en la funcińo finalizar_bucle() */
  while (bucle==1)
	printf("hola");       
  
  	printf ("Han pasado 5 segundos\n"); 
	
	return 0; 
				 
}

/* La funcińo finalizar_bucle, cambia el valor de la variable bucle y desactiva la alarma */

void finalizar_bucle () {       
	
	//Se ignora la señal SIGALRM
	signal (SIGALRM, SIG_IGN);  

	bucle=0;
	
}
