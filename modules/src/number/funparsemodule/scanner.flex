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

#define YY_SKIP_YYWRAP 1
#define YY_ALWAYS_INTERACTIVE 1

// this is needed to make the generated source
// compilable with vc6 on windows
#define YY_NO_UNISTD_H

#define YY_DECL int yylex(void* lval)
#define yywrap() 1

#include <stdlib.h>
#include "parser.tab.h"   /* Zeug vom Parser ! */

%}

ALPHA	[a-z]
DIGIT	[0-9]
ID	{ALPHA}({ALPHA}|{DIGIT})*
INTEGER	{DIGIT}+
EXPONENT ("e"|"E")("+"|"-")?{INTEGER}
FLOAT   {INTEGER}("."{INTEGER}?)?({EXPONENT})?

%%


{FLOAT}		{ 
                  YYSTYPE* lvalp = (YYSTYPE*) lval;
                  lvalp->num = atof(yytext);
                  return NUMBER;
                }
"+"		{ return PLUS; }
"-"		{ return MINUS; }
"*"		{ return TIMES; }
"/"		{ return DIV;	}
"%"		{ return MODULO; }
"^"		{ return HOCH;	}
";"		{ return SEMICOLON; }
","		{ return KOMMA;	}
"|"             { return PIPE; }
"("		{ return KLAUF; }
")"		{ return KLZU; }
{ID}		{
                  YYSTYPE* lvalp = (YYSTYPE*) lval;
                  lvalp->text = strdup(yytext);
                  return ID;
                }
"\n"            { return EOL; }



[ \t]+          /* eat up whitespace */    
	
.  { fprintf (stderr,"Fehler beim Scannen. Ungültiges Token : %s \n",yytext); }

%%
