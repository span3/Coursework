// Steven Pan span3@ucsc.edu
// $Id: nsort.c,v 1.1 2011-05-12 04:01:34-07 - - $
// This program reads in ints from stdin, and then
// sorts them in a queue in ascending order before
// printing them out.

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_ref;
struct node {
   double item;
   node_ref link;
};

int main () {
   float currnum = 0;
   node_ref head = NULL;
   node_ref curr = NULL;
   node_ref prev = NULL;
   curr = head;
   scanf ("%e", &currnum);
   if (head == NULL) {
      node_ref new = malloc(sizeof(struct node));
      assert (new != NULL);
      new->item = currnum;
      new->link = head;
      head = new;
   }else {
      for (curr = head; curr != NULL; curr = curr->link) {
         while (curr != NULL) {
            if (curr->item < currnum) break;
            prev = curr;
            curr = curr->link;
         }
         node_ref temp = malloc(sizeof(struct node));
         assert (temp != NULL);
         temp->item = currnum;
         temp->link = curr;
         if (prev == NULL) head = temp;
         else prev->link = temp;
      }
   }
   for (curr = head; curr != NULL; curr = curr->link) {
      printf("%d\n", curr->item);
   }
   while (head != NULL) {
      node_ref old = head;
      head = head->link;
      free (old);
   }
}
