// $Id: tree.h,v 1.1 2011-06-03 16:45:21-07 - - $

#ifndef __FREQTREE_H__
#define __FREQTREE_H__

typedef struct tree *tree_ref;

tree_ref new_tree (int charval, int frequency,
             tree_ref left, tree_ref right);

void free_tree (tree_ref);

int cmp_tree (tree_ref, tree_ref);

char **encode_tree (tree_ref);

#endif


