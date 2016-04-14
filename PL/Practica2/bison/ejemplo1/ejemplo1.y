/*
 Ejemplo 1
 
 Interpreta expresiones aritméticas: suma, resta, multiplicación y división
 Permite expresiones entre paréntesis y el signo "-" unario
 No permite el signo "+" unario
 Las expresiones deben terminar con un salto de línea
 
  El programa finaliza pulsando Control + D
*/


%{ 
#include <stdio.h>

#include "ejemplo1.h"  /*  tipos de datos de la pila de yacc */
%}


%token NUMBER
%left '+' '-'   /* asociatividad a la izquierda; precedencia menor */
%left '*' '/'
%left UNARYMINUS /* maxima precedencia */ 

%%

list :       /* nada: epsilon - produccion */
        | list '\n'
        | list expr '\n'  {printf("\t%.8g\n",$2);}
        ;

expr :    NUMBER        {$$ = $1;}  
        | expr '+' expr {$$ = $1 + $3;}
        | expr '-' expr {$$ = $1 - $3;}
        | expr '*' expr {$$ = $1 * $3;}
        | expr '/' expr {$$ = $1 / $3;}
        | '(' expr ')'  {$$ = $2;}
        |'-' expr %prec UNARYMINUS { $$ = -$2; }
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
