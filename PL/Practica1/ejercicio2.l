/**************************** ejemplo55.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Codifica un programa en flex que copie el archivo de entrada en
      uno de salida, sumando N1 a todo número positivo que sea múltiplo
      de N2, donde N1 y N2 son dos números pasados como argumentos
      desde la línea de órdenes.

   */
#include <stdio.h>
int n1, n2;

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

{numero}     {if(atoi(yytext)%n2==0){
                fprintf(yyout,"%d", atoi(yytext)+n1);
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
            n1=5;
            n2=4; 
            break;

   case 3:  yyin=fopen(argv[1],"r"); 
            yyout=fopen(argv[2],"w");
            n1=5;
            n2=4;
            break;

   case 5:  yyin=fopen(argv[1],"r"); 
            yyout=fopen(argv[2],"w");
            n1=atoi(argv[3]);
            n2=atoi(argv[4]);
            break;

   default: printf("\E[31mArgumentos mal <fich entrada><fich salida><n1><n2>\e[0m\n");
            exit(-1);
  }
  yylex();
}