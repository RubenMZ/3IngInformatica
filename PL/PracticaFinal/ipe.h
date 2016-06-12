#ifndef FINAL_H
#define FINAL_H

 /* ejemplo9.h */


int yylex();

void yyerror(char *s);

void warning(char *s, char *t);

void execerror(char *s,char *t);

void init();

typedef struct Symbol 
            { /* elementos de la tabla de simbolos */
	        char *nombre;
	        short tipo; /* NUMBER,VAR,FUNCION,INDEFINIDA,CONSTANTE */ 
	        short subtipo;
	        struct {
		       double val;      /* VAR, NUMBER, INDEFINIDA, CONSTANTE */
		       double (*ptr)(); /* FUNCION  */
	        	char chain[1000];
		      } u;
                 struct Symbol *siguiente;
	     } Symbol;

Symbol *install(), *install2(), *lookup();

typedef struct Datum { /* tipo de la pila del interprete */ 
                     short tipo;
                     short subtipo;
                     double val;
                     Symbol *sym;
                     char chain[1000];
                    } Datum;

void push(Datum d);
extern Datum pop();
extern void pop2();

typedef void (*Inst)(); /* instruccion maquina */
#define STOP (Inst) 0

extern Inst prog[];

/* NOVEDAD */
extern Inst* progp;

void initcode();
 
Inst *code(Inst f);

void execute(Inst *p);

/**************************/
extern void assign();
extern void constpush();

void escribir();
void escribircadena();
void eval();

void funcion();
void funcion0();
void funcion1();
void funcion2();

/*%left SUMA RESTA 
 %left PROD DIV DIV_INT MOD POT*/
void modulo();
void multiplicar();
void negativo();
void positivo();
void potencia(); 
void restar();
void sumar();
void varpush();
void dividir();
void dividir_int();

/*MAYOR_QUE MENOR_QUE MENOR_IGUAL MAYOR_IGUAL DISTINTO IGUAL*/
void mayor_que();
void menor_que();
void mayor_igual();
void menor_igual();
void igual(); 
void distinto();

void y_logico();
void o_logico();
void negacion();

void concatenacion();

void ifcode();
void whilecode();
void forcode();
void dowhilecode();

void lugar();
void borrar();

void leervariable();
void leercadena();

#endif
