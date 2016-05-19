%{
#include "macros.h"
#include "final.h"
#include "final.tab.h"
extern char *progname;
extern int lineno;
%}
/* definiciones regulares */
espacio		[ \t]
espacios	{espacio}+
linea           [\n]
letra		[a-zA-Z]
digito		[0-9]
    
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?

caracter	[a-zA-Z]|[0-9]
identificador   {letra}({caracter})*(_{caracter})*({caracter})*   


inicio		(?i:inicio)
fin 		(?i:fin)
__mod 		(?i:__mod)
__div     (?i:__div)
__o 		(?i:__o)
__y 		(?i:__y)
__no 		(?i:__no)
leer 		(?i:leer)
leer_cadena   (?i:leer_cadena)
escribir 	(?i:escribir)
escribir_cadena  (?i:escribir_cadena)
si 		(?i:si)
entonces 	(?i:entonces)
si_no		(?i:si_no)
fin_si		(?i:fin_si)
mientras 	(?i:mientras)
hacer		(?i:hacer)
fin_mientras  	(?i:fin_mientras)
repetir 	(?i:repetir)
hasta_que 	(?i:hasta_que)
para 		(?i:para)
desde 		(?i:desde)
hasta 		(?i:hasta)
paso 		(?i:paso)
fin_para 	(?i:fin_para)
__borrar  (?i:__borrar)
__lugar   (?i:__lugar)

cadena          \'(.)*\'

reservada (inicio|fin|__mod|__div|__o|__y|__no|leer|leer_cadena|escribir|escribir_cadena|si|entonces|si_no|fin_si|mientras|hacer|fin_mientras|repetir|hasta_que|para|desde|hasta|paso|fin_para|__borrar|__lugar) 

error_Id      ({letra}({caracter}*|__+)*{caracter}*_*)|({numero}({caracter}*|_*|__+)*{caracter}*)
error_Num   ({digito}+|(\.|\,)+)({digito}+|_*|(\.|\,)+)*{digito}*

%%


espacio { ; } /* saltar los espacios y los tabuladores */

{numero}			{double d;  
                                   sscanf(yytext,"%lf",&d);
                                 /* Instala el numero en la tabla de simbolos */
				   yylval.sym=install("",NUMBER,d); 
				   return NUMBER;}

{identificador} { Symbol *s;
					int i=0;
					for(i=0; i<strlen(yytext); i++){
						yytext[i]=tolower(yytext[i]);
					}
                   if ((s=lookup(yytext)) == 0)
                               s = install (yytext, INDEFINIDA, 0.0);
                    yylval.sym = s;
                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

":="                    {return ASIGNACION;}
"+"                     {return SUMA;}
"-"                     {return RESTA;}
"*"                     {return PROD;}
"/"                     {return DIV;}
{__borrar}				{return TOKEN_BORRAR;}
{__lugar}				{return TOKEN_LUGAR;}
{__div}                 {return DIV_INT;}
{__mod}					{return MOD;}
"**"                    {return POT;}
"||"                    {return CONCAT;}
"<"                     {return MENOR_QUE;}
"<="                    {return MENOR_IGUAL;}
">"                     {return MAYOR_QUE;}
">="                    {return MAYOR_IGUAL;}
"=="                    {return IGUAL;}
"<>"                    {return DISTINTO;}
{__o}                   {return O_LOGICO;}
{__y}                   {return Y_LOGICO;}
{__no}                  {return NO_LOGICO;}


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
