/**************************** ejercicio3.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Codifica un analizador que reemplace una palabra por otra en un fichero de entrada.
      */
#include <stdio.h>
#include <string.h>

char *palabra, *palabra2;

%}
/* Definiciones regulares */

espacio		[ \t]
espacios	{espacio}+
linea           [\n]
letra		[a-zA-Z]
digito		[0-9]       
cadena	        {letra}({letra}|{digito})*
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?

/***** Zona de las reglas *****/
%%
.|{linea}|{espacio} {fprintf(yyout, "%s", yytext);}

{cadena}       {if(strcmp(palabra,yytext)==0){
                    fprintf(yyout, "%s",palabra2);
                  }else{
                    fprintf(yyout,"%s",yytext);
                  }
                }


%%


/***** Zona de funciones auxiliares *****/

 extern FILE *yyin, *yyout;
 void main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 5: 
                yyin=fopen(argv[1],"r");
                yyout=fopen(argv[2],"w");
                palabra=argv[3];
                palabra2=argv[4];
                yylex(); 
                break;

   default:     printf("<in.txt><out.txt><palabra><palabraReemplazar>\n");
                break;
  }
  
}