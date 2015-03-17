/* $Id: queue.c,v 1.15 2011-05-19 22:32:16-07 - - $ */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

static char *queue_tag = "struct queue";
static char *queuenode_tag = "struct queuenode";

typedef struct queuenode *queuenode_ref;

struct queuenode {
   char *tag;
   queue_item_t item;
   queuenode_ref link;
};

struct queue {
   char *tag;
   queuenode_ref front;
   queuenode_ref rear;
};

queue_ref new_queue (void) {
   queue_ref new = malloc(sizeof(struct queue));
   new->tag = queue_tag;
   new->front = NULL;
   new->rear = NULL;
   assert (new != NULL);
   return new;
}

void free_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (isempty_queue (queue));
   memset (queue, 0, sizeof (struct queue));
   free (queue);
}

void insert_queue (queue_ref queue, queue_item_t item) {
   assert (is_queue (queue));
   queuenode_ref tmp = malloc(sizeof(struct queuenode));
   assert (tmp != NULL);
   tmp->item = item;
   tmp->tag = queuenode_tag;
   tmp->link = NULL;
   if (queue->front == NULL) queue->front = tmp;
   else queue->rear = tmp;
}

queue_item_t remove_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (! isempty_queue (queue));
   queue_item_t val = queue->front->item;
   queue->front = queue->front->link;
   return val;
}

bool isempty_queue (queue_ref queue) {
   assert (is_queue (queue));
   return queue->front == NULL;
}

bool is_queue (queue_ref queue) {
   return queue != NULL && queue->tag == queue_tag;
}


