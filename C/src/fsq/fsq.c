#include <stdlib.h>	/*	for malloc	*/
#include <assert.h>	/*	for assert	*/

#include "fsq.h"	/*	header file	*/
#include "singly_linked_list.h"	/*	header file	*/

struct fsq
{
	list_t *list;
	size_t capacity;
};


fsq_t *FSQCreate(size_t capacity)
{
	fsq_t *fsq = (fsq_t *)malloc(sizeof(fsq_t));
	
	if (NULL == fsq)
	{
		return NULL;
	}
	
	fsq->list = ListCreate();
	fsq->capacity = capacity;
	
	if (NULL == fsq->list)
	{
		free(fsq);
		return NULL;
	}
	
	return (fsq);
}

void FSQDestroy(fsq_t *fsq)
{
	assert(fsq);
	
	ListDestroy(fsq->list);
	
	free(fsq);
}

int FSQEnqueue(fsq_t *fsq, void *data)
{
	list_iterator_t insert = NULL;
	
	assert(fsq);
	assert(data);
	
	insert = ListTail(fsq->list);
	
	if (FSQSize(fsq) < fsq->capacity)
	{
		insert = ListInsert(data, ListTail(fsq->list));
	}
	
	return (ListIsSame(insert, ListTail(fsq->list)));
}

void FSQDequeue(fsq_t *fsq)
{
	assert(fsq);
	
	ListRemove(ListHead(fsq->list));
}

void *FSQPeek(const fsq_t *fsq)
{
	assert(fsq);
	
	return (ListGetData(ListHead(fsq->list)));
}

size_t FSQSize(const fsq_t *fsq)
{
	assert(fsq);
	
	return (ListSize(fsq->list));
}

size_t FSQCapacity(const fsq_t *fsq)
{
	assert(fsq);
	
	return (fsq->capacity);	
}

int FSQIsEmpty(const fsq_t *fsq)
{
	assert(fsq);
	
	return (ListIsEmpty(fsq->list));
}

void FSQAppend(fsq_t *dest, fsq_t *src)
{
	assert(dest);
	assert(src);
	
	if (FSQSize(dest) + FSQSize(src) <= dest->capacity)
	{
		ListAppend(dest->list, src->list);
	}
}