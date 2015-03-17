%{
// $Id: scanner.l,v 1.1 2013-10-28 11:10:46-07 - - $

#include "auxlib.h"
#include "lyutils.h"

#define YY_USER_ACTION  { scanner_useraction (); }
#define IGNORE(THING)   { }

%}

%option 8bit
%option debug
%option ecs
%option nodefault
%option nounput
%option noyywrap
%option perf-report
%option verbose
%option warn

LETTER          [A-Za-z_]
DIGIT           [0-9]
INTEGER         ({DIGIT}+)
CHARCONST	(([^\\\n]|\\[\\"0nt]))
STRINGCONST	(\"([^\\"\n]|\\[\\"0nt])*\")
IDENT           ({LETTER}({LETTER}|{DIGIT})*)

%%

void|bool|char|int|string|struct|if|else {return yylval_token (PATTERN); }
while|return|new|false|true|null|ord|chr {return yylval_token (PATTERN); }

"#".*           { scanner_include(); }
[ \t]+          { IGNORE (white space) }
\n              { scanner_newline(); }

{IDENT}         { return yylval_token (IDENT); }
{DIGIT}		{ return yylval_token (NUMBER); }

"=="|"[]"|"!="	{ return yylval_token (SPECIAL); }
"<="|">="	{ return yylval_token (SPECIAL); }
"="             { return yylval_token ('='); }
"<"		{ return yylval_token ('<'); }
">"		{ return yylval_token ('>'); }
"+"             { return yylval_token ('+'); }
"-"             { return yylval_token ('-'); }
"*"             { return yylval_token ('*'); }
"/"             { return yylval_token ('/'); }
"%"		{ return yylval_token ('%'); }
"!"		{ return yylval_token ('!'); }
"("             { return yylval_token ('('); }
")"             { return yylval_token (')'); }
"["		{ return yylval_token ('['); }
"]"		{ return yylval_token (']'); }
"{"		{ return yylval_token ('{'); }
"}"		{ return yylval_token ('}'); }
";"             { return yylval_token (';'); }
","		{ return yylval_token (','); }
"."		{ return yylval_token ('.'); }

{CHARCONST}	{ return yylval_token (CHAR); }
{STRINGCONST}	{ return yylval_token (STR); }

.               { scanner_badchar (*yytext); }

%%

RCSC("$Id: scanner.l,v 1.1 2013-10-28 11:10:46-07 - - $")

