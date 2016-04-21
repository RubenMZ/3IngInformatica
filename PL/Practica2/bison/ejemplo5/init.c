/* init.c */
#include "ejemplo5.h"
#include "ejemplo5.tab.h"
#include <math.h>

/* Prototipo de una nueva funcion matematica */
extern double integer(double x);
/* Prototipos de funciones matematicas que "controlan" posibles errores" */
extern double Log(double x), Log10(double x), Exp(double x), Sqrt(double x);

/* Constantes predefinidas */
static struct{
              char *nombre;
	      double cval;
	      } consts[] = {
	                    "PI",    3.14159265358979323846,
	                    "E",     2.71828182845904523536,
	                    "GAMMA", 0.57721566490153286060,
	                    "DEG",  57.29577951308232087680,
	                    "PHI",   1.61803398874989484820,
	                    0,       0
	                   };

/* Funciones predefinidas */ 
static struct {    
	       char *nombre;
	       double (*func)();
              } funciones [] = {
	                       "sin",   sin,
		               "cos",   cos,
		               "atan",  atan,
		               "log",   Log,
		               "log10", Log10,
		               "exp",   Exp,
		               "sqrt",  Sqrt,
		               "int",   integer,
		               "abs",   fabs,
		               0,       0
		              };

/* Instalacion de las constantes y de las funciones predefinidas 
  en la tabla de simbolos */

/************************************************************************/
/** Nombre: init                                                       **/
/** Labor que desarrolla: Inserta  en la tabla de simbolos las         **/ 
/**        constantes y las funciones  que se encuentran en las        **/
/**        variables globales "consts" y "funciones"                   **/ 
/** Tipo de resultado: entero "int" (tipo por defecto)                 **/
/** Parametros: Ninguno.                                               **/
/************************************************************************/
void init()
{
 int i;
 Symbol *s;

 for (i=0; consts[i].nombre; i++)
       install(consts[i].nombre,VAR,consts[i].cval);

 for (i=0; funciones[i].nombre; i++)
     {
      s=install(funciones[i].nombre,FUNCION_PREDEFINIDA,0.0);
      s->u.ptr=funciones[i].func;
     }
}
