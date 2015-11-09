#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

	typedef struct usuario{
		char nombre[100];
		char pass[100];
		int estado;//0->Nada(solo conectado), 1->UsuarioCorrecto, 2->Pass correcta, 3->Usuario Preparado 
		int partida;//=-1->Ninguna, >-1 Partida
		int id;
		int ** carton;
	}Usuario;

	typedef struct partida{
		int id;
		int usuarios[4];
		int comenzada;
		int numUsuarios;
		int bolas[90];
		int numBolas;
		int estado;//0-> comenzada, 1->una linea 2->dos lineas 3->bingo
		int bandera; //0-> no cambia nada, 1-> se aumenta el estado
	}Partida;

#endif