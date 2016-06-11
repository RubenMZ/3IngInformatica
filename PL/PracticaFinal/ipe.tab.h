/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_IPE_TAB_H_INCLUDED
# define YY_YY_IPE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    VAR = 259,
    CONSTANTE = 260,
    CADENA = 261,
    FUNCION0_PREDEFINIDA = 262,
    FUNCION1_PREDEFINIDA = 263,
    FUNCION2_PREDEFINIDA = 264,
    INDEFINIDA = 265,
    ESCRIBIR = 266,
    ESCRIBIR_CADENA = 267,
    MIENTRAS = 268,
    SI = 269,
    ENTONCES = 270,
    SI_NO = 271,
    FIN_SI = 272,
    LEER = 273,
    LEER_CADENA = 274,
    TOKEN_BORRAR = 275,
    TOKEN_LUGAR = 276,
    INICIO = 277,
    FIN = 278,
    HACER = 279,
    FIN_MIENTRAS = 280,
    REPETIR = 281,
    HASTA_QUE = 282,
    PARA = 283,
    DESDE = 284,
    HASTA = 285,
    PASO = 286,
    FIN_PARA = 287,
    ASIGNACION = 288,
    O_LOGICO = 289,
    Y_LOGICO = 290,
    MAYOR_QUE = 291,
    MENOR_QUE = 292,
    MENOR_IGUAL = 293,
    MAYOR_IGUAL = 294,
    DISTINTO = 295,
    IGUAL = 296,
    SUMA = 297,
    RESTA = 298,
    PROD = 299,
    DIV = 300,
    DIV_INT = 301,
    MOD = 302,
    UNARIO = 303,
    NO_LOGICO = 304,
    POT = 305,
    CONCAT = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 14 "ipe.y" /* yacc.c:1909  */
             
       Symbol *sym;    /* puntero a la tabla de simbolos */
       Inst *inst;     /* instruccion de maquina */

#line 111 "ipe.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_IPE_TAB_H_INCLUDED  */
