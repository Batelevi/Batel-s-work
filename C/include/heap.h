/***********************************************
* Developer:   Batel Levi                      *
* Reviewer:                                    *
* Version:     1.0                             *
* Description: API for Heap.c                  *           
************************************************/
#ifndef __OL134_HEAP_H__
#define __OL134_HEAP_H__

#include <stddef.h> /*  For size_t  */

typedef struct heap heap_t;

/* HeapCreate:
	Description:
		Create Heap DS
	Params:
	    Compare function used to create max heap. in order to create min heap - reverse lhs and rhs in the compare function
	Return
	    Success - Pointer to heap DS                  
    	Failure - NULL
	Complexity:
		Time - O(1)
*/
heap_t *HeapCreate(int (*cmp_func)(const void *lhs, const void *rhs));

/* HeapDestroy:
	Description:
		Destroy DS
	Return
	    Void
	Complexity:
		Time - O(1)
*/
void HeapDestroy(heap_t *heap);

/* HeapPush:
	Description:
		Pushes a value into the heap
	Return
	    Success - 0
	    Failure - 1
	Complexity:
		Time - O(log(n)) 
*/
int HeapPush(heap_t *heap, void *data);

/* HeapPop:
	Description:
		Pops a value from the heap
	Complexity:
		Time - O(log(n))
*/
void HeapPop(heap_t *heap);

/* HeapPeek:
	Description:
        Gives an access to max element in the heap
	Complexity:
		Time - O(1)
*/
void *HeapPeek(heap_t *heap);

/* HeapSize:
	Return
	   Max element in the heap                  
	Complexity:
		Time - O(1)
*/
size_t HeapSize(const heap_t *heap);

/* HeapIsEmpty:
	Return:
	   1 - Empty
	   0 - Not empty
	Complexity:
		Time - O(1)
*/
int HeapIsEmpty(const heap_t *heap);

/* HeapRemove:
	Params:
	    heap            - Pointer to heap DS
	    is_match_func   - Used to remove data from heap via param
	    param           - Data to remove 
	Return:
        Success - Pointer to data removed
        Failure - NULL if element doesn't exist
	Complexity:
		Time - O(n)
*/
void *HeapRemove(heap_t *heap, int (*is_match_func)(const void *lhs, const void *rhs), void *param);

#endif /*__OL134_HEAP_H__*/