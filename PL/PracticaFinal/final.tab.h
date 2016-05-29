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

#ifndef YY_YY_FINAL_TAB_H_INCLUDED
# define YY_YY_FINAL_TAB_H_INCLUDED
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
    FUNCION0_PREDEFINIDA = 261,
    FUNCION1_PREDEFINIDA = 262,
    FUNCION2_PREDEFINIDA = 263,
    INDEFINIDA = 264,
    ESCRIBIR = 265,
    ESCRIBIR_CADENA = 266,
    MIENTRAS = 267,
    SI = 268,
    ENTONCES = 269,
    SI_NO = 270,
    FIN_SI = 271,
    LEER = 272,
    LEER_CADENA = 273,
    TOKEN_BORRAR = 274,
    TOKEN_LUGAR = 275,
    INICIO = 276,
    FIN = 277,
    HACER = 278,
    FIN_MIENTRAS = 279,
    REPETIR = 280,
    HASTA_QUE = 281,
    PARA = 282,
    DESDE = 283,
    HASTA = 284,
    PASO = 285,
    FIN_PARA = 286,
    ASIGNACION = 287,
    O_LOGICO = 288,
    Y_LOGICO = 289,
    MAYOR_QUE = 290,
    MENOR_QUE = 291,
    MENOR_IGUAL = 292,
    MAYOR_IGUAL = 293,
    DISTINTO = 294,
    IGUAL = 295,
    SUMA = 296,
    RESTA = 297,
    PROD = 298,
    DIV = 299,
    DIV_INT = 300,
    MOD = 301,
    UNARIO = 302,
    NO_LOGICO = 303,
    POT = 304,
    CONCAT = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 14 "final.y" /* yacc.c:1909  */
             
       Symbol *sym;    /* puntero a la tabla de simbolos */
       Inst *inst;     /* instruccion de maquina */

#line 110 "final.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FINAL_TAB_H_INCLUDED  */
