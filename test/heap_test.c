#include <stdio.h>
#include <assert.h>	/*	for assert	*/

#include "heap.h"	/*	header file	*/
#include "dynamic_vector.h"	/*	header file	*/

#define TYPE int
#define SIZEOFTYPE(x) (char )((x)0 + 1)

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int failure = 0;

void TestHeap();
void PrintError(char *name, int line ,long int function_result ,long int should_be);

int Compar(const void *lhs, const void *rhs);
int IsMatch(const void *lhs, const void *rhs);

struct heap
{
    int (*cmp_func)(const void *lhs, const void *rhs);
    vector_t *vector;
};

void PrintVector(vector_t *vector);


int main ()
{
	TestHeap();
	
	return (0);
}


void TestHeap()
{
	heap_t *heap = HeapCreate(Compar);
	int a15 = 15;
	int a10 = 10;
	int a20 = 20;
	int a9 = 9;
	int a16 = 16;
	int a25 = 25;
	int a7 = 7;
	int a2 = 2;
	int a8 = 8;

	PrintError("HeapCreate", __LINE__, !heap, 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 0);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 1);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a10), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 1);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a10);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a15), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 2);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a15);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a20), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 3);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a9), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 4);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a16), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 5);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a25), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 6);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a25);

	HeapPop(heap);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 5);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	HeapPop(heap);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 4);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a16);

	HeapPop(heap);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 3);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a15);

	HeapPop(heap);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 2);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a10);

	HeapPop(heap);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 1);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a9);

	HeapPop(heap);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 0);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 1);
	/*PrintError("HeapPeek", __LINE__, (size_t)HeapPeek(heap), 0);*/

	
	PrintError("HeapPush", __LINE__, HeapPush(heap, &a10), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 1);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a10);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a15), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 2);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a15);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a20), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 3);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a9), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 4);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a16), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 5);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a25), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 6);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a25);

	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a10), a10);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 5);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a25);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a7), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 6);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a25);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a2), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 7);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a25);

	PrintError("HeapPush", __LINE__, HeapPush(heap, &a8), 0);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 8);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a25);

	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a16), a16);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 7);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a25);

	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a25), a25);
	PrintError("HeapSize", __LINE__, HeapSize(heap), 6);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);
	HeapPop(heap);

	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 1);
	
	HeapPush(heap, &a2);
	HeapPush(heap, &a7);
	HeapPush(heap, &a10);
	HeapPush(heap, &a16);
	HeapPush(heap, &a8);
	HeapPush(heap, &a9);
	HeapPush(heap, &a20);
	HeapPush(heap, &a15);
	HeapPush(heap, &a25);

	PrintError("HeapSize", __LINE__, HeapSize(heap), 9);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a25);

	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a15), a15);
	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a8), a8);
	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a16), a16);
	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a25), a25);
	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a9), a9);
	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a2), a2);
	PrintError("HeapRemove", __LINE__, *(int *)HeapRemove(heap, IsMatch, &a10), a10);

	PrintError("HeapSize", __LINE__, HeapSize(heap), 2);
	PrintError("HeapIsEmpty", __LINE__, HeapIsEmpty(heap), 0);
	PrintError("HeapPeek", __LINE__, *(int *)HeapPeek(heap), a20);

	PrintVector(heap->vector);

	HeapDestroy(heap);

	if (0 == failure)
	{
		printf("Heap - %s\n", SUCCESS);
	}
}

int Compar(const void *lhs, const void *rhs)
{
	assert(lhs);
	assert(rhs);

	return (*(int *)lhs - *(int *)rhs);
}

int IsMatch(const void *lhs, const void *rhs)
{
	assert(lhs);
	assert(rhs);

	return (*(int *)lhs == *(int *)rhs);
}

void PrintVector(vector_t *vector)
{
    size_t i = 0;    
    size_t vector_size = VectorSize(vector);
    
    printf("Heap:\n");
    
    for(i = 0; i < vector_size; i++)
    {
        printf("%d ", **(TYPE **)VectorGetAccessToElement(vector, i));    
    }

	printf("\n\n");
}

void PrintError(char *name, int line ,long int function_result ,long int should_be)
{
	if (function_result != should_be)
	{
		printf("%s - %s - in line %d - function result is: %ld and should be: %ld\n", name, FAILURE, line, function_result, should_be);
		failure = 1;
	}
}