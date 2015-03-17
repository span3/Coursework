// $Id: tree.c,v 1.1 2011-06-03 16:45:21-07 - - $

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#include "auxlib.h"

struct tree {
   int charval;
   int freq;
   tree_ref children[2];
};

struct encoding {
   int length;
   char string [UCHAR_MAX + 2];
};

int tree_charval(tree_ref tree) {
   return tree->charval;
};

int tree_freq(tree_ref tree) {
   return tree->freq;
};

tree_ref child(int index, tree_ref tree) {
   if (index == 0) {
      tree_ref result = (tree_ref)tree->children[0];
      return result;
   }
   else {
      tree_ref result = (tree_ref)tree->children[1];
      return result;
   }
};

tree_ref new_tree (int charval, int frequency,
                   tree_ref child0, tree_ref child1) {
   tree_ref new = malloc(sizeof(struct tree));
   new->charval = charval;
   new->freq = frequency;
   new->children[0] = child0;
   new->children[1] = child1;
   return new;
}

void free_tree (tree_ref tree) {
   DEBUGF ('t', "tree=%p\n", tree);
   if (tree == NULL) return;
   free_tree (tree->children[0]);
   free_tree (tree->children[1]);
   free (tree);
}

int intcmp (int this, int that) {
   if (this < that) return -1;
   if (this > that) return +1;
   return 0;
}

int cmp_tree (tree_ref this, tree_ref that) {
   int freqdiff = intcmp (this->freq, that->freq);
   if (freqdiff != 0) return freqdiff;
   return intcmp (this->charval, that->charval);
}

void encode_tree_rec (char **encodings, struct encoding *encoding,
                      tree_ref tree) {
   DEBUGF ('t', "encodings=%p, encoding=%p, tree=%p\n",
           encodings, encoding, tree);
}

char **encode_tree (tree_ref tree) {
   struct encoding encoding;
   char **encodings = calloc (UCHAR_MAX + 1, sizeof (char*));
   encoding.length = 0;
   encoding.string[0] = '\0';
   encode_tree_rec (encodings, &encoding, tree);
   return encodings;
}


