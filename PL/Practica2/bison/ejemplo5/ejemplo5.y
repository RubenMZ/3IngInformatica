/* 
  Ejemplo 5
  
   Se ha ampliado el ejemplo 4 
   
   Permite que una variable pueda ser un identificador que empiece por una letra y que pueda ir seguida de letras o dígitos.

   Los identificadores se almacenan en una tabla de símbolos (lista simplemente encadenada)

   Hay constantes predefinidas
   	                    "PI",    3.14159265358979323846
	                    "E",     2.71828182845904523536
	                    "GAMMA", 0.57721566490153286060
	                    "DEG",  57.29577951308232087680
	                    "PHI",   1.61803398874989484820
   Pero permite cambiar el valor de una constante
   PI := 3.14
   PI := 0.0
   
   También permite funciones predefinidas con un argumento:
   	sin, cos, atan, log, Log10,  exp, sqrt, int,  abs
   	
   	
   	
*/
%{
#include <stdio.h>
#include <math.h>

#include "ejemplo5.h"
%}

%union{
       double val;  /* valor actual */ 
       Symbol *sym; /* puntero a la tabla de simbolos */
      }

%token FIN
%token <val> NUMBER 
%token <sym> VAR INDEFINIDA FUNCION_PREDEFINIDA 
%type <val> expr asgn
%right ASIGNACION
%left '+' '-'
%left '*' '/' '%'
%left UNARIO
%right '^'
%%

list :       /* nada: epsilon produccion */
        | list FIN
        | list asgn FIN  
        | list expr FIN  {printf("\t%.8g\n",$2);}
        | list error FIN {yyerrok;}
        ; 

asgn :    VAR ASIGNACION expr {$$ = $1->u.val=$3; $1->tipo = VAR;}
	;

expr :    NUMBER 
        | VAR { if ($1->tipo ==  INDEFINIDA) 
		  execerror(" variable no definida ",$1->nombre);
                 else $$ = $1->u.val;}
        | asgn
        | FUNCION_PREDEFINIDA '(' expr ')' {$$ = (*($1->u.ptr))($3);}
        | expr '+' expr {$$ = $1 + $3;}
        | expr '-' expr {$$ = $1 - $3;}
        | expr '*' expr {$$ = $1 * $3;}
        | expr '/' expr {if ($3 == 0.0) execerror(" division por cero ","");
			  else $$ = $1 / $3;}   
        | expr '%' expr {if ($3 == 0.0) execerror("division por cero ","");
			  else $$ = (int) $1 % (int) $3;}
        | expr '^' expr { $$ = pow($1,$3);}
        | '(' expr ')'  {$$ = $2;}
        | '-' expr %prec UNARIO {$$ = -$2;}  
        | '+' expr %prec UNARIO {$$ = +$2;} 
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

/* Llamada al analizador sintáctico */
 yyparse();

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

void execerror(char *s,char *t) /* recuperacion de errores durante la ejecucion */
{
 warning(s,t);
  longjmp(begin,0);
}

void fpecatch()     /*  atrapa errores de punto flotante */
{
 execerror("error de punto flotante ",(char *)0);
}
