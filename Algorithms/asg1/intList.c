#include <stdlib.h>
#include "intList.h"


struct IntListNode
{
    int element;
    IntList next;
};

const IntList IntNil = NULL;

typedef struct IntListNode IntListNode;

int intFirst(IntList oldL)
{
    return oldL->element;
}

IntList	intRest(IntList oldL)
{
    return oldL->next;
}

IntList intCons(int newE, IntList oldL)
{
    IntList newList = calloc(1, sizeof(struct IntListNode));
    newList->element = newE;
    newList->next = oldL;
    return newList;
}

