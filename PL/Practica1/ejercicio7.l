

/**************************** ejercicio3.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      • Codifica un analizador léxico que permita reconocer los
componentes léxicos de un programa escrito en pseudocódigo. 

      */
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

caracter	{letra}|{digito}
identificador   {letra}({caracter})*(_{caracter})*({caracter})*   

reservada	

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
 

/***** Zona de las reglas *****/
%%

{user}    { if (opcion==1){
                if(strcmp(yytext, usuario)==0){
                  count++;
                }
            }else{
                strcpy(userAux,yytext);
            }
          }

{file}    {;}

{date}    { if(opcion==2){
                if(strcmp(fecha, yytext)==0 && strcmp(usuario, userAux)==0){
                count++;
                }
            }
          }

{time}    {;}

.|{espacio}|{linea} {;}


%%


/***** Zona de funciones auxiliares *****/

 extern FILE *yyin, *yyout;
 void main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 3: 
                yyin=fopen(argv[1],"r");
                usuario=argv[2];
                opcion=1;
                yylex();
                printf("Hay %d registros de impresion para el usuario %s\n",count,usuario ); 
                break;

   default:     printf("<in.txt><usuario>[fecha]\n");
                break;
  }
  
}