/************************************
* Developer:  Batel Levi            *
* Reviewer:                         *
* Version:    1.1                   *    
* Description: API for queue.c      * 
*************************************/

#ifndef __OL134_QUEUE_H__
#define __OL134_QUEUE_H__

#include <stddef.h>	/*	for size_t	*/

typedef struct queue queue_t;

/*------------------------------------*/
/* QueueCreate:

	Return:
		success: pointer to the new queue
		failure: NULL
	Complexity:
		Time - O(1) */
queue_t *QueueCreate(void);

/*------------------------------------*/
/* QueueDestroy:

	Params:
		queue
	Complexity:
		Time - O(n) */
void QueueDestroy(queue_t *queue);

/*------------------------------------*/
/* QueueEnqueue:

	Params:
		data, queue
	Return:
		0 if success, 1 if fail
	Complexity:
		Time - O(1) */
int QueueEnqueue(queue_t *queue, void *data);

/*------------------------------------*/
/* QueueDequeue:
	
	Params:
		queue
	Complexity:
		Time - O(1) 
	Note:
		Undefined behaviour incase of empty queue */
void QueueDequeue(queue_t *queue);

/*------------------------------------*/
/* QueuePeek:

	Params:
		queue
	Return:
		data in the first node of the queue
	Complexity:
		Time - O(1) */
void *QueuePeek(const queue_t *queue);

/*------------------------------------*/
/* QueueSize:
	
	Params:
		queue
	Return:
		number of nodes in the queue
	Complexity:
		Time - O(n) */

size_t QueueSize(const queue_t *queue);

/*------------------------------------*/
/* QueueIsEmpty:
 	
	Params:
		queue
	Return:
		1 if empty, 0 if not
	Complexity:
		Time - O(1) */
int QueueIsEmpty(const queue_t *queue);

/*------------------------------------*/
/* QueueAppend:
 	
 	Description: concatenate all the elements from src and appends them to dest
 				 queue concatenation causes src to be empty after concatenation
	Params:
		dest - queue to be concatenated 
		source - queue appended to dest
	Complexity:
		Time - O(1) */
void QueueAppend(queue_t *dest, queue_t *src);

/*------------------------------------*/
#endif /*__OL134_QUEUE_H__*/
