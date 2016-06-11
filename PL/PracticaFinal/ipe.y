
%{
#include <stdio.h>
#include <math.h>

#include "ipe.h"

#include "macros.h"

#define code2(c1,c2)         code(c1); code(c2)
#define code3(c1,c2,c3)      code(c1); code(c2); code(c3)
%}

%union{             
       Symbol *sym;    /* puntero a la tabla de simbolos */
       Inst *inst;     /* instruccion de maquina */
}
/* Definiciones regulares */
%token <sym> NUMBER VAR CONSTANTE CADENA FUNCION0_PREDEFINIDA FUNCION1_PREDEFINIDA FUNCION2_PREDEFINIDA INDEFINIDA ESCRIBIR ESCRIBIR_CADENA MIENTRAS SI ENTONCES SI_NO FIN_SI LEER LEER_CADENA TOKEN_BORRAR TOKEN_LUGAR INICIO FIN HACER FIN_MIENTRAS REPETIR HASTA_QUE PARA DESDE HASTA PASO FIN_PARA
%type <inst> stmt asgn expr stmtlist cond mientras si para variable repetir end 

%right ASIGNACION

%left O_LOGICO
%left Y_LOGICO
%left MAYOR_QUE MENOR_QUE MENOR_IGUAL MAYOR_IGUAL DISTINTO IGUAL
%left SUMA RESTA 
%left PROD DIV DIV_INT MOD 
%left UNARIO NO_LOGICO
%left POT
%left CONCAT



/***** Zona de las reglas *****/
%%

list :    /* nada: epsilon produccion */ 
        | list stmt ';'  {code(STOP); return 1;}
        | list error ';'  {yyerrok;} 
        ;

stmt :    /* nada: epsilon produccion */  {$$=progp;}
        | asgn          {code(pop2);}
        | TOKEN_BORRAR        {code(borrar);}
        | TOKEN_LUGAR '(' expr ',' expr ')' {$$=$3;code(lugar);}
        | ESCRIBIR '(' expr ')'    {code(escribir); $$ = $3;}
        | LEER '(' VAR ')'    {code2(leervariable,(Inst)$3);}
        | ESCRIBIR_CADENA '(' expr ')'   {code(escribircadena); $$ = $3;}
        | LEER_CADENA '('  VAR  ')'    {code2(leercadena,(Inst)$3);}
        | mientras cond HACER stmtlist FIN_MIENTRAS end 
                  {
                   ($1)[1]=(Inst)$4; /* cuerpo del bucle */
                   ($1)[2]=(Inst)$6; /* siguiente instruccion al bucle */
                  }
        | si cond ENTONCES stmtlist FIN_SI end /* proposicion si sin parte si_no */
                  {
                   ($1)[1]=(Inst)$4; /* cuerpo del si */
                   ($1)[3]=(Inst)$6; /* siguiente instruccion al si */
                  }
        | si cond ENTONCES stmtlist end SI_NO stmtlist FIN_SI end/* proposicion si con parte si_no */
                  {
                   ($1)[1]=(Inst)$4; /* cuerpo del si */
                   ($1)[2]=(Inst)$7; /* cuerpo del si_no */
                   ($1)[3]=(Inst)$9; /* siguiente instruccion al si-si_no */
                  }
        | para variable DESDE expr end HASTA expr end PASO expr end HACER stmtlist FIN_PARA end 
              { 
                  ($1)[1]=(Inst)$4; /* expresion desde */ 
                  ($1)[2]=(Inst)$7; /* expresion hasta */ 
                  ($1)[3]=(Inst)$10; /* expresion paso */ 
                  ($1)[4]=(Inst)$13; /* cuerpo del bucle */ 
                  ($1)[5]=(Inst)$15; /* siguiente instruccion al para */ }
        | repetir stmtlist HASTA cond end
              {
                  ($1)[1]=(Inst)$4; /* condicion */
                  ($1)[2]=(Inst)$5; /* siguiente instruccion al si */
              }
        ;

asgn :    VAR ASIGNACION expr { $$=$3; 
                                code3(varpush,(Inst)$1,assign);}
        | CONSTANTE ASIGNACION expr 
          {execerror(" NO se pueden asignar datos a constantes ",$1->nombre);}
  ;

cond :    '(' expr ')' {code(STOP); $$ =$2;}
        ;

