#ifndef FUNCIONESSERVIDOR_H
#define FUNCIONESSERVIDOR_H

#include "estructuras.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#define MSG_SIZE 250
#define MAX_CLIENTS 40

	void manejador(int signum);
	void salirCliente(int socket, fd_set * readfds, int * numUsuarios, Usuario usuarios[], int numPartidas, Partida partidas[]);
	void salirPartida(int socket, int numPartidas, Partida partidas[]);
	int comprobarOpcion(char * cabecera1, char * cabecera2);
	void continuarJugando(Usuario u, int estado);




#endif