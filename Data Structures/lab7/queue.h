/* $Id: queue.h,v 1.1 2011-05-19 22:03:43-07 - - $ */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "auxlib.h"

typedef struct queue *queue_ref;
typedef char *queue_item_t;

queue_ref new_queue (void);

void free_queue (queue_ref);

void insert_queue (queue_ref, queue_item_t);

queue_item_t remove_queue (queue_ref);

bool isempty_queue (queue_ref);

bool is_queue (queue_ref);

#endif


