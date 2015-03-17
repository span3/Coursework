//Steven Pan span3@ucsc.edu
//Fernando Carrillo fcarril1@ucsc.edu
// $Id: spellchk.c,v 1.1 2011-05-24 00:57:56-07 - - $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "auxlib.h"
#include "hashset.h"
#include "yyextern.h"

#define STDIN_NAME       "-"
#define DEFAULT_DICTNAME "/usr/share/dict/words"
#define DEFAULT_DICT_POS 0
#define EXTRA_DICT_POS   1
#define NUMBER_DICTS     2

FILE *open_infile (char *filename) {
   FILE *file = fopen (filename, "r");
   if (file == NULL) {
      syseprintf (filename);
      set_exitstatus (EXIT_FAILURE);
   };
   DEBUGF ('m', "filename = \"%s\", file = 0x%p\n", filename, file);
   return file;
}

void spellcheck (char *filename, hashset_ref hashset) {
   yylineno = 1;
   DEBUGF ('m', "filename = \"%s\", hashset = 0x%p\n",
                filename, hashset);
   //Goes through and checks each word against the hashset.
   for (;;) {
      int token = yylex();
      if (token == 0) break;
      DEBUGF ('m', "line %d, yytext = \"%s\"\n", yylineno, yytext);
      int check = has_hashset(hashset,yytext);
      if (check == 0) {
         char* newtext = strdup(yytext);
         int itor = 0;
         for (itor = 0; itor < strlen(yytext); itor++) {
            newtext[itor] = tolower(yytext[itor]);
         }
         check = has_hashset(hashset,yytext);
         if (check == 0) printf("%s ",yytext);
      }
   }
}

void load_dictionary (char *dictionary_name, hashset_ref hashset) {
   char* insert = malloc(sizeof(char*));
   FILE *ofile = open_infile(dictionary_name);
   if (dictionary_name == NULL) return;
   DEBUGF('m', "dictionary_name = \"%s\", hashset = %p\n",
           dictionary_name, hashset);
   for (;;) {
      fgets(insert,1000,ofile);
      if (insert == NULL) break;
      char* newinsert = malloc(sizeof(insert)-1);
      newinsert = strdup(insert);
      put_hashset(hashset,newinsert);
   }
   fclose(ofile);
}

int main (int argc, char **argv) {
   char *default_dictionary = DEFAULT_DICTNAME;
   char *user_dictionary = NULL;
   hashset_ref hashset = new_hashset ();
   yy_flex_debug = FALSE;
   set_execname (argv[0]);

   // Scan the arguments and set flags.
   opterr = FALSE;
   for (;;) {
      int option = getopt (argc, argv, "nxyd:@:");
      if (option == EOF) break;
      switch (option) {
         case 'd': user_dictionary = optarg;
                   break;
         case 'n': default_dictionary = NULL;
                   break;
         case 'x': STUBPRINTF ("-x\n");
                   break;
         case 'y': yy_flex_debug = TRUE;
                   break;
         case '@': set_debugflags (optarg);
                   if (strpbrk (optarg, "@y")) yy_flex_debug = TRUE;
                   break;
         default : eprintf ("%: -%c: invalid option\n", optopt);
                   set_exitstatus (EXIT_FAILURE);
      };
   };

   // Load the dictionaries into the hash table.
   load_dictionary (default_dictionary, hashset);
   load_dictionary (user_dictionary, hashset);

   // Read and do spell checking on each of the files.
   if (optind >= argc) {
      yyin = stdin;
      spellcheck (STDIN_NAME, hashset);
   }else {
      int fileix = optind;
      for (; fileix < argc; ++fileix) {
         DEBUGF ('m', "argv[%d] = \"%s\"\n", fileix, argv[fileix]);
         char *filename = argv[fileix];
         if (strcmp (filename, STDIN_NAME) == 0) {
            yyin = stdin;
            spellcheck (STDIN_NAME, hashset);
         }else {
            yyin = open_infile (filename);
            if (yyin == NULL) continue;
            spellcheck (filename, hashset);
            fclose (yyin);
         }
      };
   }
   
   yycleanup ();
   return get_exitstatus ();
}
