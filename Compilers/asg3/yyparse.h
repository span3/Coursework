
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ROOT = 258,
     IDENT = 259,
     INTEGER = 260,
     STRINGCONST = 261,
     CHARCONST = 262,
     NUMBER = 263,
     CHAR = 264,
     STR = 265,
     VOID = 266,
     BOOL = 267,
     INT = 268,
     STRING = 269,
     STRUCT = 270,
     IF = 271,
     ELSE = 272,
     WHILE = 273,
     RETURN = 274,
     NEW = 275,
     FALSE = 276,
     TRUE = 277,
     NUL = 278,
     ORD = 279,
     CHR = 280,
     EQEQ = 281,
     ARRAY = 282,
     NOTEQ = 283,
     LESSEQ = 284,
     GREATEQ = 285,
     TYPEID = 286,
     TYPE = 287,
     FIELD = 288,
     INDEX = 289,
     BINOP = 290,
     BASETYPE = 291,
     BLOCK = 292,
     IFELSE = 293,
     VARDECL = 294,
     POS = 295,
     NEG = 296,
     FUNCTION = 297,
     VARIABLE = 298,
     CONSTANT = 299,
     CALL = 300,
     t = 301,
     e = 302
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


