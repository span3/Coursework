// $Id: strhash.c,v 1.1 2011-05-24 00:57:56-07 - - $

#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

#include "strhash.h"

hashcode_t strhash (char *string) {
   assert (string != NULL);
   hashcode_t hashcode = 0;
   while (*string) hashcode = hashcode * 31 + (unsigned char) *string++;
   return hashcode;
}
