/**************************** ejemplo2.l ***********************************/

/***** Zona de las declaraciones o definiciones *****/
%{
   /*
      Descripción: el analizador léxico distingue entre verbos y no verbos
   */
%}

/***** Zona de las reglas *****/
%%

[\t ]+	      ;	/* Se ignoran los espacios en blanco */ 

es |
soy |
eres |
eramos |
era |
ser |
siendo |
sido |
hacer |
hace |
hizo |
puede |
podia |
tiene |
tener |
tenia |
ir		{ printf("%s: es un verbo\n", yytext); }

[a-zA-Z]+ 	{ printf("%s: no es un verbo\n", yytext); }

.|\n		{ ECHO; /* resto de cadenas */ }
%%


/***** Zona de funciones auxiliares *****/

main()
{
	yylex();
}