/* intList.h (what is the purpose of this file?)
*/

#ifndef C101IntList
#define C101IntList

typedef struct IntListNode * IntList;

extern const IntList intNil;

int intFirst(IntList oldL);
	
IntList intRest(IntList oldL);

/* Constructors (what are the preconditions and postconditions?)
*/

/** cons
*/
IntList intCons(int newE, IntList oldL);

#endif

