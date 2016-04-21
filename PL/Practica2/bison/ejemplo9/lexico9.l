%{
#include "macros.h"
#include "ejemplo9.h"
#include "ejemplo9.tab.h"
extern char *progname;
extern int lineno;
%}
/* definiciones regulares */
numero        [0-9]
letra         [a-zA-Z]
identificador {letra}({letra}|{numero})*

%%
[ \t] { ; } /* saltar los espacios y los tabuladores */

{numero}+\.?|{numero}*\.{numero}+ {double d;  
                                   sscanf(yytext,"%lf",&d);
                                 /* Instala el numero en la tabla de simbolos */
				   yylval.sym=install("",NUMBER,d); 
				   return NUMBER;}

{identificador} { Symbol *s;
                   if ((s=lookup(yytext)) == 0)
                               s = install (yytext, INDEFINIDA, 0.0);
                    yylval.sym = s;
                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

">="	{return MAYOR_IGUAL;}
"<="	{return MENOR_IGUAL;}
"=="	{return IGUAL;}
"!="	{return DISTINTO;}
">"	{return MAYOR_QUE;}
"<"	{return MENOR_QUE;}
"!"	{return NEGACION;}
"||"	{return O_LOGICO;}
"&&"	{return Y_LOGICO;}
":="      {return ASIGNACION;}
^#       { 
 	  BORRAR; 
	  LUGAR(10,10);
	  INTENSIDAD;
	  printf(">>>>>>> Fin del programa <<<<<<<\n");
	  APAGA;
	  LUGAR(24,1);

  	  return 0;
	}
\n      {lineno++; } /* no se devuelve nada, continúa el analisis léxico */
.       {return yytext[0];}
