#include <math.h>

#include "ejemplo6.h"
#include "ejemplo6.tab.h"


/* Prototipo de una nueva funcion matematica */
extern double integer(double x), Azar();
/* Prototipos de funciones matematicas que "controlan" posibles errores" */
extern double Log(double x), Log10(double x), Exp(double x), Sqrt(double x),
              Atan2(double x, double y);

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
              } funciones0[] =  {
                          	 "azar",  Azar,
		               	  0,       0
		              	},
                funciones1 [] = {
	                       	 "seno",   sin,
		                 "coseno", cos,
		                 "atan",   atan,
		                 "log",    Log,
		                 "log10",  Log10,
		                 "exp",    Exp,
		                 "raiz",   Sqrt,
		                 "entero", integer,
		                 "abs",    fabs,
		                 0,       0
		              	},
                funciones2[] = {
                                "atan2", Atan2,
		                0,       0
		              	};

/***************************************************************************/
/** Nombre: init                                                          **/
/** Labor que desarrolla: Inserta  en la tabla de simbolos las            **/ 
/**        constantes y las funciones  que se encuentran en las           **/
/**        variables globales "consts,funciones0,funciones1 y funciones2" **/ 
/** Tipo de resultado: entero "int" (tipo por defecto)                    **/
/** Parametros: Ninguno.                                                  **/
/***************************************************************************/
void init()
{
 int i;
 Symbol *s;

 for (i=0; consts[i].nombre; i++)
       install(consts[i].nombre,CONSTANTE,consts[i].cval);

 for (i=0; funciones0[i].nombre; i++)
     {
      s=install(funciones0[i].nombre,FUNCION0_PREDEFINIDA,0.0);
      s->u.ptr=funciones0[i].func;
     }

 for (i=0; funciones1[i].nombre; i++)
     {
      s=install(funciones1[i].nombre,FUNCION1_PREDEFINIDA,0.0);
      s->u.ptr=funciones1[i].func;
     }

 for (i=0; funciones2[i].nombre; i++)
     {
      s=install(funciones2[i].nombre,FUNCION2_PREDEFINIDA,0.0);
      s->u.ptr=funciones2[i].func;
     }

}
