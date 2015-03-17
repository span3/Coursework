%{

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "lyutils.h"
#include "astree.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYMALLOC yycalloc

static void* yycalloc (size_t size);

%}

%debug
%defines
%error-verbose
%token-table
%verbose

%destructor { error_destructor ($$); } <>

%token  ROOT IDENT INTEGER STRINGCONST CHARCONST
%token	NUMBER CHAR STR VOID BOOL INT STRING
%token  STRUCT IF ELSE WHILE RETURN NEW FALSE TRUE NUL ORD CHR
%token  EQEQ ARRAY NOTEQ LESSEQ GREATEQ TYPEID
%token  TYPE FIELD INDEX BINOP BASETYPE BLOCK IFELSE VARDECL POS NEG FUNCTION VARIABLE CONSTANT CALL

%nonassoc t
%nonassoc e
%right  IF ELSE
%right  '='
%right	EQEQ NOTEQ '<' LESSEQ '>' GREATEQ
%left   '+' '-'
%left   '*' '/' '%'
%right  POS NEG '!' ORD CHR
%nonassoc '[' '.'

%start  program


%%

program : program structdef 	{free_ast($1);$$ = adopt1 ($1,$2);}
	| program function	{free_ast($1);$$ = adopt1 ($1,$2);}
	| program statement	{free_ast($2);$$ = adopt1 ($1,$2);}
	| program error '}'	{$$ = $1;}
	| program error ';'	{$$ = $1;}
	|			{$$ = new_parseroot();}
	;

structdef	: STRUCT IDENT '{' structdecl '}' 	{free_ast($3); free_ast($5); $$ = adopt2 (new_astree(STRUCT, " "), $2, $4);}
		| STRUCT IDENT '{' '}'			{free_ast($3); free_ast($4); $$ = adopt1 (new_astree(STRUCT, " "), $2);}
		;

structdecl	: structdecl decl ';'	{ $$ = adopt1 (new_astree(TYPE, " "),$2); free_ast($3);}
		| decl ';'		{ $$ = $1; free_ast ($2);}		
		;

decl	: type IDENT	{$$ = adopt1 (new_astree(TYPE, " "), $2);}
	;

type	: basetype ARRAY	{$$ = adopt2 (new_astree(TYPE, " "),$1, new_astree(ARRAY, " "));}
	| basetype		{$$ = adopt1 (new_astree(TYPE, " "), $1);}
	;

basetype: VOID		{$$ = adopt1(new_astree(BASETYPE, " "), $1);}
	| BOOL		{$$ = adopt1(new_astree(BASETYPE, " "), $1);}
	| CHAR		{$$ = adopt1(new_astree(BASETYPE, " "), $1);}
	| INT		{$$ = adopt1(new_astree(BASETYPE, " "), $1);}
	| STRING	{$$ = adopt1(new_astree(BASETYPE, " "), $1);}
	| IDENT		{$$ = adopt1(new_astree(BASETYPE, " "), adopt1sym ($1, NULL, TYPEID));}
	;

function: decl '(' functdecl ')' block		{free_ast($2); free_ast($4); $$ = adopt3 (new_astree(FUNCTION, " "),$1,$3,$5);}
	| decl '(' ')' block			{free_ast($2); free_ast($3); $$ = adopt2(new_astree(FUNCTION, " "), $1, $4);}
	;

functdecl:decl			{$$ = $1;}
	| functdecl ',' decl	{free_ast($2); $$ = adopt1($1, $3);}
	;

block	: '{' blockstate '}' 		{free_ast($1); free_ast($3); $$ = adopt1(new_astree(BLOCK, " "),$2);}
	| '{' '}'			{free_ast($1); free_ast($2); $$ = adopt1sym($$, $1, BLOCK);}
	| ';'				{$$ = $1;}
	;

blockstate: blockstate statement	{$$ = adopt1($1,$2);}
	| statement				{$$ = $1;}
	;

