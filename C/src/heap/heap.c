/***********************************************
* Developer:   Batel Levi                      *
* Reviewer:    Shalev                          *         
************************************************/
#include <assert.h>	/*	for assert	*/
#include <stdlib.h>	/*	for malloc	*/

#include "heap.h"	/*	header file	*/
#include "dynamic_vector.h"	/*	header file	*/

#define INIT_SIZE 10


struct heap
{
    int (*cmp_func)(const void *lhs, const void *rhs);
    vector_t *vector;
};

static void HeapifyUp(heap_t *heap, size_t i_child);
static void HeapifyDown(heap_t *heap, size_t i_parent);
static void Swap(void *param1, void *param2);


heap_t *HeapCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	heap_t *heap = (heap_t *)malloc(sizeof(heap_t));

	if (NULL == heap)
	{
		return NULL;
	}

	assert(cmp_func);

	heap->cmp_func = cmp_func;
	heap->vector = VectorCreate(INIT_SIZE, sizeof(size_t));

	if (NULL == heap->vector)
	{
		free(heap);
		return NULL;
	}

	return (heap);
}

void HeapDestroy(heap_t *heap)
{
	assert(heap);

	VectorDestroy(heap->vector);
	free(heap);
}

int HeapPush(heap_t *heap, void *data)
{
	assert(heap);

	if (VectorPushBack(heap->vector, &data))
	{
		return (1);
	}

	HeapifyUp(heap, HeapSize(heap) - 1);

	return (0);
}

static void HeapifyUp(heap_t *heap, size_t i_child)
{
	void **child = NULL;
	void **parent = NULL;
	size_t i_parent = 0;

	child = VectorGetAccessToElement(heap->vector, i_child);
	i_parent = (i_child - 1) / 2 * !!i_child;
	parent = VectorGetAccessToElement(heap->vector, i_parent);

	while (heap->cmp_func(*parent, *child) < 0)
	{
		Swap(parent, child);
		child = parent;
		i_child = i_parent;
		i_parent = (i_child - 1) / 2 * !!i_child;
		parent = VectorGetAccessToElement(heap->vector, i_parent);
	}
}

static void Swap(void *param1, void *param2)
{
	size_t temp = 0;

	assert(param1);
	assert(param2);

	temp = *(size_t *)param1;
	*(size_t *)param1 = *(size_t *)param2;
	*(size_t *)param2 = temp;
}

void HeapPop(heap_t *heap)
{
	void **peek = NULL;
	void **last = NULL;

	assert(heap);

	if (HeapIsEmpty(heap))
	{
		return;
	}

	peek = VectorGetAccessToElement(heap->vector, 0);
	last = VectorGetAccessToElement(heap->vector, VectorSize(heap->vector) - 1);

	Swap(peek, last);
	VectorPopBack(heap->vector);

	if (HeapSize(heap) > 1)
	{
		HeapifyDown(heap, 0);
	}
}

static void HeapifyDown(heap_t *heap, size_t i_parent)
{
	void **parent = NULL;
	void **child = NULL;
	size_t i_child = 0;

	assert(heap);

	parent = VectorGetAccessToElement(heap->vector, i_parent);
	i_child = i_parent;
	i_child += (i_child + 1) * (HeapSize(heap) > i_child * 2 + 1);

	/*	note - in cases where the elements are equal, it doesn't necessarily
		keep the insert order - relevant to PQ	*/
	if (HeapSize(heap) > i_child + 1)
	{
		i_child += heap->cmp_func(*(void **)VectorGetAccessToElement(heap->vector, i_child + 1),
							  	  *(void **)VectorGetAccessToElement(heap->vector, i_child)) >= 0; 
	}

	child = VectorGetAccessToElement(heap->vector, i_child);

	while (i_child != i_parent && heap->cmp_func(*parent, *child) <= 0)
	{
		Swap(parent, child);
		parent = child;
		i_parent = i_child;
		i_child = i_parent;
		i_child += (i_child + 1) * (HeapSize(heap) > i_child * 2 + 1);

		if (HeapSize(heap) > i_parent * 2 + 2)
		{
			i_child += heap->cmp_func(*(void **)VectorGetAccessToElement(heap->vector, i_child + 1),
									  *(void **)VectorGetAccessToElement(heap->vector, i_child)) >= 0; 
		}

		child = VectorGetAccessToElement(heap->vector, i_child);
	}
}

void *HeapPeek(heap_t *heap)
{
	assert(heap);

	if (HeapIsEmpty(heap))
	{
		return NULL;
	}

	return (*(void **)VectorGetAccessToElement(heap->vector, 0));
}

size_t HeapSize(const heap_t *heap)
{
	assert(heap);

	return (VectorSize(heap->vector));
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);

	return (VectorIsEmpty(heap->vector));
}

void *HeapRemove(heap_t *heap, int (*is_match_func)(const void *lhs, const void *rhs),
				 void *param)
{
	void *to_remove = NULL;
	size_t i = 0;

	assert(heap);
	assert(is_match_func);

	for (i = 0; i < HeapSize(heap); ++i)
	{
		if (is_match_func(*(void **)VectorGetAccessToElement(heap->vector, i), param))
		{
			break;
		}
	}

	if (i == HeapSize(heap))
	{
		return NULL;
	}

	to_remove = *(void **)VectorGetAccessToElement(heap->vector, i);

	Swap(VectorGetAccessToElement(heap->vector, i), 
		 VectorGetAccessToElement(heap->vector, HeapSize(heap) - 1));
	
	VectorPopBack(heap->vector);

	if ((int)i < (int)HeapSize(heap) - 1)
	{
		param = *(void **)VectorGetAccessToElement(heap->vector, i);

		HeapifyUp(heap, i);

		if (is_match_func(*(void **)VectorGetAccessToElement(heap->vector, i), param))
		{
			HeapifyDown(heap, i);
		}
	}

	return (to_remove);
}