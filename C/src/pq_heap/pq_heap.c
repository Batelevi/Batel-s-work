/*********************************************
* Developer:   Batel Levi                    *
* Reviewer:    Idan                          *
*********************************************/

#include <stddef.h>	/*	for size_t	*/
#include <assert.h>	/*	for assert	*/
#include <stdlib.h>	/*	for malloc	*/

#include "pq_heap.h"	/*	header file	*/
#include "heap.h"	/*	header file	*/

#define TO_HEAP(x) ((x)->heap) 


struct pqueue
{
	heap_t *heap;
};


pqueue_t *PQueueCreate(pq_cmp_func_t cmp_func)
{
	pqueue_t *pqueue = NULL;
	
	assert(cmp_func);

	pqueue = (pqueue_t *)malloc(sizeof(pqueue_t));
	
	if (NULL == pqueue)
	{
		return NULL;
	}

	pqueue->heap = HeapCreate(cmp_func);
	
	if (NULL == pqueue->heap)
	{
		free(pqueue);
		return NULL;
	}
	
	return (pqueue);
}


void PQueueDestroy(pqueue_t *pqueue)
{
	assert(pqueue);
	
	HeapDestroy(TO_HEAP(pqueue));
	
	free(pqueue);
	pqueue = NULL;
}


int PQueueEnqueue(pqueue_t *pqueue, void *data)
{
	assert(pqueue);
	assert(data);
		
	return (HeapPush(TO_HEAP(pqueue), data));
}


void PQueueDequeue(pqueue_t *pqueue)
{
	assert(pqueue);
	
	HeapPop(TO_HEAP(pqueue));
}

void *PQueuePeek(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (HeapPeek(TO_HEAP(pqueue)));
}


size_t PQueueSize(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (HeapSize(TO_HEAP(pqueue)));
}


int PQueueIsEmpty(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (HeapIsEmpty(TO_HEAP(pqueue)));
}


void PQueueClear(pqueue_t *pqueue)
{
	assert(pqueue);
	
	while (!PQueueIsEmpty(pqueue))
	{
		PQueueDequeue(pqueue);
	}
}


void *PQueueErase(pqueue_t *pqueue, pq_is_match_func_t is_match, void *param)
{
	assert(pqueue);
	
	return (HeapRemove(TO_HEAP(pqueue), is_match, param));
}