statement: block	{$$ = $1;}
	|  vardecl	{$$ = $1;}
	|  while	{$$ = $1;}
	|  ifelse	{$$ = $1;}
	|  return	{$$ = $1;}
	|  expr ';'	{free_ast($2); $$ = $1;}
	;

vardecl	: type IDENT '=' expr ';'	{free_ast($3); free_ast($5); $$ = adopt3(new_astree(VARDECL, " "),$1,$2,$4);}
	;

while	: WHILE '(' expr ')' statement	{free_ast($2); free_ast($4); $$ = adopt2($1,$3,$5);}
	;

ifelse	: IF '(' expr ')' statement %prec t			{free_ast($2); free_ast($4); $$ = adopt2($1,$3,$5);}
	| IF '(' expr ')' statement ELSE statement %prec e	{free_ast($2); free_ast($4); $$ = adopt2(adopt1sym($1,$3,IFELSE), $5, $7);}
	;

return	: RETURN expr ';'	{free_ast($3); $$ = adopt1($1,$2);}
	| RETURN ';'		{free_ast($2); $$ = adopt1sym($1,NULL,RETURN);}
	;

expr	: binop			{$$ = $1;}
	| unop			{$$ = $1;}
	| allocator		{$$ = $1;}
	| call			{$$ = $1;}
	| '(' expr ')'		{free_ast($1); free_ast($3); $$ = $2;}
	| variable		{$$ = adopt1(new_astree(VARIABLE, " "),$1);}
	| constant		{$$ = adopt1(new_astree(CONSTANT, " "),$1);}
	;

binop	: expr '=' expr		{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr EQEQ expr	{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr NOTEQ expr	{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr '<' expr		{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr LESSEQ expr	{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr '>' expr		{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr GREATEQ expr	{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr '+' expr		{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr '-' expr		{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr '*' expr		{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr '%' expr		{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	| expr '/' expr		{$$ = adopt3(new_astree(BINOP, " "),$1,$2,$3);}
	;

unop	: '+' expr %prec POS	{$$ = adopt1sym($1,$2,POS);}
	| '-' expr %prec NEG	{$$ = adopt1sym($1,$2,NEG);}
	| '!' expr		{$$ = adopt1($1,$2);}
	| ORD expr		{$$ = adopt1($1,$2);}
	| CHR expr		{$$ = adopt1($1,$2);}
	;

allocator: NEW basetype '(' ')'		{free_ast($3); free_ast($4); $$ = adopt1(new_astree(NEW, " "),$2);}
	| NEW basetype '(' expr ')'	{free_ast($3); free_ast($5); $$ = adopt2(new_astree(NEW, " "),$2,$4);}
	| NEW basetype '[' expr ']'	{free_ast($3); free_ast($5); $$ = adopt3(new_astree(NEW, " "),$2,new_astree(ARRAY, " "),$4);}
	;

variable: IDENT			{$$ = $1;}
	| expr '[' expr ']'	{free_ast($4); $$ = adopt1(adopt1sym($2,$1,INDEX),$3);}
	| expr '.' IDENT	{$$ = adopt2($2,$1,adopt1sym($3,NULL,FIELD));}
	;

call	: callexpr ')'		{free_ast($2); $$ = $1;}
	| IDENT '(' ')'		{free_ast($2); free_ast($3); $$ = adopt1(new_astree(CALL, " "),$1);}
	;

callexpr: callexpr ',' expr			{free_ast($2); $$ = adopt1($1,$3);}
	| IDENT '(' expr			{$$ = adopt2(new_astree(CALL, " "),$1,$3); }
	;

constant: INTEGER	{$$ = $1;}
	| CHARCONST	{$$ = $1;}
	| STRINGCONST	{$$ = $1;}
	| FALSE		{$$ = $1;}
	| TRUE		{$$ = $1;}
	| NUL		{$$ = $1;}
	;

%%

const char* get_yytname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

bool is_defined_token (int symbol) {
   return YYTRANSLATE (symbol) > YYUNDEFTOK;
}

static void* yycalloc (size_t size) {
   void* result = calloc (1, size);
   assert (result != NULL);
   return result;
}
