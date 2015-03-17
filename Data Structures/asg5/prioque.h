// $Id: prioque.h,v 1.1 2011-06-03 16:45:21-07 - - $

#ifndef __PRIOQUEUE_H__
#define __PRIOQUEUE_H__

#include "tree.h"

typedef tree_ref prioque_item;
typedef struct prioque *prioque_ref;
typedef int (*cmpfn_prioque) (prioque_item, prioque_item);

prioque_ref new_prioque (int initdim,cmpfn_prioque);

void free_prioque (prioque_ref);

void insert_prioque (prioque_ref, prioque_item);

prioque_item deletemin_prioque (prioque_ref);

#endif


