#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define public
#define private static

#define PAGE_SIZE      4096
#define BUDDY_FLAG     0x01
#define FREELIST_FLAG  0x04
#define FIRSTFIT_FLAG  0x00
#define NEXTFIT_FLAG   0x08
#define BESTFIT_FLAG   0x10
#define WORSTFIT_FLAG  0x18
#define FIRSTFIT   1
#define NEXTFIT    2
#define BESTFIT    3
#define WORSTFIT   4

typedef struct allocator *allocator_ref;
struct allocator {
   int handle;           // handle of allocator
   long n_bytes;         // allocation space available
   unsigned int flags;   // flags for allocator type
   int parm1;            
   // for buddy allocator
   int totalBytesUsed;
   int buddyMaxLevel;
   unsigned int *buddyMap;

   // for list allocator
   void *memory;         // points to head of memory
};
allocator_ref allocators[512]; // array that holds multiple allocators
int allocSize = 0;
void *nextfit = NULL;

private int buddy_init (long n_bytes, unsigned int flags, int parm1) {
   int handle = allocSize;; // return possible error or handle
   if (n_bytes & (n_bytes-1) != 0) {
      printf ("Not a power of 2 \n");
      return -1;
   }
   int minPageLength = (int)pow(2, parm1);  // Number of byte in smallest page
   int smallestPageNumber = n_bytes/minPageLength; // Number of smallest pages
   int totalPositions = smallestPageNumber * 2; // Number of positions
   int buddyMapBytes = ceil((float)totalPositions / 32) * 4; // Total bytes must be multiple of 4, since using ints   
   allocator_ref newAlloc = malloc(sizeof(struct allocator) + buddyMapBytes + n_bytes);
   newAlloc->handle = handle;
   newAlloc->n_bytes = n_bytes;
   newAlloc->flags = flags;
   newAlloc->parm1 = parm1;
   newAlloc->totalBytesUsed = sizeof(struct allocator);
   newAlloc->buddyMaxLevel = log(smallestPageNumber)/log(2);
   newAlloc->buddyMap = (void*)((newAlloc) + sizeof(struct allocator));
   memset (newAlloc->buddyMap, 0, buddyMapBytes);
   newAlloc->memory = newAlloc + sizeof(struct allocator) + (buddyMapBytes/8);
   allocators[allocSize] = newAlloc;
   return handle;
}

private int freelist_init (long n_bytes, unsigned int flags, int parm1) {
   int handle = allocSize;     // Get current value of handle
   // initialize new allocator
   allocator_ref newAlloc = malloc(n_bytes);
   newAlloc->handle = handle;
   newAlloc->n_bytes = n_bytes;
   newAlloc->flags = flags;
   newAlloc->parm1 = parm1;
   newAlloc->memory = (void*)&(newAlloc->memory) + sizeof (void *);
   long initoverhead = newAlloc->memory - (void*)newAlloc;
   long space_left = n_bytes - initoverhead;  
   void *sizeptr;
   sizeptr = newAlloc->memory;
   *(long*)sizeptr = space_left-sizeof(long);
   newAlloc->memory = sizeptr+4;
   *(int *)newAlloc->memory = NULL;
   // put the allocator into the array
   allocators[handle] = newAlloc;
   return handle;
}

public int meminit(long n_bytes, unsigned int flags, int parm1 ) {
   int handle = -1; // return handle or error
   // initialize allocators on first run
   if (allocSize == 0) {
      int i;
      for (i = 0; i < MAX_ALLOCATORS; ++i) allocators[i] = NULL;
   }
   // check if there is allocation space
   if (allocSize >= MAX_ALLOCATORS) {
      // return error
      printf("No more allocation space \n");
      return -1; // Error, couldn't find handle
   }
   // Determine flag specifics and free
   // now allocate and initialize
   if (flags & BUDDY_FLAG) {
      handle = buddy_init (n_bytes, flags, parm1);
   } else if (flags & FREELIST_FLAG) {
      handle = freelist_init (n_bytes, flags, parm1);
   } else {
      printf ("Wrong flag entered \n");
      return handle;
   }
   if (handle < 0) {
      printf ("Could not initialize using given parameters \n");
      return handle;
   }
   allocSize++;
   return (allocSize - 1);
}

