#include <assert.h>   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inssort.h"

void insertion_sort (void *base, size_t nelem, size_t size,
              int (*compar) (const void *, const void *)) {
   int sorted = 1;
   for (sorted = 1; sorted < nelem; sorted++) {
      int slot = sorted;
      char* address = base + size*(slot);
      void* element = alloca(sizeof(size));
      memcpy(element,address,size);
      for (; slot > 0; slot--) {
         char* address1 = base + size * (slot-1);
         char* address2 = base + size * (sorted);
         if (compar (address1,address2) <= 0) {
            memcpy(address2,address1,size);
         }
      }
      memcpy(base + size*(slot),element,size);
      free(element);
   }
}
