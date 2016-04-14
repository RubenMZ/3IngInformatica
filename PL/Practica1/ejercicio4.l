/**************************** ejercicio3.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Codifica un programa flex que reciba un fichero de texto y una palabra y cuente el número veces que aparece dicha palabra en el fichero.
   */
#include <stdio.h>
#include <string.h>

int count=0;
char* palabra;

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

{palabra}       {if(strcmp(palabra,yytext)==0){
                    count++;
                  }
                  }
.|{espacio}|{linea}         {;}


%%


/***** Zona de funciones auxiliares *****/

 extern FILE *yyin, *yyout;
void main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 3: 
                yyin=fopen(argv[1],"r");
                palabra=argv[2];
                yylex(); 
                printf("\E[32mApariciones de la palabra %s -> %d\n\e[0m",palabra, count);
                break;

   default:     printf("\E[31mArgumentos mal <in.txt><palabra>\n\e[0m");
                break;
  }
  
}