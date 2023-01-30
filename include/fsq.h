/************************************
* Developer:   Batel Levi           *
* Reviewer:                         *
* Version:     1.0                  *
* Description: API for fsq.c        * 
*************************************/
#ifndef __OL134_FSQ_H__
#define __OL134_FSQ_H__

#include <stddef.h>	/*	for size_t	*/

typedef struct fsq fsq_t;

/*------------------------------------*/
/* FSQCreate:

	Return:
		Success - pointer to the new fsq
		Failure - NULL
	Complexity:
		Time - O(1) */
fsq_t *FSQCreate(size_t capacity);

/*------------------------------------*/
/* FSQDestroy:

	Params:
		fsq
	Complexity:
		Time - O(n) */
void FSQDestroy(fsq_t *fsq);

/*------------------------------------*/
/* FSQEnqueue:

	Params:
		data, fsq
	Return:
		Success - 0
		Failure - 1
	Complexity:
		Time - O(1) */
int FSQEnqueue(fsq_t *fsq, void *data);

/*------------------------------------*/
/* FSQDequeue:
	
	Params:
		fsq
	Complexity:
		Time - O(1) 
	Note:
		Undefined behavior in case of empty fsq */
void FSQDequeue(fsq_t *fsq);

/*------------------------------------*/
/* FSQPeek:

	Params:
		fsq
	Return:
		data in the first node of the fsq
	Complexity:
		Time - O(1) */
void *FSQPeek(const fsq_t *fsq);

/*------------------------------------*/
/* FSQSize:
	
	Params:
		fsq
	Return:
		number of nodes in the fsq
	Complexity:
		Time - O(n) */

size_t FSQSize(const fsq_t *fsq);

/*------------------------------------*/
/* FSQCapacity:
	
	Params:
		fsq
	Return:
		capacity of the fsq
	Complexity:
		Time - O(n) */

size_t FSQCapacity(const fsq_t *fsq);

/*------------------------------------*/
/* FSQIsEmpty:
 	
	Params:
		fsq
	Return:
		1 if empty, 0 if not
	Complexity:
		Time - O(1) */
int FSQIsEmpty(const fsq_t *fsq);

/*------------------------------------*/
/* FSQAppend:
 	
 	Description: concatenate all the elements from src and appends them to dest
				 only if not exceeds the capacity.
 				 fsq concatenation causes src to be empty after concatenation
	Params:
		dest	- fsq to be concatenated 
		source	- fsq appended to dest
	Complexity:
		Time - O(1) */
void FSQAppend(fsq_t *dest, fsq_t *src);

/*------------------------------------*/
#endif /*__OL134_FSQ_H__*/