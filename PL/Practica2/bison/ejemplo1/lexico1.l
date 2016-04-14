%{
#include <stdio.h>

#include "ejemplo1.h"
#include "ejemplo1.tab.h"


/* extern YYSTYPE yylval; */
extern char *progname;
extern int lineno;
%}
/* definicion regular */

numero   [0-9]
  	
%%
[ \t] 		{ ; } /* saltar los espacios y los tabuladores */

{numero}+\.?|{numero}*\.{numero}+  {
                                    sscanf(yytext,"%lf",&yylval);
                                    // yylval - Permite comunicar el valor de un componente lexico al sintactico
                                    return NUMBER; 
                                    }

\n      {lineno++; return '\n';}

.       {return yytext[0];}
%%

