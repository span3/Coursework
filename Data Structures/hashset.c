// $Id: hashset.c,v 1.1 2011-05-24 00:57:56-07 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

struct hashset {
   size_t length;
   int load;
   char **array;
};

hashset_ref new_hashset (void) {
   hashset_ref new = malloc (sizeof (struct hashset));
   assert (new != NULL);
   new->length = HASH_NEW_SIZE;
   new->load = 0;
   new->array = malloc (new->length * sizeof (char*));
   size_t index = 0;
   for (index = 0; index < new->length; ++index) {
      new->array[index] = NULL;
   }
   assert (new->array != NULL);
   DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
                new, new->length, new->array);
   return new;
}

void free_hashset (hashset_ref hashset) {
   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void put_hashset (hashset_ref hashset, char *item) {
   hashcode_t starting_index = strhash(item) % hashset->length;
   int done = 0;
   hashcode_t itor = 0;
   for (itor = starting_index; itor < hashset->length; itor++) {
      if (hashset->array[itor] != NULL) {
         int comp = strcmp(item,hashset->array[itor]);
         if (comp == 0) {
            done = 1;
            break;
         }
      }
      else {
         hashset->array[itor] = item;
         hashset->load = hashset->load+1;
         done = 1;
         break;
      }
   }
   if (done == 0) {
      for (itor = 0; itor < starting_index; itor++) {
         if (hashset->array[itor] != NULL) {
            int comp = strcmp(item,hashset->array[itor]);
            if (comp == 0) {
               break;
            }
         }
         else {
            hashset->array[itor] = item;
            hashset->load = hashset->load+1;
            break;
         }
      }
   }
   if (hashset->load * 2  > hashset->length) {
      int load = hashset->load;
      int newsize = (hashset->load * 2) + 1;
      char** newarray = malloc(newsize * sizeof(char*));
      for (itor = 0; itor < hashset->length;itor++) {
         if (hashset->array[itor] != NULL) {
            int start = strhash(hashset->array[itor]) % newsize;
            newarray[start] = hashset->array[itor];
         }
      }
      hashset->array = newarray;
      hashset->length = newsize;
      hashset->load = load;
   }
}

bool has_hashset (hashset_ref hashset, char *item) {
   int starting_index = strhash(item) % hashset->length;
   int itor = 0;
   for (itor = starting_index; itor < hashset->length; itor++) {
      int comp = strcmp(item,hashset->array[itor]);
      if (comp == 0) return TRUE;
      else if (hashset->array[itor] == NULL) return FALSE;
   }
   for (itor = 0; itor < starting_index; itor++) {
      int comp = strcmp(item,hashset->array[itor]);
      if (comp == 0) return TRUE;
      else if (hashset->array[itor] == NULL) return FALSE;
   }
   return FALSE;
}
