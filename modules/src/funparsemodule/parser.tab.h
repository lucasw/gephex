/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     HOCH = 259,
     TIMES = 260,
     MODULO = 261,
     DIV = 262,
     PLUS = 263,
     MINUS = 264,
     EOL = 265,
     SEMICOLON = 266,
     KLAUF = 267,
     KLZU = 268,
     ID = 269,
     KOMMA = 270,
     PIPE = 271,
     NEGATION = 272
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define HOCH 259
#define TIMES 260
#define MODULO 261
#define DIV 262
#define PLUS 263
#define MINUS 264
#define EOL 265
#define SEMICOLON 266
#define KLAUF 267
#define KLZU 268
#define ID 269
#define KOMMA 270
#define PIPE 271
#define NEGATION 272




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 45 "./parser.y"
{
  struct slist_s_t* list;
  struct expression_s_t* expr;
  char*        text;
  double       num;
}
/* Line 1529 of yacc.c.  */
#line 90 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



