%{
#include "ejemplo2.h"
#include "ejemplo2.tab.h"


/* extern YYSTYPE yylval; */
extern char *progname;
extern int lineno;
%}
/* definicion regular */

numero   [0-9]
  	
%%
[ \t] 		{ ; } /* saltar los espacios y los tabuladores */

{numero}+\.?|{numero}*\.{numero}+  {sscanf(yytext,"%lf",&yylval);
                                    return NUMBER;}


&|\+	{return MAS;}

\-		{return MENOS;}

\*|x		{return POR;}
	
\/|\:		{return DIV;}

\%		{return MOD;}

\^		{return EXP;}

;       {return FIN;}
\n      {lineno++; return FIN;}
^#      {printf("\n Fin del programa\n"); return 0;}
.       {return yytext[0];}
%%

