typedef struct Symbol 
            { /* elementos de la tabla de simbolos */
	        char *nombre;
	        short tipo; /* NUMBER,VAR,FUNCION,INDEFINIDA,CONSTANTE */ 
	        union {
		       double val;      /* VAR, NUMBER, INDEFINIDA, CONSTANTE */
		       double (*ptr)(); /* FUNCION  */
		      } u;
                 struct Symbol *siguiente;
	     } Symbol;

Symbol *install(char *s, int t, double d), *lookup(char *);

typedef union Datum { /* tipo de la pila del interprete */ 
                     double val;
                     Symbol *sym;
                    } Datum;

extern Datum pop();
extern pop2();

typedef int (*Inst)(); /* instruccion maquina */
#define STOP (Inst) 0

extern Inst prog[];
extern  assign(), constpush(), dividir(), escribir(), eval(), funcion(),
        modulo(), multiplicar(), negativo(), positivo(), potencia(), restar(),
        sumar(), varpush();
