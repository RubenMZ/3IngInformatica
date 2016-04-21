#ifndef EJEMPLO6_H
#define EJEMPLO6_H

 /* ejemplo6.h */


int yylex();

void yyerror(char *s);

void warning(char *s, char *t);

void execerror(char *s,char *t);

void init();

typedef struct Symbol { /* entrada en la tabla de simbolos */
	               char *nombre;
	               short tipo;  /* VAR, FUNCION, INDEFINIDA */ 
	               union {
		              double val;        /* si es VAR */
		              double (*ptr)();   /* si es FUNCION */
		             } u;
                       struct Symbol * siguiente;
	              } Symbol;

Symbol *install(char *s, int t, double d), *lookup(char *);

#endif
