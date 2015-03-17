#include <assert.h>   
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include "inssort.h"

static int intcmp (const void *this, const void *that) {
   int *thisint = (int*) this;
   int *thatint = (int*) that;
   return *thisint < *thatint ? -1 : *thisint > *thatint ? +1 : 0;
}

int main () { 
   int load = 0;
   double array[1000];
   double input;
   for (;;) {
      scanf("%lg",&input);
      if (input == EOF) break;
      array[load] = input;
      load++;
   }
   insertion_sort(array,load,sizeof(int),intcmp);
   int itor = 0;
   for (itor = 0; itor < load; itor++) {
      printf("%lg\n",array[itor]);
   }
}