// Get bit value from specified position
private int getBMapBit(allocator_ref myAlloc, int level, int position) {
   assert (myAlloc != NULL);
   unsigned int *buddyMap = myAlloc->buddyMap;
   int offset = pow(2, level-1) + position;  // Which bit inside buddyMap
   int targetInt = floor(offset / 32);  // Point to int containing bit
   int targetOffset = offset - (targetInt * 32); // Point to position of bit inside int
   if (buddyMap[targetInt] & (1 << targetOffset))
      return 1;
   else
      return 0;
}

// Get bit value from buddy of specified position
private int getBMapBuddyBit(allocator_ref myAlloc, int level, int position) {
   int buddyPosition;
   if (level == 0) return 1;
   if (position % 2 == 0)
      buddyPosition = position + 1;
   else
      buddyPosition = position - 1;
   return getBMapBit(myAlloc, level, buddyPosition);
}

// Get bit value from buddy of specified position
private void setBMapBit(allocator_ref myAlloc, int level, int position, int value) {
   assert (myAlloc != NULL);
   if (value != 0 && value != 1) {
      fprintf(stderr, "Error: setBMapBit value must be 0 or 1.\n");
      return;
   }
   unsigned int *buddyMap = myAlloc->buddyMap;
   int offset = pow(2, level-1) + position;  // Which bit inside buddyMap
   int targetInt = floor(offset / 32);  // Point to int containing bit
   int targetOffset = offset - (targetInt * 32); // Point to position of bit inside int
   if (value == 0)
      buddyMap[targetInt] &= ~(1 << targetOffset);
   else
      buddyMap[targetInt] |= 1 << targetOffset;
}

// Get memory address of specified position
private void *getMemoryAddress (allocator_ref myAlloc, int level, int position) {
   assert (myAlloc != NULL);
   void *memory = myAlloc->memory;
   long n_bytes = myAlloc->n_bytes;
   long offset = ((float)n_bytes/pow(2, level)) * position;  // Which fraction inside buddyMap
   return memory+offset;
}

// Divide block into two
private void divide (allocator_ref myAlloc, int level, int position) {
   //printf("Divided: Level %d\n", level);
   setBMapBit(myAlloc, level, position, 1); // Mark as used
   setBMapBit(myAlloc, level+1, position*2, 0);   // Mark resulting buddies as unused
   setBMapBit(myAlloc, level+1, position*2+1, 0);
}

// Allocate a new memory block
private void *buddy_alloc (allocator_ref myAlloc, long n_bytes) {
   assert (myAlloc != NULL);
   if (n_bytes > myAlloc->n_bytes) {
      printf("Requested size is too large \n"); 
      return NULL;
   }
   void *memptr = NULL;
   double numFit = myAlloc->n_bytes / n_bytes;
   int targetLevel = floor(log(numFit)/log(2));
   int level = targetLevel;
   if (level > myAlloc->buddyMaxLevel) {
      level = myAlloc->buddyMaxLevel;
   }
   int piecePosition = -1;
   int levelFound = 0;
   while (levelFound == 0) {
      // Check each bit in index for open value
      int counter;
      for (counter = 0; counter < pow(2,level); counter++) {
         if (getBMapBit(myAlloc, level, counter) == 0
            && getBMapBuddyBit(myAlloc, level, counter) == 1) { // Check for free block with used buddy
            levelFound = 1;
            piecePosition = counter;
            break;
         }
      }
      if (levelFound == 0) {
         level--;
         if (level < 0) {
            printf("No free spots found \n");
            return NULL;
         }
      }
   }
   while (level != targetLevel) {
      if (level >= myAlloc->buddyMaxLevel) {
         break;
      }
      divide (myAlloc, level, piecePosition);
      level++;
      piecePosition *= 2;
   }
   // Mark piece we are returning as used
   setBMapBit(myAlloc, level, piecePosition, 1);
   double bytesUsed = myAlloc->n_bytes / pow(2,level);   
   myAlloc->totalBytesUsed += bytesUsed;
   memptr = getMemoryAddress (myAlloc, level, piecePosition);   
   return memptr;
}

