/*
 Ejemplo 2

 Se ha ampliado el ejemplo 1 
 Se permite el uso de 
  - punto coma ";" como delimitador de expresiones, además del salto de línea
  - signo + unario
  - operador del resto de la división entera: %
  - operador potencia de un número: ^ (asociativo por la derecha)
  
  El programa termina su ejecución cuando se teclea # al principio de la línea 
  o pulsando Control + D
*/


%{
#include <stdio.h>
#include <math.h>

#include "ejemplo2.h"  

%}


%token NUMBER FIN
%left MAS MENOS   /* asociatividad a la izquierda; precedencia menor */
%left POR DIV MOD
%left UNARIO /* maxima precedencia */ 
%right EXP
%%

list :       /* nada: epsilon - produccion */
        | list FIN
        | list expr FIN  {printf("\t%.8g\n",$2);}
        ;

expr :    NUMBER        {$$ = $1;}  
        | expr MAS expr {$$ = $1 + $3;}
        | expr MENOS expr {$$ = $1 - $3;}
        | expr POR expr {$$ = $1 * $3;}
        | expr DIV expr {$$ = $1 / $3;}
        | expr MOD expr {$$ = (int) $1 % (int) $3;}
        | expr EXP expr {$$ = pow($1,$3);}
        | '(' expr ')'  {$$ = $2;}
        | MENOS expr %prec UNARIO { $$ = -$2;}
        | MAS expr %prec UNARIO { $$ = $2;}
	;

%%

#include <stdio.h>
#include <ctype.h>

char *progname;
int lineno = 1;

main(int argc, char *argv[])
{
 progname=argv[0];
 yyparse();
}


/* Llamada en caso de error de sintaxis de yacc */

yyerror(char *s)
{
 warning(s,(char *) 0);
}

/* Imprime mensajes de aviso */

warning(char *s, char *t)
{
 fprintf(stderr,"%s: %s", progname,s);
 if (t) fprintf(stderr," %s ",t);
 fprintf(stderr," en la linea %d \n",lineno);
}
