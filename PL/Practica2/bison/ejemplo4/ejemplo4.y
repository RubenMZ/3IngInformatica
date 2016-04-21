/*
 Ejemplo 4:

  Se ha modificado el ejemplo 3 para usar el operador de asignación de Pascal
   := 

  Por ejemplo
   a := 3;
*/


%{
#include <stdio.h>
#include <math.h>

#include "ejemplo4.h"  

  double mem[26]; /* memoria para la variables `a',..., `z' */
%}

%union{             /* tipo de la pila */
       double val;  /* valor actual */ 
       int index;   /* indice de mem[] */
} 

%token FIN
%token <val> NUMBER
%token <index> VAR
%type <val> expr 
%right ASIGNACION 
%left '+' '-'
%left '*' '/' '%'
%left UNARIO
%right '^'

%%

list :       /* nada: epsilon produccion */
        | list FIN
        | list expr FIN  {printf("\t%.8g\n",$2); mem['p'-'a']=$2;}
        | list error FIN {yyerrok;}
        ;
expr :    NUMBER 
        | VAR { $$ = mem [$1];}
        | VAR ASIGNACION  expr { $$ = mem [$1] = $3;}
        | expr '+' expr {$$ = $1 + $3;}
        | expr '-' expr {$$ = $1 - $3;}
        | expr '*' expr {$$ = $1 * $3;}
        | expr '%' expr {if ($3 == 0.0) execerror("division por cero ","");
			  else $$ = (int) $1 % (int) $3;}
        | expr '^' expr {$$ = pow($1,$3);}
        | expr '/' expr {if ($3 == 0.0) execerror("division por cero ","");
			  else $$ = $1 / $3;}
        | '(' expr ')'  {$$ = $2;}
        | '+' expr %prec UNARIO { $$ = +$2; }
        | '-' expr %prec UNARIO { $$ = -$2; }
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

 progname=argv[0];

/* Establece un estado viable para continuar despues de un error */
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
 fprintf(stderr,"%s: %s", progname,s);
 if (t) fprintf(stderr,"%s",t);
 fprintf(stderr," en la linea %d \n",lineno);
}

void execerror(char *s,char *t) /* recuperacion de errores durante la ejecucion */
{
 warning(s,t); /* da el mensaje de error */
 longjmp(begin,0); /* vuelve a un estado viable */
}

void fpecatch()     /* maneja errores de punto flotante */
{
 execerror("error de punto flotante ",(char *)0);
}
