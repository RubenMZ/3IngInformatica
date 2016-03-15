/**************************** ejercicio3.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Elaborar un programa de flex que reciba un fichero de texto y cuente el número de caracteres, palabras y líneas que contiene
   */
#include <stdio.h>
#include <string.h>

int palabra=0;
int caracter=0;
int lineas=0;
%}
/* Definiciones regulares */

espacio		[ \t]
espacios	{espacio}+
linea           [\n]
letra		[a-zA-Z]
digito		[0-9]       
palabra	        {letra}({letra}|{digito})*
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?

/***** Zona de las reglas *****/
%%

{palabra}       {palabra++;
                caracter+=strlen(yytext);
                }

{espacio}|{digito}|{letra}      {caracter++;}

{linea}         {lineas++;
                caracter++;}

^#            {return 0;}

%%


/***** Zona de funciones auxiliares *****/

 extern FILE *yyin, *yyout;
void main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 2:      yyin=fopen(argv[1],"r");
                yylex(); 
                printf("Palabras: %d\n",palabra);
                printf("Caracteres: %d\n",caracter);
                printf("Lineas: %d\n",lineas);
                break;

   default:     printf("Argumentos mal\n");
                break;
  }
  
}