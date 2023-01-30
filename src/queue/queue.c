#include <stdlib.h>	/*	for malloc	*/
#include <assert.h>	/*	for assert	*/

#include "queue.h"	/*	header file	*/
#include "singly_linked_list.h"	/*	header file	*/

struct queue
{
	list_t *list; 	
};


queue_t *QueueCreate(void)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	
	if (NULL == queue)
	{
		return NULL;
	}
	
	queue->list = ListCreate();
	
	if (NULL == queue->list)
	{
		free(queue);
		return NULL;
	}
	
	return (queue);
}

void QueueDestroy(queue_t *queue)
{
	assert(queue);
	
	ListDestroy(queue->list);
	
	free(queue);
}

int QueueEnqueue(queue_t *queue, void *data)
{
	list_iterator_t insert = NULL;
	
	assert(queue);
	assert(data);
	
	insert = ListInsert(data, ListTail(queue->list));
	
	return (ListIsSame(insert, ListTail(queue->list)));
}

void QueueDequeue(queue_t *queue)
{
	assert(queue);
	
	ListRemove(ListHead(queue->list));
}

void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	
	return (ListGetData(ListHead(queue->list)));
}

size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	
	return (ListSize(queue->list));
}


int QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return (ListIsEmpty(queue->list));
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);
	
	ListAppend(dest->list, src->list);
}
