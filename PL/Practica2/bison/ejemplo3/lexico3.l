%{
#include "ejemplo3.tab.h"

/*extern YYSTYPE yylval;*/

extern char *progname;
extern int lineno;
%}
/* definiciones regulares */

numero   [0-9]
letra    [a-z]
  	
%%
[ \t] 		{ ; } /* saltar los espacios y los tabuladores */

{numero}+\.?|{numero}*\.{numero}+  {sscanf(yytext,"%lf",&yylval.val);
                                    return NUMBER;}

{letra} {yylval.index=yytext[0] -'a'; return VAR;}

;       {return FIN;}
\n      {lineno++; return FIN;}
^#      {printf("\n Fin del programa\n"); return 0;}
.       {return yytext[0];}
%%

