

/**************************** ejercicio3.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      • Codifica un analizador léxico que permita reconocer los
componentes léxicos de un programa escrito en pseudocódigo. 

      */
#include <stdio.h>
#include <string.h>
#include "ejercicio7.h"   


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

reservada	{inicio|fin|__mod|__o|__y|__no|leer|escribir|si|entonces|si_no|fin_si|mientras|hacer|fin_mientras|repetir|hasta_que|para|desde|hasta|paso|fin_para} 

inicio		[iI][nN][iI][cC][iI][o]
fin 		[fF][iI][nN]
__mod 		__[mM][oO][dD]
__o 		__[oO]
__y 		__[yY]
__no 		__[nN][oO]
leer 		[lL][eE]{2}[rR]
escribir 	[eE][sS][cC][rR][iI][bB][iI][rR]
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
 
cadena          \'(.)*\'


error_Id      ({letra}({caracter}*|__+)*{caracter}*_*)|({numero}({caracter}*|_*|__+)*{caracter}*)
error_Num   ({digito}+|(\.|\,)+)({digito}+|_*|(\.|\,)+)*{digito}*

%x ESTADO_COMENTARIO
%x ESTADO_CADENA
/***** Zona de las reglas *****/
%%

{inicio}        {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,INICIO);}
{fin}           {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,FIN);}
{leer}          {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,LEER);}
{escribir}      {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,ESCRIBIR);}
{si}            {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,SI);}
{entonces}      {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,ENTONCES);}
{si_no}         {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,SI_NO);}
{fin_si}        {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,FIN_SI);}
{mientras}      {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,MIENTRAS);}
{hacer}         {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,HACER);}
{fin_mientras}  {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,FIN_MIENTRAS);}
{repetir}       {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,REPETIR);}
{hasta_que}     {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,HASTA_QUE);}
{para}          {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,PARA);}
{desde}         {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,DESDE);}
{hasta}         {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,HASTA);}
{paso}          {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,PASO);}
{fin_para}      {printf("\E[32mPALABRA RESERVADA <%s> con token num = %d\n\e[0m",yytext,FIN_PARA);}

{identificador} {printf(" => IDENTIFICADOR <%s> con token num = %d\n",yytext, ID);}

{numero}        {printf("\E[35m $ NUMERO $ <%s> con token num = %d\n\e[0m",yytext, NUM);}



":="                    {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext,ASIGNACION);}
"+"                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, SUMA);}
"-"                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, RESTA);}
"*"                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, PRODUCTO);}
"/"                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, DIVISION);}
{__mod}                 {printf("\E[34m PALABRA RESERVADA Y OPERADOR <%s> con token num = %d\n\e[0m", yytext, __MOD);}
"**"                    {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, POTENCIA);}
"||"                    {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, CONCATENACION);}
"<"                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, MENOR_QUE);}
"<="                    {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, MENOR_IGUAL_QUE);}
">"                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, MAYOR_QUE);}
">="                    {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, MAYOR_IGUAL_QUE);}
"=="                    {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, IGUAL);}
"<>"                    {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, DISTINTO);}
{__o}                   {printf("\E[34m PALABRA RESERVADA Y OPERADOR <%s> con token num = %d\n\e[0m", yytext, __O);}
{__y}                   {printf("\E[34m PALABRA RESERVADA Y OPERADOR <%s> con token num = %d\n\e[0m", yytext, __Y);}
{__no}                  {printf("\E[34m PALABRA RESERVADA Y OPERADOR <%s> con token num = %d\n\e[0m", yytext, __NO);}
";"                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, FIN_SENTENCIA);}
")"                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, PARENTESISDER);}
"("                     {printf("\E[34m OPERADOR <%s> con token num = %d\n\e[0m", yytext, PARENTESISIZQ);}

{error_Id}                {printf("\E[31mERROR. Identificador incorrecto <%s>\n\e[0m",yytext);}

{error_Num}               {printf("\E[31mERROR. Numero incorrecto <%s>\n\e[0m",yytext);}

"#".*               {printf("\E[33mCOMENTARIO # de una linea con token %d : \n\e[0m%s\n", COMENTARIO_LINEA, yytext);}


"(*"              {
                  /* Se activa el reconocimiento de un comentario */
                  BEGIN ESTADO_COMENTARIO;
                  printf("\E[33m* COMENTARIO * con token num = %d :\n\e[0m", COMENTARIO);
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
                  printf("\E[33m //CADENA con token %d : \n\e[0m", CADENA);
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
   case 2: 
                yyin=fopen(argv[1],"r");
                yylex();
                break;

   default:     printf("<in.txt>\n");
                break;
  }
  
}