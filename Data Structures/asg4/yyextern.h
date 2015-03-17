// $Id: yyextern.h,v 1.1 2011-05-24 00:57:56-07 - - $

#ifndef __YYEXTERN_H__
#define __YYEXTERN_H__

//
// DESCRIPTION
//    Definitions of external names used by flex-generated code.
//

#include <stdio.h>

extern FILE *yyin;            // File currently being read

extern char *yytext;          // Pointer to the string that was found

extern int yy_flex_debug;     // yylex's verbose tracing flag

extern int yylex (void);      // Read next word from opened file yyin

extern int yylineno;          // Line number within the current file

extern void yycleanup (void); // Cleans up flex's buffers when done

#endif


