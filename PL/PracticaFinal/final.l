
%{

#include <stdio.h>
#include <string.h> 


%}
/* Definiciones regulares */

espacio		[ \t]
espacios	{espacio}+
linea           [\n]
letra		[a-zA-Z]
digito		[0-9]
    
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?

caracter	[a-zA-Z]|[0-9]
identificador   {letra}({caracter})*(_{caracter})*({caracter})*   


inicio		[iI][nN][iI][cC][iI][o]
fin 		[fF][iI][nN]
__mod 		__[mM][oO][dD]
__div     __[dD][iI][vV]
__o 		__[oO]
__y 		__[yY]
__no 		__[nN][oO]
leer 		[lL][eE]{2}[rR]
leer_cadena   [lL][eE]{2}[rR]_[cC][aA][dD][eE][nN][aA]
escribir 	[eE][sS][cC][rR][iI][bB][iI][rR]
escribir_cadena  [eE][sS][cC][rR][iI][bB][iI][rR]_[cC][aA][dD][eE][nN][aA]
si 		[sS][iI]
entonces 	[eE][nN][tT][oO][nN][cC][eE][sS]
si_no		[sS][iI]_[nN][oO]
fin_si		[fF][iI][nN]_[sS][iI]
mientras 	[mM][iI][eE][nN][tT][rR][aA][sS]
hacer		[hH][aA][cC][eE][rR]
fin_mientras  	[fF][iI][nN]_[mM][iI][eE][nN][tT][rR][aA][sS]
repetir 	[rR][eE][pP][eE][tT][iI][rR]
hasta_que 	[hH][aA][sS][tT][aA]_[qQ][uU][eE]
para 		[pP][aA][rR][aA]
desde 		[dD][eE][sS][dD][eE]
hasta 		[hH][aA][sS][tT][aA]
paso 		[pP][aA][sS][oO]
fin_para 	[fF][iI][nN]_[pP][aA][rR][aA]
__borrar  (?i:__borrar)
__lugar   (?i:__lugar)

cadena          \'(.)*\'

reservada (inicio|fin|__mod|__div|__o|__y|__no|leer|leer_cadena|escribir|escribir_cadena|si|entonces|si_no|fin_si|mientras|hacer|fin_mientras|repetir|hasta_que|para|desde|hasta|paso|fin_para|__borrar|__lugar) 

error_Id      ({letra}({caracter}*|__+)*{caracter}*_*)|({numero}({caracter}*|_*|__+)*{caracter}*)
error_Num   ({digito}+|(\.|\,)+)({digito}+|_*|(\.|\,)+)*{digito}*

%x ESTADO_COMENTARIO
%x ESTADO_CADENA


/***** Zona de las reglas *****/
%%

{reservada}   {printf("la detecta antes\n");}

{inicio}        {printf("Detecta reservada\n");}
{fin}           {printf("Detecta reservada\n");}
{leer}          {printf("Detecta reservada\n");}
{escribir}      {printf("Detecta reservada\n");}
{si}            {printf("Detecta reservada\n");}
{entonces}      {printf("Detecta reservada\n");}
{si_no}         {printf("Detecta reservada\n");}
{fin_si}        {printf("Detecta reservada\n");}
{mientras}      {printf("Detecta reservada\n");}
{hacer}         {printf("Detecta reservada\n");}
{fin_mientras}  {printf("Detecta reservada\n");}
{repetir}       {printf("Detecta reservada\n");}
{hasta_que}     {printf("Detecta reservada\n");}
{para}          {printf("Detecta reservada\n");}
{desde}         {printf("Detecta reservada\n");}
{hasta}         {printf("Detecta reservada\n");}
{paso}          {printf("Detecta reservada\n");}
{fin_para}      {printf("Detecta reservada\n");}
{__borrar}      {printf("Detecta reservada\n");}
{__lugar}       {printf("Detecta reservada\n");}

{identificador} {printf("Detecta id\n");}

{numero}        {printf("Detecta id\n");}



":="                    {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"+"                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"-"                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"*"                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"/"                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
{__mod}                 {printf("\E[34m PALABRA RESERVADA Y OPERADOR <%s> con token num =\n\e[0m", yytext);}
"**"                    {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"||"                    {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"<"                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"<="                    {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
">"                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
">="                    {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"=="                    {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"<>"                    {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
{__o}                   {printf("\E[34m PALABRA RESERVADA Y OPERADOR <%s> con token num =\n\e[0m", yytext);}
{__y}                   {printf("\E[34m PALABRA RESERVADA Y OPERADOR <%s> con token num =\n\e[0m", yytext);}
{__no}                  {printf("\E[34m PALABRA RESERVADA Y OPERADOR <%s> con token num =\n\e[0m", yytext);}
";"                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
")"                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}
"("                     {printf("\E[34m OPERADOR <%s> con token num =\n\e[0m", yytext);}

{error_Id}                {printf("\E[31mERROR. Identificador incorrecto <%s>\n\e[0m",yytext);}

{error_Num}               {printf("\E[31mERROR. Numero incorrecto <%s>\n\e[0m",yytext);}

"#".*               {printf("\E[33mCOMENTARIO # de una linea con token : \n\e[0m%s\n", yytext);}


"(*"              {
                  /* Se activa el reconocimiento de un comentario */
                  BEGIN ESTADO_COMENTARIO;
                  printf("\E[33m* COMENTARIO * con token num = :\n\e[0m");
                  ECHO;

                  }

<ESTADO_COMENTARIO>"(*"/(.|\n)  {
                                printf("\n Comentario mal anidado\n");
                                ECHO; 
                                return 0;
                                }

<ESTADO_COMENTARIO>"*)"         { /* Fin del comentario: se vuelve al estado por defecto */
                                printf("%s\n", yytext);
                                BEGIN 0; 
                                }      

<ESTADO_COMENTARIO>[.\n]        {ECHO;}



"'"              {
                  BEGIN ESTADO_CADENA;
                  printf("\E[33m //CADENA con token : \n\e[0m");
                  ECHO;
                  }

<ESTADO_CADENA>"\\\'"(.)  {ECHO; 
                                }

<ESTADO_CADENA>"'"         { /* Fin del comentario: se vuelve al estado por defecto */
                                printf("%s\n", yytext);
                                BEGIN 0; 
                                }      

<ESTADO_CADENA>[.\n]        {ECHO;}

{espacio}|{linea}     {;}

.               {printf("\E[31mERROR. Caracter incorrecto <%s>\n\e[0m", yytext);}

%%


/***** Zona de funciones auxiliares *****/

 extern FILE *yyin, *yyout;
 void main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 1: 
                yylex();
                break;

   default:     printf("Este ejercicio no requiere argumentos\n");
                break;
  }
  
}