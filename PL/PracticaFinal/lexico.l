%{
#include "macros.h"
#include "ipe.h"
#include "ipe.tab.h"
#include <string.h>

extern char *progname;
extern int lineno;

int numComentarioLinea=0;
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
_mod 		(?i:_mod)
_div     	(?i:_div)
_o 			(?i:_o)
_y 			(?i:_y)
_no 		(?i:_no)
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
_borrar  	(?i:_borrar)
_lugar   	(?i:_lugar)

cadena          \'(.)*\'

reservada (inicio|fin|_mod|_div|_o|_y|_no|leer|leer_cadena|escribir|escribir_cadena|si|entonces|si_no|fin_si|mientras|hacer|fin_mientras|repetir|hasta_que|para|desde|hasta|paso|fin_para|_borrar|_lugar) 

error_Id      ({letra}({caracter}*|__+)*{caracter}*_*)|({numero}({caracter}*|_*|__+)*{caracter}*)
error_Num   ({digito}+|(\.|\,)+)({digito}+|_*|(\.|\,)+)*{digito}*


%x ESTADO_COMENTARIO
%x ESTADO_COMENTARIO_LINEA

%%


{espacio} { ; } /* saltar los espacios y los tabuladores */

{numero}			{	double d;  
                        sscanf(yytext,"%lf",&d);
                        /* Instala el numero en la tabla de simbolos */
					   	yylval.sym=install("",NUMBER, NUMBER,d); 
				   		return NUMBER;}

{cadena}	{char *c;
			c=(char*)malloc(strlen(yytext)+1);
			int  i = 1;
			int  j = 0;
			   strcpy(c, yytext);
			while (c[i] != '\0')
			  {
			    if ( ('\\' != c[i]) )
			    {
			      c[j] = c[i];	  
			    }else{
			    	i++;
			    	if('t' != c[i] && 'n' != c[i]){
			    		c[j]=c[i];
			    	}else{
			    		if('n' == c[i])
			    			c[j]='\n';
			    		else
			    			c[j]='\t';
			    	}	
			    }
			    j++;
			    i++;
			 }
			 c[j-1]='\0';
			yylval.sym=install2("", CADENA, CADENA, c);
			return CADENA;
			}

{identificador} { Symbol *s;
					int i=0;
					for(i=0; yytext[i]; i++){
						yytext[i]=tolower(yytext[i]);
					}
                   if ((s=lookup(yytext)) == 0)
                               s = install (yytext, INDEFINIDA, INDEFINIDA, 0.0);
                    yylval.sym = s;
                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

":="                    {return ASIGNACION;}
"+"                     {return SUMA;}
"-"                     {return RESTA;}
"*"                     {return PROD;}
"/"                     {return DIV;}
{_borrar}				{return TOKEN_BORRAR;}
{_lugar}				{return TOKEN_LUGAR;}
{_div}                 {return DIV_INT;}
{_mod}					{return MOD;}
"**"                    {return POT;}
"||"                    {return CONCAT;}
"<"                     {return MENOR_QUE;}
"<="                    {return MENOR_IGUAL;}
">"                     {return MAYOR_QUE;}
">="                    {return MAYOR_IGUAL;}
"="                    {return IGUAL;}
"<>"                    {return DISTINTO;}
{_o}                   {return O_LOGICO;}
{_y}                   {return Y_LOGICO;}
{_no}                  {return NO_LOGICO;}

"#"              {BEGIN ESTADO_COMENTARIO;}
<ESTADO_COMENTARIO>"#"         {BEGIN 0; ;}      
<ESTADO_COMENTARIO>.        {yymore();}
<ESTADO_COMENTARIO>\n        {yymore();}

"@"               {BEGIN ESTADO_COMENTARIO_LINEA;}
<ESTADO_COMENTARIO_LINEA>\n 	{BEGIN 0;;}
<ESTADO_COMENTARIO_LINEA>.		{yymore();}

^&       { 
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