private void *firstfit_alloc (allocator_ref myAlloc, long n_bytes) {
   assert (myAlloc != NULL);
   void *memptr = NULL;
   void *current;
   void *next = NULL;
   void *prev = NULL; 
   void *nextfree = NULL;
   int current_head = 0;
   current = myAlloc->memory;
   while(current != NULL){
      long curr_size = *(long*)(current-4);
      next = *(int*)current;
      
      // A segment large enough was found
      if (n_bytes < curr_size){
         if (current == myAlloc->memory)
            current_head = 1;
         nextfree = *(int*)current;
         *(long*)(current-4) = n_bytes;
         memptr = current;
         current = current + n_bytes;
         *(long*)(current) = curr_size - n_bytes - 4;
         current += 4;
         // check if current is the head of list
         if (current_head == 1){
            myAlloc->memory = current;
            *(int*)current = nextfree;
            current_head = 0;
         }
         else{
            *(int*)prev = current;  
            *(int*)current = nextfree;      
         }
      }
      prev = current;
      current = next;
   } // end while
   return memptr;
}

private void *nextfit_alloc (allocator_ref myAlloc, long n_bytes) {
   assert (myAlloc != NULL);
   void *memptr = NULL;
   void *current;
   void *next = NULL;
   void *prev = NULL; 
   void *nextfree = NULL;
   int current_head = 0;
   // If nextfit is NULL start at the beginning
   if (nextfit == NULL)
      nextfit = myAlloc->memory;
   // set the current as the nextfit (last time it worked)
   current = nextfit;
   while(current != NULL){
      long curr_size = *(long*)(current-4);
      next = *(int*)current;
      // A segment large enough was found
      if (n_bytes < curr_size){
         if (current == myAlloc->memory)
            current_head = 1;
         nextfree = *(int*)current;
         *(long*)(current-4) = n_bytes;
         memptr = current;
         current = current + n_bytes;
         *(long*)(current) = curr_size - n_bytes - 4;
         current += 4;
         // check if current is the head of list
         if (current_head == 1){
            myAlloc->memory = current;
            *(int*)current = nextfree;
            nextfit = current;
            current_head = 0;
         }
         else{
            *(int*)prev = current;  
            *(int*)current = nextfree;    
            nextfit = current;  
         }
      }
      prev = current;
      current = next;
   }
   if (current == NULL)
      nextfit = NULL;
   return memptr;
}

private void *bestfit_alloc (allocator_ref myAlloc, long n_bytes) {
   assert (myAlloc != NULL);
   void *memptr = NULL;
   void *current;
   void *next = NULL;
   void *prev = NULL;
   void *nextfree = NULL;
   int current_head = 0;
   void *bestfit = NULL;
   void *bestfitprev = NULL;
   long smallest_diff = 9999999999999999;
   long size_diff = 0;
   current = myAlloc->memory;
   // try to find the best fitting segment
   while(current != NULL){
      long curr_size = *(long*)(current-4);
      size_diff = curr_size - (n_bytes+4);
      next = *(int*)current;
      if (size_diff >= 0 && size_diff < smallest_diff){
         smallest_diff = size_diff;
         bestfit = current;
         bestfitprev = prev;
      }
      prev = current;
      current = next;
   }
   if (bestfit == NULL)
      return NULL;
   else{
      if (bestfit == myAlloc->memory)
            current_head = 1;
      nextfree = *(int*)bestfit;
      long best_size = *(long*)(bestfit-4);
      *(long*)(bestfit-4) = n_bytes;
      memptr = bestfit;
      bestfit += n_bytes;
      *(long*)(bestfit) = best_size - n_bytes - 4;
      bestfit += 4;
      // check if current is the head of list
      if (current_head == 1){
         myAlloc->memory = bestfit;
         *(int*)bestfit = nextfree;
         current_head = 0;
      }
      else{
         *(int*)bestfitprev = bestfit;  
         *(int*)bestfit = nextfree;      
      }

   }
   return memptr;
}