mientras:    MIENTRAS      {$$= code3(whilecode,STOP,STOP);}
        ;

si:       SI         {$$= code(ifcode); code3(STOP,STOP,STOP);}
        ;

para:     PARA  {$$= code3(forcode, STOP, STOP); code3(STOP, STOP, STOP);}
        ;

repetir:  REPETIR   {$$= code3(dowhilecode,STOP,STOP);}
        ;

end :    /* nada: produccion epsilon */  {code(STOP); $$ = progp;}
        ;

stmtlist:  /* nada: prodcuccion epsilon */ {$$=progp;}
        | stmtlist stmt ';'
        ;

variable: VAR {code((Inst)$1); $$ = progp;} ;

expr :    NUMBER        {$$=code2(constpush,(Inst)$1);}
        | CADENA           {$$=code3(varpush,(Inst)$1,eval);}
        | VAR           {$$=code3(varpush,(Inst)$1,eval);}
        | CONSTANTE       {$$=code3(varpush,(Inst)$1,eval);}
        | asgn
        | FUNCION0_PREDEFINIDA '(' ')'      {code2(funcion0,(Inst)$1->u.ptr);}
        | FUNCION1_PREDEFINIDA '(' expr ')' {$$=$3;code2(funcion1,(Inst)$1->u.ptr);}
        | FUNCION2_PREDEFINIDA '(' expr ',' expr ')'
                                            {$$=$3;code2(funcion2,(Inst)$1->u.ptr);}
        | '(' expr ')'    {$$ = $2;}
        /*%left SUMA RESTA 
          %left PROD DIV DIV_INT MOD POT*/
        | expr SUMA expr   {code(sumar);}
        | expr RESTA expr   {code(restar);}
        | expr PROD expr   {code(multiplicar);}
        | expr DIV expr   {code(dividir);}
        | expr DIV_INT expr   {code(dividir_int);}
        | expr MOD expr   {code(modulo);}
        | expr POT expr   {code(potencia);}
        |'-' expr %prec UNARIO  {$$=$2; code(negativo);}
        |'+' expr %prec UNARIO  {$$=$2; code(positivo);}
        /*MAYOR_QUE MENOR_QUE MENOR_IGUAL MAYOR_IGUAL DISTINTO IGUAL*/
        | expr MAYOR_QUE expr   {code(mayor_que);}
        | expr MAYOR_IGUAL expr {code(mayor_igual);}
        | expr MENOR_QUE expr   {code(menor_que);}
        | expr MENOR_IGUAL expr {code(menor_igual);}
        | expr IGUAL expr   {code(igual);}
        | expr DISTINTO expr   {code(distinto);}
        | NO_LOGICO expr  {code(negacion);}
        | expr Y_LOGICO expr  {code(y_logico);}
        | expr O_LOGICO expr  {code(o_logico);}
        | expr CONCAT expr {code(concatenacion);}
        ;

%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf begin;
char *progname;
int lineno = 1;
/* Dispositivo de entrada estándar de yylex() */
extern FILE * yyin;

void fpecatch();

int main(int argc, char *argv[])
{



 /* Si se invoca el intérprete con un fichero de entrada */
 /* entonces se establece como dispositivo de entrada para yylex() */
 if (argc == 2) yyin = fopen(argv[1],"r");


 progname=argv[0];

 /* inicializacion de la tabla de simbolos */
 init();

/* Establece un estado viable para continuar despues de un error */
 setjmp(begin);

 /* Establece cual va a ser la funcion para tratar errores de punto flotante */
 signal(SIGFPE,fpecatch); /* Excepcion de punto flotante*/

/* initcode inicializa el vector de intrucciones y la pila del interprete */
 for (initcode(); yyparse(); initcode()) execute(prog);

 return 0;

}

void yyerror(char *s)
{
 warning(s,(char *) 0);
}

void warning(char *s, char *t)
{
 fprintf(stderr," ** %s : %s", progname,s);
 if (t) fprintf(stderr," ---> %s ",t);
 fprintf(stderr,"  (linea %d)\n",lineno);
}

void execerror(s,t) /* recuperacion de errores durante la ejecucion */
char *s,*t;
{
  warning(s,t);
  longjmp(begin,0);
}

void fpecatch()     /*  atrapa errores de punto flotante */
{
 execerror("error de punto flotante ",(char *)0);
}

