/************************************
* Developer:  Batel Levi            *
* Reviewer:   ---                   *
* Version:    2.0                   *    
* Description: API for              *
*              circular_buffer.c    * 
*************************************/
#ifndef __OL134_CIRCULAR_BUFFER_H__
#define __OL134_CIRCULAR_BUFFER_H__

#include <stddef.h>		/*	size_t	*/
#include <sys/types.h>	/*	ssize_t	*/


typedef struct circular_buffer circular_buffer_t;

/*------------------------------------*/
/* CircularBufferCreate:
	param:
		the size of the buffer
	Return:
		succeed : returns pointer to the new buffer
		fail : returns NULL
	Complexity:
		Time - O(1) */
circular_buffer_t *CBufferCreate(size_t capacity);

/*------------------------------------*/
/* CBufferDestroyed:
	param:
		buffer
	Complexity:
		Time - O(1) */
void CBufferDestroy(circular_buffer_t *buffer);

/*------------------------------------*/	
/* CBufferFreeSpace:
	param:
		buffer
	return: 
		The number of free bytes left in the buffer
	Complexity:
		Time - O(1) */
size_t CBufferFreeSpace(const circular_buffer_t *buffer);

/*------------------------------------*/
/* CBuffersiz:
	param:
		buffer
	return: 
		The number of written bytes.  
	Complexity:
		Time - O(1) */

size_t CBuffersiz(const circular_buffer_t *buffer);
/*------------------------------------*/
/* CBuffferRead:
	param:
		buffer - the buffer which holds the source data
		dest - the destination to copy the data
		count - the number of bytes to be copy 
	outparam:
		dest - where the data copyied to 
	return: 
		The number of read bytes. 
	Complexity:
		Time - O(n) 
	Functionality: attemps to read count bytes from buffer to dest */
	
ssize_t CBufferRead(circular_buffer_t *buffer, void *dest, size_t count);
/*------------------------------------*/

/* CBuffferWrite:
	param:
		buffer - the destination buffer to write the data
		src - the data from the user to becopy 
		count - size of bytes to be copy  
	return: 
		The number of written bytes. 		 
	Complexity:
		Time - O(n) 
	Functionality: writes from src to buffer */		
	
ssize_t CBufferWrite(circular_buffer_t *buffer, const void *src, size_t count);
/*------------------------------------*/
			
/* CBuffferIsEmpty:
	param:
		buffer
	return: 
		 1 for empty, 0 if not.		 
	Complexity:
		Time - O(1) */
int CBufferIsEmpty(const circular_buffer_t *buffer);
/*------------------------------------*/				
		
#endif/*__OL134_CIRCULAR_BUFFER_H__*/	
