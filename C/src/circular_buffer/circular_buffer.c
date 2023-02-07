/************************************
* Developer:  Batel Levi            *
* Reviewer:   Shalev                *
*************************************/

#include <stdlib.h>	/*	for malloc	*/
#include <string.h>	/*	for memcpy	*/
#include <assert.h>	/*	for assert	*/

#include "circular_buffer.h"	/*	header file	*/

#define REMAINING_BYTES(x) (count - (buffer->capacity - (x)))

struct circular_buffer
{
	size_t read_offset;
	size_t capacity;
	size_t size;
	char buffer[1];
};

circular_buffer_t *CBufferCreate(size_t capacity)
{
	circular_buffer_t *buffer = NULL;
	
	assert(0 < capacity);
	
	buffer = (circular_buffer_t *)malloc(sizeof(size_t) * 3 + capacity);
	
	if (NULL == buffer)
	{
		return NULL;
	}

	buffer->read_offset = 0;
	buffer->capacity = capacity;
	buffer->size = 0;
	buffer->buffer[0] = '\0';
	
	return (buffer);
}


void CBufferDestroy(circular_buffer_t *buffer)
{
	assert(buffer);
	
	free(buffer);
	buffer = NULL;
}


size_t CBufferFreeSpace(const circular_buffer_t *buffer)
{
	assert(buffer);
	
	return (buffer->capacity - buffer->size);
}


size_t CBuffersiz(const circular_buffer_t *buffer)
{
	assert(buffer);
	
	return (buffer->size);
}

	
ssize_t CBufferRead(circular_buffer_t *buffer, void *dest, size_t count)
{
	size_t count_left = 0;
	
	assert(buffer);
	assert(dest);
	
	if (CBufferIsEmpty(buffer))
	{
		return 0;
	}
	
	count = count > buffer->size ? buffer->size : count;

	/* count_left is the number of bytes which remain to read from the beginning of the array	*/
	if (buffer->read_offset + count > buffer->capacity)
	{
		count_left =  REMAINING_BYTES(buffer->read_offset);

		count -= count_left;

		memcpy((char *)dest + count, buffer->buffer, count_left);		
	}
	
	memcpy(dest, buffer->buffer + buffer->read_offset, count);	

	buffer->read_offset += count + count_left;
	buffer->read_offset %= buffer->capacity;
	
	buffer->size -= count + count_left;
	
	return (count + count_left);
}
	
	
ssize_t CBufferWrite(circular_buffer_t *buffer, const void *src, size_t count)
{
	size_t count_left = 0;
	size_t write_offset = 0;
	
	assert(buffer);
	assert(src);
	
	write_offset = (buffer->read_offset + buffer->size) % buffer->capacity;
	
	count = count > CBufferFreeSpace(buffer) ? CBufferFreeSpace(buffer) : count;

	/* count_left is the number of bytes which remain to write from the beginning of the array	*/
	if (write_offset + count > buffer->capacity)
	{
		count_left =  REMAINING_BYTES(write_offset);
	
		count -= count_left;
	
		memcpy(buffer->buffer, (char *)src + count, count_left);
	}
		
	memcpy(buffer->buffer + write_offset, src, count);

	buffer->size += count + count_left;
	
	return (count + count_left);
}


int CBufferIsEmpty(const circular_buffer_t *buffer)
{
	assert(buffer);
	
	return (0 == buffer->size);
}