private void *worstfit_alloc (allocator_ref myAlloc, long n_bytes) {
   assert (myAlloc != NULL);
   void *memptr = NULL;
   void *current;
   void *next = NULL;
   void *prev = NULL;
   void *nextfree = NULL;
   int current_head = 0;
   long largest = 0;
   void *worstfit = NULL;
   void *worstfitprev = NULL;
   current = myAlloc->memory;
   while(current != NULL){
      long curr_size = *(long*)(current-4);
      next = *(int*)current;
      if (largest < curr_size){
         largest = curr_size;
         worstfit = current;
         worstfitprev = prev;
      }
      prev = current;
      current = next;
   }
   if (worstfit == NULL)
      return NULL;
   else{
      if (worstfit == myAlloc->memory)
            current_head = 1;
      nextfree = *(int*)worstfit;
      long largest_size = *(long*)(worstfit-4);
      *(long*)(worstfit-4) = n_bytes;
      memptr = worstfit;
      worstfit += n_bytes;
      *(long*)(worstfit) = largest_size - n_bytes - 4;
      worstfit += 4;
      // check if current is the head of list
      if (current_head == 1){
         myAlloc->memory = worstfit;
         *(int*)worstfit = nextfree;
         current_head = 0;
      }
      else{
         *(int*)worstfitprev = worstfit;  
         *(int*)worstfit = nextfree;      
      }
   }
   return memptr;
}

private void *freelist_alloc (allocator_ref myAlloc, long n_bytes, int fittype) {
   assert (myAlloc != NULL);
   void *memptr = NULL;
   switch (fittype) {
      case FIRSTFIT:
         memptr = firstfit_alloc (myAlloc, n_bytes);   break;
      case NEXTFIT:
         memptr = nextfit_alloc (myAlloc, n_bytes);    break;
      case BESTFIT:
         memptr = bestfit_alloc (myAlloc, n_bytes);    break;
      case WORSTFIT:
         memptr = worstfit_alloc (myAlloc, n_bytes);   break;
      default:
         memptr = NULL;                                break;
   }
   return memptr;
}

public void *memalloc (int handle, long n_bytes) {
   // check the handle is positive and in bounds
   if (handle < 0 || handle >= MAX_ALLOCATORS) {
      printf("Handle is not in bounds \n");
      return NULL;
   }
   allocator_ref myAlloc = allocators[handle];
   // check that the handle does not reference a null allocator
   if (myAlloc == NULL) {
      // return error
      printf("Handle was not found \n");
      return NULL; // Error, couldn't find handle
   }   
   // Determine flag specifics and allocate
   if (myAlloc->flags & BUDDY_FLAG) {
      // buddy
      return buddy_alloc (myAlloc, n_bytes);
   } else if (myAlloc->flags & FREELIST_FLAG) {
      // freelist
      if (myAlloc->flags & (FREELIST_FLAG | FIRSTFIT_FLAG)) {
         // first fit
         return firstfit_alloc (myAlloc, n_bytes);
      } else if (myAlloc->flags & (FREELIST_FLAG | NEXTFIT_FLAG)) {
         // next fit
         return nextfit_alloc (myAlloc, n_bytes);
      } else if (myAlloc->flags & (FREELIST_FLAG | BESTFIT_FLAG)) {
         // best fit
         return bestfit_alloc (myAlloc, n_bytes);
      } else if (myAlloc->flags & (FREELIST_FLAG | WORSTFIT_FLAG)) {
         // worst fit
         return worstfit_alloc (myAlloc, n_bytes);
      }
   }
   // print an error and return a null pointer if no flags matched
   printf("Incorrect flag entered \n");
   return NULL;
}

