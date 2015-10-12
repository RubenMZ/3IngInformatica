#ifndef FUNCIONES_H
#define FUNCIONES_H


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
	
	typedef struct usuario{
		char nombre[100];
		char pass[100];
		int partida;
		int id;
		int ** carton;
	}usuario;

	typedef struct partida
	{
		int usuarios[4];
		int comenzada;
		int bolas[90];
	}partida;


	void manejador(int signum);
	void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]);



	int ** generaCarton();
	int compruebaRepetido(int ** carton, int fil, int col, int n);
	void ordenarCarton(int ** carton, int fil, int col);

	int aceptaUsuario(char * nombre);
	char * cortarCadena(char * cadena, int n, char c);
	int aceptaPass(char * nombre, char* pass);
	int registrarUsuario(char * nombre, char * pass);

#endif