// $Id: huffman.c,v 1.1 2011-06-03 16:45:21-07 - - $

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "auxlib.h"
#include "tree.h"
#include "prioque.h"

#define FREQUENCIES_DIM (UCHAR_MAX + 1)
#define STDIN_NAME "-"

void load_file (FILE *input_file, int *frequencies) {
   for (;;) {
      int byte = getc (input_file);
      if (byte == EOF) break;
      ++frequencies[byte];
   }
}

void load_files (int argc, char **argv, int *frequencies) {
   if (argc <= optind) {
      DEBUGF ('f', "Loading file \"%s\"\n", "-");
      load_file (stdin, frequencies);
   }else {
      int argi;
      for (argi = optind; argi < argc; ++argi) {
         char *filename = argv[argi];
         DEBUGF ('f', "Loading file \"%s\"\n", filename);
         if (strcmp (filename, STDIN_NAME) == 0) {
            load_file (stdin, frequencies);
         }else {
            FILE *input_file = fopen (filename, "r");
            if (input_file == NULL) {
               syseprintf (filename);
               set_exitstatus (EXIT_FAILURE);
            }else {
               load_file (input_file, frequencies);
            }
         }
      }
   }
}

void print_encoding_table (int *frequencies) {
   int charval;
   for (charval = 0; charval < FREQUENCIES_DIM; ++charval) {
      if (frequencies[charval] == 0) continue;
      printf (isgraph (charval) ? " %c " : "x%02X", charval);
      printf ("%8d %s\n", frequencies[charval], "????");
   }
}

void make_trees(int* frequencies,prioque_ref pqueue) {
   int charval;
   for (charval = 0; charval < FREQUENCIES_DIM -1; ++charval) {
      if (frequencies[charval] != 0) {
         tree_ref new = new_tree(charval,frequencies[charval],
            NULL,NULL);
         insert_prioque(pqueue,new);
      }
   }
}

tree_ref make_decoding_tree (prioque_ref pqueue) {
   tree_ref new = NULL;
   for (;;) {
      if (pqueue == NULL) break;
      tree_ref lchild = deletemin_prioque(pqueue);
      if (pqueue == NULL) break;
      tree_ref rchild = deletemin_prioque(pqueue);
      int newcharval = tree_charval(lchild);
      int newfreq = tree_freq(rchild) + tree_freq(lchild);
      new = new_tree(newcharval,newfreq,
         lchild,rchild);
      insert_prioque(pqueue,new);
   }
   return new;
}

void recurse_array(char** array,char* buffer, tree_ref currtree) {
   if (child(0,currtree) == 0 && child(1,currtree) == 0) {
      char* insert = strdup(buffer);
      array[tree_charval(currtree)] = insert;
   }
   else {
      int itor = 0;
      for (itor = 0; itor < 2; itor++) {
         if (itor == 0) strcat(buffer,"0");
         else strcat(buffer,"1");
         strcat(buffer,"\0");
         int newchild = child(itor,currtree);
//         recurse_array(array,buffer,newchild);
      }
      strcat(buffer,"\0");
   }
   return;
}

void make_encoding_array(tree_ref tree) {
   char** array = malloc(sizeof(UCHAR_MAX+1));
   char* buffer = malloc(sizeof(UCHAR_MAX+1));
   recurse_array(array,buffer,tree);
}

int main (int argc, char **argv) {
   prioque_ref pqueue = new_prioque(FREQUENCIES_DIM,cmp_tree);
   int frequencies[FREQUENCIES_DIM];
   set_execname (argv[0]);
   for (;;) {
      int opt = getopt (argc, argv, "@:");
      if (opt == EOF) break;
      if (opt == '@') set_debugflags (optarg);
   }
   bzero (frequencies, sizeof frequencies);

   load_files (argc, argv, frequencies);
   make_trees(frequencies,pqueue);
   tree_ref decodetree = make_decoding_tree(pqueue);
   make_encoding_array(decodetree);
   print_encoding_table (frequencies);

   return get_exitstatus ();
}
