%{
#include "ejemplo5.h"
#include "ejemplo5.tab.h"

extern char *progname;
extern int lineno;
%}
/* definiciones regulares */
numero        [0-9]
letra         [a-zA-Z]
identificador {letra}({letra}|{numero})*

%%
[ \t] { ; } /* saltar los espacios y los tabuladores */

{numero}+\.?|{numero}*\.{numero}+ { sscanf(yytext,"%lf",&yylval.val); 
				    return NUMBER;}

{identificador} { Symbol *s;
                   if ((s=lookup(yytext)) == 0)
                               s = install (yytext, INDEFINIDA, 0.0);
                    yylval.sym = s;
                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

:=      {return ASIGNACION;}
^#      { printf("\n>>>>>>> Fin del programa <<<<<<<\n"); return 0;}
;       {return FIN ;} 
\n      {lineno++; return FIN;} 
.       {return yytext[0];}
