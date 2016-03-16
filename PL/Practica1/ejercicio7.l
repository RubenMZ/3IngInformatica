

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

%x ESTADO_COMENTARIO
/***** Zona de las reglas *****/
%%

{inicio}        {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,INICIO);}
{fin}           {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,FIN);}
{__mod}         {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,__MOD);}
{__o}           {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,__O);}
{__y}           {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,__Y);}
{__no}          {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,__NO);}
{leer}          {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,LEER);}
{escribir}      {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,ESCRIBIR);}
{si}            {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,SI);}
{entonces}      {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,ENTONCES);}
{si_no}         {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,SI_NO);}
{fin_si}        {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,FIN_SI);}
{mientras}      {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,MIENTRAS);}
{hacer}         {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,HACER);}
{fin_mientras}  {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,FIN_MIENTRAS);}
{repetir}       {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,REPETIR);}
{hasta_que}     {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,HASTA_QUE);}
{para}          {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,PARA);}
{desde}         {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,DESDE);}
{hasta}         {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,HASTA);}
{paso}          {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,PASO);}
{fin_para}      {printf("PALABRA RESERVADA <%s> con token num = %d\n",yytext,FIN_PARA);}

{identificador} {printf(" => IDENTIFICADOR <%s> con token num = %d\n",yytext, ID);}

{numero}        {printf(" $ NUMERO $ <%s> con token num = %d\n",yytext, NUM);}

.|{espacio}|{linea}     {;}


"(*"              {
                  /* Se activa el reconocimiento de un comentario */
                  BEGIN ESTADO_COMENTARIO;
                  printf("* COMENTARIO * con token num = %d :\n", COMENTARIO);
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

"#".*               {printf("# COMENTARIO de una linea con token %d : \n%s\n", COMENTARIO_LINEA, yytext);}

{cadena}             {printf("# CADENA con token %d : \n%s\n", CADENA, yytext);}

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