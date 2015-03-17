// $Id: prioque.c,v 1.1 2011-06-03 16:45:21-07 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "prioque.h"

#include "auxlib.h"

#define ROOT 0
#define PARENT(INDEX) (((INDEX) - 1) / 2)
#define LCHILD(INDEX) ((INDEX) * 2 + 1)
#define RCHILD(INDEX) ((INDEX) * 2 + 2)

struct prioque {
   int dim;
   int last;
   prioque_item *array;
   cmpfn_prioque cmpfn;
} ;

bool rootward (prioque_ref queue, int index1, int index2) {
   return queue->cmpfn (queue->array[index1], queue->array[index2]) < 0;
}

prioque_ref new_prioque (int initdim,cmpfn_prioque cmpfn) {
   prioque_ref queue = malloc (sizeof (struct prioque));
   assert (queue != NULL);
   queue->dim = initdim + 1;
   queue->last = ROOT - 1;
   queue->cmpfn = cmpfn;
   queue->array = calloc (queue->dim, sizeof (prioque_item));
   assert (queue->array != NULL);
   DEBUGF ('p', "queue=%p\n", queue);
   return queue;
}

void free_prioque (prioque_ref queue) {
   DEBUGF ('p', "queue=%p\n", queue);
   free (queue->array);
   free (queue);
}

void insert_prioque (prioque_ref queue, prioque_item item) {
   DEBUGF ('p', "queue=%p, item=%p\n", queue, item);
   assert(queue->last < queue->dim -1);
   ++queue->last;
   queue->array[queue->last] = item;
   int child = queue->last;
   while (child > ROOT) {
      int parent = PARENT(child);
      if (rootward(queue,parent,child) == 1) break;
      prioque_item tmp = queue->array[parent];
      queue->array[parent] = queue->array[child];
      queue->array[child] = tmp;
      child = parent;
   }
}

prioque_item deletemin_prioque (prioque_ref queue) {
   DEBUGF ('p', "queue=%p\n", queue);
   assert (queue != NULL);
   prioque_item tmp = queue->array[ROOT];
   queue->array[ROOT] = queue->array[queue->last];
   queue->array[queue->last] = tmp;
   prioque_item result = queue->array[queue->last];
   queue->last = queue->last --;
   int parent = ROOT;
   for (;;) {
      int child = LCHILD(parent);
      if (queue->array[child] == NULL) break;
      int smallchild = child;
      int rchild = RCHILD(parent);
      if (intcmp(rchild,child) != 0) {
         if (rootward(queue,rchild,child) == 1) {
            smallchild = rchild;
         }
      }
      if (rootward(queue,parent,smallchild) == 1) break;
      prioque_item temp = queue->array[parent];
      queue->array[parent] = queue->array[smallchild];
      queue->array[smallchild] = temp;
      parent = smallchild;
   }
   return result;
}
