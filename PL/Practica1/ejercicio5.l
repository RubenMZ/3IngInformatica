/**************************** ejercicio3.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

      * Codifica un analizador que reemplace una palabra por otra en un fichero de entrada.

int count=0;
char* palabra, *palabra2;

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
                    printf("%s",palabra2);
                  }else{
                    printf("%s",yytext);
                  }
.         {ECHO;}

^#            {return 0;}

%%digito


/***** Zona de funciones auxiliares *****/

 extern FILE *yyin, *yyout;
void main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 4: 
                yyin=fopen(argv[1],"r");
                palabra=argv[2];
                palabra2=argv[3];
                yylex(); 
                printf("Apariciones de la palabra %s -> %d\n",palabra, count);
                break;

   default:     printf("Argumentos mal\n");
                break;
  }
  
}