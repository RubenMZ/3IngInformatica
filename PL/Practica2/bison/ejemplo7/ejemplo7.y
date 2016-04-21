/*
 Ejemplo 7
 
 Realiza lo mismo que el ejemplo 5 pero genera un código intermedio 
 que posteriormente es ejecutado

*/

%{

#include <stdio.h>
#include <math.h>

#include "ejemplo7.h"


/* declaracion de "macros" para simplificar la escritura */
#define code2(c1,c2)         code(c1); code(c2)
#define code3(c1,c2,c3)      code(c1); code(c2); code(c3)
%}
%union{               /* tipos de datos de la pila */
       Symbol *sym;   /* puntero a la tabla de simbolos */
       Inst   *inst;  /* instruccion de maquina */ 
}

%token FIN
%token <sym> NUMBER VAR FUNCION_PREDEFINIDA INDEFINIDA CONSTANTE
%right ASIGNACION
%left '+' '-'
%left '*' '/' '%'
%left UNARIO
%right '^'    
%%

list :       /* nada: epsilon produccion */
        | list FIN
        | list asgn FIN  {code2(pop2,STOP); return 1;}
        | list expr FIN  {code2(escribir,STOP); return 1;}
        | list error FIN {yyerrok;}
        ; 

asgn :    VAR ASIGNACION expr {code3(varpush,(Inst)$1,assign);}
        | CONSTANTE ASIGNACION expr 
          {execerror(" NO se pueden asignar datos a constantes ",$1->nombre);}
	;

expr :    NUMBER     {code2(constpush,(Inst)$1);}
        | VAR        {code3(varpush,(Inst)$1,eval);} 
        | CONSTANTE  {code3(varpush,(Inst)$1,eval);} 
        | asgn       
        | FUNCION_PREDEFINIDA '(' expr ')' {code2(funcion,(Inst)$1->u.ptr);}
        | '(' expr ')'  
        | expr '+' expr {code(sumar);}
        | expr '-' expr {code(restar);}
        | expr '*' expr {code(multiplicar);}
        | expr '/' expr {code(dividir);}
        | expr '%' expr {code(modulo);}
        | expr '^' expr {code(potencia);}
        | '-' expr %prec UNARIO {code(negativo);}
        | '+' expr %prec UNARIO {code(positivo);}
	;

%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf begin;
char *progname;
int lineno = 1;

void fpecatch();

int main(int argc, char *argv[])
{
 /* Nombre del programa */
 progname=argv[0];

 /* Inicializacion de la tabla de simbolos */
 init();

/* Establece un estado viable para continuar despues de un error*/
 setjmp(begin);

/* Establece cual va ser la funcion para tratar los errores de punto flotante */
 signal(SIGFPE,fpecatch);

/* initcode inicializa el vector de instrucciones y la pila del interprete */
 for(initcode(); yyparse(); initcode()) 
	execute(prog);

 return 0;
}
  
void yyerror(char *s)
{
 warning(s,(char *) 0);
}

void warning(char *s, char *t)
{
 fprintf(stderr," ** %s : %s", progname,s);
 if (t) fprintf(stderr," ---> %s ",t);
 fprintf(stderr,"  (linea %d)\n",lineno);
}

void execerror(s,t) /* recuperacion de errores durante la ejecucion */
char *s,*t;
{
 warning(s,t);
  longjmp(begin,0);
}

void fpecatch()     /* atrapa errores de punto flotante */
{
 execerror("error de punto flotante ",(char *)0);
}
