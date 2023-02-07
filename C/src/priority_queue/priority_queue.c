/*********************************************
* Developer:   Batel Levi                    *
* Reviewer:    Idan                          *
*********************************************/

#include <stddef.h>	/*	for size_t	*/
#include <assert.h>	/*	for assert	*/
#include <stdlib.h>	/*	for malloc	*/

#include "priority_queue.h"	/*	header file	*/
#include "sorted_list.h"	/*	header file	*/

#define TO_SORTED_LIST(x) ((x)->sorted_list) 


struct pqueue
{
	sorted_list_t *sorted_list;
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

	pqueue->sorted_list = SortedListCreate(cmp_func);
	
	if (NULL == pqueue->sorted_list)
	{
		free(pqueue);
		return NULL;
	}
	
	return (pqueue);
}


void PQueueDestroy(pqueue_t *pqueue)
{
	assert(pqueue);
	
	SortedListDestroy(TO_SORTED_LIST(pqueue));
	
	free(pqueue);
	pqueue = NULL;
}


int PQueueEnqueue(pqueue_t *pqueue, void *data)
{
	sorted_list_iter_t iter = {0};
	
	assert(pqueue);
	assert(data);
	
	iter = SortedListInsert(TO_SORTED_LIST(pqueue), data);
	
	return (SortedListIsSameIter(iter, SortedListEnd(TO_SORTED_LIST(pqueue))));
}


void PQueueDequeue(pqueue_t *pqueue)
{
	assert(pqueue);
	
	SortedListPopFront(TO_SORTED_LIST(pqueue));
}

void *PQueuePeek(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (SortedListGetData(SortedListBegin(TO_SORTED_LIST(pqueue))));
}


size_t PQueueSize(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (SortedListSize(TO_SORTED_LIST(pqueue)));
}


int PQueueIsEmpty(const pqueue_t *pqueue)
{
	assert(pqueue);
	
	return (SortedListIsEmpty(TO_SORTED_LIST(pqueue)));
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
	sorted_list_iter_t iter;
	void *data = NULL;
	
	assert(pqueue);
	
	iter = SortedListFindIf(SortedListBegin(TO_SORTED_LIST(pqueue)),
							SortedListEnd(TO_SORTED_LIST(pqueue)),
							is_match,
							param);
	
	if (!SortedListIsSameIter(iter, SortedListEnd(TO_SORTED_LIST(pqueue))))
	{
		data = SortedListGetData(iter);
		SortedListRemove(iter);
	}
	
	return (data);
}
