
%{
/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#define YYERROR_VERBOSE
#define YYPARSE_PARAM parm

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

#include "slist.h"

#include "builtin_functions.h"

/*---------------------------------------------------------------------------*/

%}
//%semantic_parser
%pure-parser

%union
{
  struct slist_s_t* list;
  struct expression_s_t* expr;
  char*        text;
  double       num;
};

/* Token des Scanners */
%token <num> NUMBER
%token <text> HOCH
%token <text> TIMES
%token <text> MODULO
%token <text> DIV
%token <text> PLUS
%token <text> MINUS
%token <text> EOL
%token <text> SEMICOLON
%token <text> KLAUF
%token <text> KLZU
%token <text> ID
%token <text> KOMMA
%token <text> PIPE

/* Assoziativitäten und Prioritäten (TIMES bindet stärker als PLUS...) */
%left ID
%left PLUS MINUS
%left NEGATION
%left TIMES DIV MODULO
%left HOCH

%type <list>  exp_list;
%type <expr>  exp;

/* Erwarte line (s.u.) als Eingabe            */
%start start

/* Die Grammatik sollte relativ klar sein.... */

%%

start: exp                           {
                                       expression_t* e = (expression_t*) parm;
                                       *e = $1;
                                     }


exp:	NUMBER                	     { 
               			       $$ = expression_create_const($1);
				     }
     	| exp PLUS exp        	     { 
                                       slist_t args = slist_create();
                                       slist_push_front(args, $3);
                                       slist_push_front(args, $1);
 				       $$ = expression_create_builtin(add_fun,
                                                                      args);
 				     }
     	| exp MINUS exp       	     { 
                                       slist_t args = slist_create();
                                       slist_push_front(args, $3);
                                       slist_push_front(args, $1);
 				       $$ = expression_create_builtin(sub_fun,
                                                                      args);
                                     }
        | exp TIMES exp       	     { 
                                       slist_t args = slist_create();
                                       slist_push_front(args, $3);
                                       slist_push_front(args, $1);
 				       $$ = expression_create_builtin(mul_fun,
                                                                      args);
                                     }
        | exp DIV exp         	     { 
                                       slist_t args = slist_create();
                                       slist_push_front(args, $3);
                                       slist_push_front(args, $1);
 				       $$ = expression_create_builtin(div_fun,
                                                                      args);
                                     }
        | exp HOCH exp         	     { 
                                       slist_t args = slist_create();
                                       slist_push_front(args, $3);
                                       slist_push_front(args, $1);
 				       $$ = expression_create_builtin(pow_fun,
                                                                      args);
                                     }
        | exp MODULO exp      	     { 
                                       slist_t args = slist_create();
                                       slist_push_front(args, $3);
                                       slist_push_front(args, $1);
 				       $$ = expression_create_builtin(mod_fun,
                                                                      args);
                                     }
        | MINUS exp %prec NEGATION   { 
                                       slist_t args = slist_create();
                                       slist_push_front(args, $2);
 				       $$ = expression_create_builtin(neg_fun,
                                                                      args);
	                             }
        | PIPE exp PIPE              {
                                       slist_t args = slist_create();
                                       slist_push_front(args, $2);
                                       $$ = expression_create_builtin(abs_fun,
                                                                      args);
                                     }

        | ID                         {
	                               $$ = expression_create_var($1)
	                             }
        | ID KLAUF exp_list KLZU     { 
	                                $$ = expression_create_fun($1, $3); 
                                        free($1);
	                             }

	| KLAUF exp KLZU	     { 
   					$$=$2;       
 				     }
     ;

exp_list: exp            	     { 
                                       $$ = slist_create();
                                       slist_push_front($$, $1);
				     }
	 | exp KOMMA exp_list        { 
				       $$ = $3;
	                               slist_push_front($$, $1);
                                     }
    ;

%%   /* Grammatik endet hier */


int yyerror (char *s)  /* Called by yyparse on error */
{
 return fprintf(stderr, "%s\n", s);
}                  

int parse_expression(expression_t* exp, const char *s)
{
  //TODO: return code!
  yy_scan_string(s);

  if (*exp != 0)
    {
      expression_free(*exp);
      *exp = 0;
    }

  yyparse(exp); 

  if (*exp == 0)
    return 0;

  return 1;
}
