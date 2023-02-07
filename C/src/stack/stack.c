/************************************
* Developer: Batel Levi             *
* Reviewer:                         *
************************************/

#include <assert.h>	/* for assert	*/
#include <stdlib.h>	/*	for malloc	*/
#include <string.h>	/*	for memcpy	*/

#include "stack.h"	/*	header file	*/

struct stack
{
	size_t capacity;
	size_t element_size;
	size_t size;
	char *buffer;
};


stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	
	if (NULL == stack)
	{
		return (stack);
	}
	
	stack->capacity = capacity;
	
	stack->element_size = element_size;

	stack->size = 0;
	
	stack->buffer = (char *)malloc(capacity * element_size);
	
	if (NULL == stack->buffer)
	{
		free(stack);
		return NULL;
	}
	
	return (stack);
}

void StackDestroy(stack_t *stack)
{
	assert(stack);
	
	free(stack->buffer);
	
	free(stack);
}

void StackPush(stack_t *stack, const void *new_element)
{
	assert(stack);
	assert(new_element);
	
	memcpy(&stack->buffer[stack->size * stack->element_size], new_element, stack->element_size);

	++stack->size;
}

void StackPop(stack_t *stack)
{
	assert(stack);
	
	--stack->size;
}

void *StackPeek(const stack_t *stack)
{
	assert(stack);

	return(&stack->buffer[(stack->size - 1) * stack->element_size]);
}

size_t StackSize(const stack_t *stack)
{
	assert(stack);
	
	return (stack->size);
}

int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	
	return (!stack->size);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(stack);
		
	return (stack->capacity);
}

