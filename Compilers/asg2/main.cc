//Steven Pan	span3@ucsc.edu
//Assignment #2
//10/28/13
//Passes a file into cpp, tokenizes the input, stores the tokens in a stringset, then
//dumps the stringset into a .str file.
//Also creates a .tok file created through flex that lists the type and location
//of tokens.

#include <string>
using namespace std;
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

#include "auxlib.h"
#include "stringset.h"
#include "lyutils.h"
#include "astree.h"
const string CPP = "/usr/bin/cpp";
const size_t LINESIZE = 1024;
//Chomp the last character from a buffer if it is delim.
void chomp (char *string, char delim) {
   size_t len = strlen (string);
   if (len == 0) return;
   char *nlpos = string + len - 1;
   if (*nlpos == delim) *nlpos = '\0';
}
//Used to check if file is .oc
const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}
// Run cpp against the lines of the file.
void cpplines (FILE *pipe, char *filename) {
   int linenr = 1;
   char inputname[LINESIZE];
   strcpy (inputname, filename);
   for (;;) {
      char buffer[LINESIZE];
      char *fgets_rc = fgets (buffer, LINESIZE, pipe);
      if (fgets_rc == NULL) break;
      chomp (buffer, '\n');
      // http://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html
      int sscanf_rc = sscanf (buffer, "# %d \"%[^\"]\"",
                              &linenr, filename);
      if (sscanf_rc == 2) {
         continue;
      }
      char *savepos = NULL;
      char *bufptr = buffer;
      for (int tokenct = 1;; ++tokenct) {
         char *token = strtok_r (bufptr, " \t\n", &savepos);
         bufptr = NULL;
         if (token == NULL) break;
         intern_stringset(token);
      }
      ++linenr;
   }
}
void scan_opts (int argc, char** argv) {
   int option;
   opterr = 0;
   yy_flex_debug = 0;
   yydebug = 0;
   string optstring = "";
   for (;;) {
      option = getopt (argc, argv, "ly:@:D");
      if (option == EOF) break;
      switch (option) {
         case '@': set_debugflags(optarg);   break;
         case 'l': yy_flex_debug = 1;        break;
         case 'y': yydebug = 1;              break;
         case 'D': optstring = atoi(optarg); break;
      }
   }
   if (optind > argc) {
      errprintf ("Usage: %s [-ly] [-@ flags] [-D string] [filename]\n", get_execname());
      exit (get_exitstatus());
   }   
}
void lexprint(char* filename) {
   string strname = filename;
   strname.erase(strname.end()-3,strname.end());
   strname = strname + ".tok";
   FILE* stroutput = fopen(strname.c_str(), "w");
   for (;;) {
      if (yylex() == 0) break;
      else dump_astree(stroutput,yylval);
   }
   
}
int main (int argc, char **argv) {
   
   string debugflag;
   string optstring = "";
   set_execname (argv[0]);
   for (int argi = 1; argi < argc; ++argi) {
      //Checks for options entered using -.
      scan_opts (argc, argv);
      //Only pass the file into CPP if it ends in .oc
      if (strcmp(get_filename_ext(argv[argi]),"oc") == 0) {
         char *filename = argv[argi];
         string command = CPP + " " + optstring.c_str() + filename;
         FILE *pipe = popen (command.c_str(), "r");
         yyin = popen (command.c_str(), "r");
         DEBUGF ('m', "filename = %s, yyin = %p, fileno (yyin) = %d\n",
           filename, yyin, fileno (yyin));
         cpplines(pipe,filename);
         int fclose_rc = fclose(pipe);
         eprint_status (command.c_str(), fclose_rc);
         if (yyin == NULL) {
            syserrprintf(command.c_str());
         }else {
            lexprint(filename);
         }
         //Opens up a .str version of the program and dumps stringset into it.
         string strname = argv[argi];
         strname.erase(strname.end()-3,strname.end());
         strname = strname + ".str";
         FILE *stroutput = fopen(strname.c_str() , "w");
         dump_stringset(stroutput);
         fclose_rc = fclose(stroutput);
         yylex_destroy();
         eprint_status (strname.c_str(), fclose_rc);
      }
   }
   return get_exitstatus();
}
