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
		int estado;//0-> comenzada, 1->UNA-LINEA 2->DOS-LINEAS 3->BINGO
		int bandera; /*-1-> no cambia nada, 0->empieza partida, mandar cartones 
					>0-> cambia estado UNA-LINEA, DOS-LINEAS , BINGO*/
	}Partida;

#endif