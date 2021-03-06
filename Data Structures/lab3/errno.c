// $Id: errno.c,v 1.1 2011-04-21 01:48:28-07 - - $
// Fernando Carrillo fcarril1@ucsc.edu
// Steven Pan span3@ucsc.edu

/*
NAME
     errno -- translate system error numbers into text messages

SYNOPSIS
     errno [-a] [-e status] [errno...]

DESCRIPTION
     The errno utility prints out some the system call error code
     numbers and their text equivalents.

OPTIONS
     All options must precede all operands and are scanned with the
     function getopt(3c).

     -a   All of the system error codes are printed.

     -e status
          The program returns a status code given by status.

OPERANDS
     Each operand is a numeric system error code which is printed
     along with its text equivalent.  Operands are ignored if the -a
     option is given.

EXIT STATUS

     0    If no -e option is given and no errors are detected.

     1    If no -e option is given but errors are detected.

     n    The -e options specifies the exit status.

SEE ALSO
     errno(3c), getopt(3c), printf(3c), strerror(3c), strtol(3c).
*/

#include <libgen.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum {FALSE=0, TRUE=1} bool;

void eprintf (const char *format, ...) {
   va_list args;
   va_start (args, format);
   fflush (NULL);
   vfprintf (stderr, format, args);
   va_end (args);
   fflush (NULL);
}


//
// main - as described in the man-page above.
//

char *progname = NULL;
int arga = 0;
int arge = 0;
int option = 0;
int wantusageexit = 0;
char * earg = 0;

int main (int argc, char **argv) {
   for (;;) {
      progname = basename (argv[0]);
      option = getopt(argc, argv, "ae:");
      if (option == EOF) break;
      switch (option) {
         case 'a': arga = 1;
                   break;
         case 'e': arge = 1;
                   earg = optarg;
                   break;
         default : wantusageexit = 1;
      }
   }
   if (wantusageexit == 1) {
      eprintf ("Usage: %s", progname);
      exit (EXIT_FAILURE);
   }
   if (arga == 1) {
      for (int start = 0; start < 132; start++) {
         eprintf("strerror(%d)= \"%s\"\n", start, strerror (start));
      }
   }
   if (arga == 0 && arge == 0)  {
      for (int start = 1; start < argc; start++) {
         char *endptr = NULL;
         int errno = strtol (argv[start], &endptr, 10);
         eprintf("strerror(%d)= \"%s\"\n", errno, strerror (errno));
      }
   }
   if (arge == 1) {
      char *endptr = NULL;
      int errno = strtol (earg, &endptr, 10);
      eprintf("strerror(%d)= \"%s\"\n", errno, strerror (errno));
      return EXIT_SUCCESS;  
   }
   return EXIT_SUCCESS;
}
