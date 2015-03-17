%{
// $Id: scanner.l,v 1.2 2011-05-24 00:58:18-07 - - $

#include <stdlib.h>

#include "auxlib.h"
#include "yyextern.h"

%}

%option 8bit
%option debug
%option ecs
%option interactive
%option nodefault
%option noyywrap
%option yylineno

NUMBER  ([[:digit:]]+([-:.][[:digit:]]+)*)
WORD    ([[:alnum:]]+([-&'.][[:alnum:]]+)*)
OTHER   (.|\n)

%%

{NUMBER}        { }
{WORD}          { return 1;  }
{OTHER}         { }

%%

void yycleanup (void) {
   yy_delete_buffer (YY_CURRENT_BUFFER);
}
