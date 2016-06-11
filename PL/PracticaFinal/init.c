#include <math.h>

#include "ipe.h"
#include "ipe.tab.h"

/* Prototipo de una nueva funcion matematica */
extern double integer(double x), Azar();
/* Prototipos de funciones matematicas que "controlan" posibles errores" */
extern double Log(double x), Log10(double x), Exp(double x), Sqrt(double x),
              Atan2(double x, double y);

static struct{
              char *nombre;
	      double cval;
	      } constantes[] = {
	                    "PI",    3.14159265358979323846,
	                    "E",     2.71828182845904523536,
	                    "GAMMA", 0.57721566490153286060,
	                    "DEG",  57.29577951308232087680,
	                    "PHI",   1.61803398874989484820,
	                    0,       0
	                   };

static struct{   /* palabras clave */
              char *nombre;
	      int  kval;
	      } keywords[] = {
                   "inicio",        INICIO,
			             "fin",      FIN,
			             "leer",     LEER,
			             "leer_cadena",     LEER_CADENA,
                   "escribir",      ESCRIBIR,
                   "escribir_cadena", ESCRIBIR_CADENA,
                   "si", SI,
                   "entonces", ENTONCES,
                   "si_no",SI_NO,
                   "fin_si", FIN_SI,
                   "mientras",MIENTRAS,
                   "hacer",HACER,
                   "fin_mientras",FIN_MIENTRAS,
                   "repetir",REPETIR,
                   "hasta_que", HASTA_QUE,
                   "para", PARA,
                   "desde", DESDE,
                   "hasta", HASTA,
                   "paso", PASO,
                   "fin_para", FIN_PARA,
			      0,           0,
                             };

static struct {    /* Nombres predefinidos de funciones */ 
	       char *nombre;
	       double (*func)();
              } funciones0[] = {
                               "azar", Azar,
                                0, 0
                              },
                funciones1 [] = {
	                       "seno",   sin,
		               "coseno",   cos,
		               "atan",  atan,
		               "log",   Log,
		               "log10", Log10,
		               "exp",   Exp,
		               "raiz",  Sqrt,
		               "entero",   integer,
		               "abs",   fabs,
		               0,       0
		              },
              funciones2[] = {"atan2", Atan2,
                               0, 0
                             };
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

 for (i=0; constantes[i].nombre; i++)
       install(constantes[i].nombre,CONSTANTE, CONSTANTE, constantes[i].cval);

 for (i=0; keywords[i].nombre; i++)
       install(keywords[i].nombre,keywords[i].kval, keywords[i].kval,0.0);

 for (i=0; funciones0[i].nombre; i++)
     {
      s=install(funciones0[i].nombre,FUNCION0_PREDEFINIDA, FUNCION0_PREDEFINIDA,0.0);
      s->u.ptr=funciones0[i].func;
     }
 for (i=0; funciones1[i].nombre; i++)
     {
      s=install(funciones1[i].nombre,FUNCION1_PREDEFINIDA, FUNCION1_PREDEFINIDA,0.0);
      s->u.ptr=funciones1[i].func;
     }
 for (i=0; funciones2[i].nombre; i++)
     {
      s=install(funciones2[i].nombre,FUNCION2_PREDEFINIDA, FUNCION2_PREDEFINIDA ,0.0);
      s->u.ptr=funciones2[i].func;
     }
}

