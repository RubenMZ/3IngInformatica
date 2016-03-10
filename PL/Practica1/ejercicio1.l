/**************************** ejemplo1.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Codifica un programa en flex que copie el archivo de entrada en uno de salida, 
      sumando 5 a todo número positivo que sea múltiplo de 4.

   */
#include <stdio.h>

%}
/* Definiciones regulares */

espacio		[ \t\n]
espacios	{espacio}+
letra		[a-zA-Z]
digito		[0-9]
identificador	{letra}({letra}|{digito})*
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?

/***** Zona de las reglas *****/
%%
{espacios}|{identificador}  {fprintf(yyout,"%s", yytext);}

{numero}     {if(atoi(yytext)%4==0){
                fprintf(yyout,"%d", atoi(yytext)+5);
              }else{
                fprintf(yyout,"%s", yytext);
              }
              }

^#            {return 0;}

%%


/***** Zona de funciones auxiliares *****/

 extern FILE *yyin, *yyout;
void main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 2:  yyin=fopen(argv[1],"r"); 
            break;
   case 3:  yyin=fopen(argv[1],"r"); 
            yyout=fopen(argv[2],"w"); 
  }
  yylex();
}