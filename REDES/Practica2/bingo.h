#ifndef BINGO_H
#define BINGO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "registro.h"

#define MSG_SIZE 250
#define MAX_CLIENTS 40

	int ** generaCarton();
	int compruebaRepetido(int ** carton, int fil, int col, int n);
	void ordenarCarton(int ** carton, int fil, int col);
	void mandarBola(Partida * partidas, int n);
	int compruebaBola(int * vector, int n, int bola);
	char * inttochar(int ** matriz);
	int ** chartoint(char * cadena);
	void mandarCarton(Partida * partida, Usuario usuarios[], int n);
	void actualizarPartidas(int numPartidas, Partida partidas[]);

#endif