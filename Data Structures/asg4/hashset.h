// $Id: hashset.h,v 1.1 2011-05-24 00:57:56-07 - - $

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include "auxlib.h"

typedef struct hashset *hashset_ref;

//
// Create a new hashset with a default number of elements.
//
hashset_ref new_hashset (void);

//
// Frees the hashset, and the words it points at.
//
void free_hashset (hashset_ref);

//
// Inserts a new string into the hashset.
//
void put_hashset (hashset_ref, char*);

//
// Looks up the string in the hashset and returns TRUE if found,
// FALSE if not found.
//
bool has_hashset (hashset_ref, char*);

#endif


