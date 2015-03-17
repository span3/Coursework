// Steven Pan span3@ucsc.edu
// $Id: lsort.c,v 1.1 2011-05-12 04:01:34-07 - - $
// This program reads in Strings from stdin, and
// then sorts them in ascending order before printing
// them out.

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *node_ref;
typedef char *cstring;
struct node {
   cstring item;
   node_ref link;
};

int main () {
   char* currnum = NULL;
   char buffer[72];
   node_ref head = NULL;
   node_ref curr = NULL;
   node_ref prev = NULL;
   curr = head;
   currnum = fgets(buffer,sizeof buffer,stdin);
   if (head == NULL) {
      node_ref new = malloc(sizeof(struct node));
      assert (new != NULL);
      new->item = currnum;
      new->link = head;
      head = new;
   }else {
      for (curr = head; curr != NULL; curr = curr->link) {
         while (curr != NULL) {
            if (strcmp(currnum,curr->item) > 0) break;
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
