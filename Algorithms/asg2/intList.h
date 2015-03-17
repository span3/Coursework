// File: intList.h
// Author: Steven Pan (span3@ucsc.edu)
// Date: 5/13/12
// Class: CMPS 101
// Assignment: 2

#ifndef C101IntList
#define C101IntList

typedef struct IntListNode * IntList;

/* intNil denotes the empty IntList */
extern const IntList IntNil;

/* Access functions */

/* first()
 * precondition: oldL !=nil;
 * postcondition: oldL.element is returned
*/
int intFirst(IntList oldL);

/* rest()
 * precondition: oldL != nil
 * postcondition: oldL.next is returned
*/
IntList intRest(IntList oldL);

/* Constructors */

/* cons()
 * precondition: no precondition
 * postcondition: IntList != nil
*/
IntList intCons(int newE, IntList oldL);

#endif

