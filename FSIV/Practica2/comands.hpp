#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <iostream>


struct CLIParams
{
  CLIParams ()
    : entero(0), //Valores por defecto de los argumentos opcionales.
      flotante(0.0),
      cadena(""),
      verbose(false)
    {}
  int entero;
  float flotante;  
  const char * cadena;
  bool verbose;
};

static void mostrarUso (const char * progname) throw ();
static int parseCLI (int argc, char* const* argv, CLIParams& params) throw ();

#endif