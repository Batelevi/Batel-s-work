/*********************************************
* Developer:   Batel Levi                    *
* Reviewer:                                  *
* Version:     1.1                           *  
* Description: API for priority_queue.c      * 
*********************************************/

#ifndef __OL134_P_QUEUE_H__
#define __OL134_P_QUEUE_H__


#include <stddef.h> /*size_t*/

typedef struct pqueue pqueue_t;

typedef int (*pq_is_match_func_t)(const void *data, const void *criteria);
typedef int (*pq_cmp_func_t)(const void *lhs, const void *rhs);


/*------------------------------------*/
/* PQueueCreate:
	Params:
		cmp function for defining priority
	Return:
		pointer to the new created queue if success, NULL if failed
	Complexity:
		Time - O(1) */
pqueue_t *PQueueCreate(pq_cmp_func_t cmp_func);

/*------------------------------------*/
/* PQueueDestroy:

	Params:
		queue
	Complexity:
		Time - O(n) */
void PQueueDestroy(pqueue_t *pqueue);

/*------------------------------------*/
/* PQueueEnqueue:

	Params:
		data, queue
	Return:
		0 if success, 1 if fail
	Complexity:
		Time - O(n) */
int PQueueEnqueue(pqueue_t *pqueue, void *data);

/*------------------------------------*/
/* PQueueDequeue:
	
	Params:
	    pqueue - the existing pqueue
	Complexity:
		Time - O(1) 
	Note:
		Undefined behaviour incase of empty queue */
void PQueueDequeue(pqueue_t *pqueue);

/*------------------------------------*/
/* PQueuePeek:

	Params:
		pqueue - the existing pqueue
    Return:
		data in the first element of the queue
	Complexity:
		Time - O(1) */
void *PQueuePeek(const pqueue_t *pqueue);

/*------------------------------------*/
/* PQueueSize:
	
	Params:
	    pqueue - the existing pqueue
	Return:
		number of nodes in the queue
	Complexity:
		Time - O(n) */
size_t PQueueSize(const pqueue_t *pqueue);

/*------------------------------------*/
/* PQueueIsEmpty:
 	
	Params:
		pqueue - the existing pqueue
	Return:
		1 if empty, 0 if not
	Complexity:
		Time - O(1) */
int PQueueIsEmpty(const pqueue_t *pqueue);

/*------------------------------------*/
/* PQueueClear:
	Description:
		Removing all the elements in the pqueue but keeps the pqueue itself
	Params:
		pqueue - our pqueue to clear
	Complexity:
		Time - O(n)
	Note: undefined behavior on empty queue*/
void PQueueClear(pqueue_t *pqueue);

/*------------------------------------*/
/* PQueueErase:
	Description:
		Removing specific element from the pqueue, no related to priority
	Params:
		pqueue - our pqueue to remove data element from
		data - data we want to erase
	Return:
	    data - retruns the data of the erased element
	    NULL - if the data doesn't exist
	Complexity:
		Time - O(n) 
	Attention: is_match is a compare function provided by the user and should know how to find the data via param
	            must return 1 if match found, 0 if not found*/
void *PQueueErase(pqueue_t *pqueue, pq_is_match_func_t is_match, void *param);

/*------------------------------------*/
#endif /*__OL134_P_QUEUE_H__*/
