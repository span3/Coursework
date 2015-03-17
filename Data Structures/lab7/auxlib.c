// $Id: auxlib.c,v 1.1 2011-05-19 22:03:43-07 - - $

#include <assert.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxlib.h"

static int exitstatus = EXIT_SUCCESS;
static char *execname = NULL;
static char *debugflags = "";
static bool alldebugflags = FALSE;

void set_execname (char *argv0) {
   execname = basename (argv0);
}

char *get_execname (void) {
   assert (execname != NULL);
   return execname;
}

static char *init_dprintf (char *format) {
   assert (format != NULL);
   fflush (NULL);
   if (strstr (format, "%:") == format) {
      fprintf (stderr, "%s: ", get_execname ());
      format += 2;
   };
   return format;
}

void dprintf (char *format, ...) {
   va_list args;
   format = init_dprintf (format);
   va_start (args, format);
   vfprintf (stderr, format, args);
   va_end (args);
   fflush (NULL);
}

void eprintf (char *format, ...) {
   va_list args;
   assert (execname != NULL);
   assert (format != NULL);
   format = init_dprintf (format);
   va_start (args, format);
   vfprintf (stderr, format, args);
   va_end (args);
   fflush (NULL);
   exitstatus = EXIT_FAILURE;
}

void syseprintf (char *object) {
   eprintf ("%:%s: %s\n", object, strerror (errno));
}

int get_exitstatus (void) {
   return exitstatus;
}

void set_exitstatus (int newexitstatus) {
   newexitstatus &= 0xFF;
   if (exitstatus < newexitstatus) exitstatus = newexitstatus;
   DEBUGF ('a', "exitstatus = %d\n", exitstatus);
}

void __stubprintf (char *file, int line, const char *func,
                   char *format, ...) {
   va_list args;
   fflush (NULL);
   printf ("%s: %s[%d] %s: ", execname, file, line, func);
   va_start (args, format);
   vprintf (format, args);
   va_end (args);
   fflush (NULL);
}

void set_debugflags (char *flags) {
   debugflags = flags;
   if (strchr (debugflags, '@') != NULL) alldebugflags = TRUE;
   DEBUGF ('a', "Debugflags = \"%s\"\n", debugflags);
}

void __debugprintf (char flag, char *file, int line,
                    char *format, ...) {
   va_list args;
   if (alldebugflags || strchr (debugflags, flag) != NULL) {
      fflush (NULL);
      va_start (args, format);
      fprintf (stderr, "DEBUGF(%c): %s[%d]:\n",
                flag, file, line);
      vfprintf (stderr, format, args);
      va_end (args);
      fflush (NULL);
   }
}


