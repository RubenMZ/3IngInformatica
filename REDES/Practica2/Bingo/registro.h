#ifndef REGISTRO_H
#define REGISTRO_H

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
#include <unistd.h>


#define MSG_SIZE 250
#define MAX_CLIENTS 40

	void inicializarUsuario(Usuario *u, int id);
	int aceptaUsuario(char * nombre);
	char * cortarCadena(char * cadena, int n, char c);
	int aceptaPass(char * nombre, char* pass);
	int registrarUsuario(char * nombre, char * pass);
	int registroComandos(char* argv, Usuario* user);
	char * cifrarPass(char * cadena);
	void continuarRegistro(Usuario usuario);
	Usuario buscarUsuario(int id, Usuario usuarios[],int n);
	int buscarPosicion(int id, Usuario usuarios[],int n);
	Partida * buscarPartida(int id, Partida partidas[], int n);

#endif