private void buddyFree (allocator_ref myAlloc, void *region) {
   assert (myAlloc != NULL && region != NULL);
   long memoryOffset = region - myAlloc->memory;  
   int level = myAlloc->buddyMaxLevel;
   int position = 0;
   int bytesFreed = 0;
   while (level >= 0) {
      float position2 = memoryOffset / ((float)(myAlloc->n_bytes)/pow(2,level));
      if (floor(position2) == position2) {
         position = (int)position2;
         if (getBMapBit(myAlloc, level, position) == 1) {
            setBMapBit(myAlloc, level, position, 0);
            bytesFreed = myAlloc->n_bytes / pow(2,level);
            break;
         }
      }
      level --;
      if (level == -1) {
         printf("No variable to free.\n");
         return;
      }
   }
   myAlloc->totalBytesUsed -= bytesFreed;
   int merging = 1;
   while (merging == 1) {
      if (getBMapBuddyBit(myAlloc, level, position) == 0) {
         level--;
         position /= 2;
         setBMapBit(myAlloc, level, position, 0);
      } 
	  else {
	     merging = 0;
	  }
      if (level < 0) merging = 0;
   }   
}

private void listFree (allocator_ref myAlloc, void *region) {
   assert (myAlloc != NULL && region != NULL);
   void *current;
   void *next;
   void *prev;
   next = NULL;
   prev = NULL;
   long user_size = *(long*)(region-4);
   current = myAlloc->memory;
   while(current != NULL){
      long curr_size = *(long*)(current-4);
      next = *(int*)current;
      // Find proper place to insert into list
      if (region < current){
         current = next;
         continue;
      }
      // Check if left region can merge with this free
      if (current + curr_size == region){
         *(long*)(current-4) += (user_size + 4);
         // Check if right region can merge with this free
         if ((current + *(long*)(current-4) + 4) == next){
            *(int*)current = *(int*)next;
            *(long*)(current-4) += *(long*)(next-4);
         }
      }
      else{
         *(int*)region = *(int*)current;
         *(int*)(current) = region;
         // Check if the right region can merge with this free
         if ((region + user_size + 4) == next){
            *(int*)region = *(int*)next;
            *(long*)(region-4) += *(long*)next;
         }
      }
   }
}

public void memfree (void *region) {
   if (region == NULL) {
      printf("Region is already null \n");
      return;
   }   
   int handle = -1;
   // iterate through each allocators until the region is found
   int i;
   for (i = 0; i < MAX_ALLOCATORS && handle == -1; ++i) {
      // search free list for region
      if (allocators[i] != NULL && (allocators[i]->flags & (FREELIST_FLAG))
          && (region >= allocators[i]->memory)
          && region < (allocators[i]->memory + allocators[i]->n_bytes - sizeof (struct allocator))) {
         handle = i;
      }
   }
   for (i = 0; i < MAX_ALLOCATORS && handle == -1; ++i) {
      // search buddy for region
      if (allocators[i] != NULL && (allocators[i]->flags & BUDDY_FLAG)
          && (region >= allocators[i]->memory)) {
         int minPageLength = (int)pow(2, allocators[i]->parm1);
         int smallestPageNumber = (allocators[i]->n_bytes)/minPageLength;
         int totalPositions = smallestPageNumber * 2;
         int buddyMapBytes = ceil((float)totalPositions / 32) * 4;
         int structsize = sizeof (struct allocator);
         if (region < (allocators[i]->memory - structsize - buddyMapBytes + allocators[i]->n_bytes)) {
            handle = i;
         }
      }
   }
   if (handle == -1) {
      printf("Region does not exist \n");
      return;
   }
   allocator_ref myAlloc = allocators[handle];   
   // call free method for the allocator
   if (myAlloc->flags & BUDDY_FLAG) {
      buddyFree (myAlloc, region);
   } else if (myAlloc->flags & FREELIST_FLAG) {
      listFree (myAlloc, region);
   }
}