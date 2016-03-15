/**************************** ejercicio3.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      • Considérese un fichero de registro que contiene información sobre los ficheros que se han imprimido en una impresora.
      • Cada línea tiene la siguiente información:
            usuario fichero fecha hora
      • Codifica un analizador léxico que permita
          o Contar cuántos trabajos ha imprimido un usuario
              El programa recibirá como argumentos
              • el nombre del fichero de registro
              • el nombre del usuario
          o Contar cuántos trabajos ha imprimido un usuario cada día
              • el nombre del fichero de registro
              • el nombre del usuario
              • el día que se desea consultar. 
      */
#include <stdio.h>
#include <string.h>

char *usuario, *fecha, userAux[1000];
int count=0;
int opcion=0;

%}
/* Definiciones regulares */

espacio		[ \t]
espacios	{espacio}+
linea           [\n]
letra		[a-zA-Z]
digito		[0-9]
word      {letra}({letra}|{digito})*       
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?

user    {letra}({letra}|{digito})*
file    ({word}\.{word})
date    ({digito}{1,2}\/{digito}{1,2}\/{digito}{4})
time    {digito}+\:{digito}{digito}

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

  case 4:       yyin=fopen(argv[1],"r");
                usuario=argv[2];
                fecha=argv[3];
                opcion=2;
                yylex(); 
                printf("Hay %d registros de impresion para el usuario %s en el dia %s\n",count,usuario, fecha); 
                break;

   default:     printf("<in.txt><usuario>[fecha]\n");
                break;
  }
  
}