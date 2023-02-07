/*****************************************
* Developer:      Batel Levi             *
* Reviewer:       Idan                   * 
******************************************/

#include <stddef.h> /* for size_t */
#include <stdlib.h>	/*	for malloc realloc	*/
#include <assert.h>	/*	for assert	*/
#include <string.h>	/*	for memcpy	*/

#include "dynamic_vector.h"	/*	header file	*/

#define GROWTH_FACTOR 2


struct vector
{
	size_t capacity;
	size_t element_size;
	size_t size;
	char *buffer;
};


vector_t *VectorCreate(size_t capacity, size_t element_size)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	
	if (NULL == vector)
	{
		return (vector);
	}

	vector->capacity = capacity;

	vector->element_size = element_size;

	vector->size = 0;
	
	vector->buffer = (char *)malloc(capacity * element_size);
	
	if (NULL == vector->buffer)
	{
		free(vector);
		return NULL;
	}	

	return (vector);
}

void VectorDestroy(vector_t *vector)
{
	assert(vector);
	
	free(vector->buffer);
	
	free(vector);
}

int VectorPushBack(vector_t *vector, const void *new_element)
{
	char *temp = NULL;
	
	assert(vector);
	assert(new_element);
	
	if (vector->size == vector->capacity)	/*	if is full	*/
	{
		temp = (char *)realloc(vector->buffer, vector->capacity * vector->element_size * GROWTH_FACTOR);
		
		if (NULL == temp)
		{
			return (1);
		}
		
		vector->buffer = temp;
		
		vector->capacity *= GROWTH_FACTOR;
	}
	
	memcpy(&vector->buffer[vector->size * vector->element_size], new_element, vector->element_size);
	
	++vector->size;
	
	return (0);
}

void VectorPopBack(vector_t *vector)
{
	assert(vector);
	assert(vector->size > 0);
	
	--vector->size;
}

void *VectorGetAccessToElement(const vector_t *vector, size_t element_index)
{
	assert(vector);
	
	assert(element_index < vector->size);
	
	return (&vector->buffer[element_index * vector->element_size]);
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	char *temp = NULL;
	
	assert(vector);
	
	temp = (char *)realloc(vector->buffer, new_capacity * vector->element_size);
	
	if (NULL == temp)
	{
		return (1);
	}
	
	vector->buffer = temp;
	vector->capacity = new_capacity;
	
	return (0);
}

int VectorShrink(vector_t *vector) /* shrinks vector to current size */
{
	char *temp = NULL;
	
	assert(vector);

	temp = (char *)realloc(vector->buffer, vector->size * vector->element_size);
	
	if (NULL == temp)
	{
		return (1);
	}
	
	vector->buffer = temp;
	vector->capacity = vector->size;
	
	return (0);
}

size_t VectorSize(const vector_t *vector)
{
	assert(vector);
	
	return (vector->size);
}

int VectorIsEmpty(const vector_t *vector)
{
	assert(vector);
	
	return (vector->size == 0);
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);
	
	return (vector->capacity);
}
