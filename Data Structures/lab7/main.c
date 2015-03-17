//Steven Pan span3@ucsc.edu
//$Id: main.c,v 1.2 2011-05-19 22:14:30-07 - - $
//This program reads in lines into queue, then prints out the queue.
//It incorporates headers files to do so.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxlib.h"
#include "queue.h"

void putinqueue (queue_ref queue, FILE *input, char *filename) {
   char buffer[1024];
   int linenr;
   for (linenr = 1; ; ++linenr) {
      char *linepos = fgets (buffer, sizeof buffer, input);
      if (linepos == NULL) break;
      linepos = strchr (buffer, '\n');
      if (linepos == NULL) {
         printf ("%: %s[%d]: unterminated line\n", filename, linenr);
      }else {
         *linepos = '\0';
      };
      linepos = strdup (buffer);
      assert (linepos != NULL);
      insert_queue (queue, linepos);
   };
}

void putfileinqueue (queue_ref queue, char *filename) {
   FILE *input = fopen (filename, "r");
   if (input == NULL) {
      printf (filename);
   }else {
      putinqueue (queue, input, filename);
      if (fclose (input)) printf (filename);
   };
}

int main (int argc, char **argv) {
   queue_ref queue = NULL;
   set_execname (argv[0]);
   queue = new_queue();

   if (argc < 2) {
      putinqueue (queue, stdin, "-");
   }else {
      int argi;
      for (argi = 1; argi < argc; ++argi) {
         if (strcmp (argv[argi], "-") == 0) {
            putinqueue (queue, stdin, "-");
         }else {
            putfileinqueue (queue, argv[argi]);
         };
      };
   };

   while (! isempty_queue (queue)) {
      printf ("%s\n", remove_queue (queue));
   };
   free_queue(queue);
   return get_exitstatus();
}
