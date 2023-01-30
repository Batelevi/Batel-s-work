#include <stdio.h>
#include <assert.h>	/*	for assert	*/


#include "priority_queue.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int failure = 0;

void TestPriorityQueue();
void PrintError(char *name, int line ,int function_result ,int should_be);

int Cmp(const void *rhs, const void *lhs);	/*	priority by tens digit	*/
int IsMatch(const void *rhs, const void *lhs);

int main ()
{
	TestPriorityQueue();
	
	return (0);
}


void TestPriorityQueue()
{
	pqueue_t *pqueue = PQueueCreate(Cmp);
	int a1 = 10;
	int a2 = 20;
	int a23 = 23;
	int a3 = 30;
	int a35 = 35;
	int a4 = 40;
	size_t size = 0;


	if (pqueue == NULL)
	{
		printf("PQueueCreate - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;
	}

	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
	PrintError("PQueueIsEmpty", __LINE__, (int)PQueueIsEmpty(pqueue), !(int)size);

	PQueueEnqueue(pqueue, &a23);
	PQueueEnqueue(pqueue, &a2);

	size += 2;

	PrintError("PQueueIsEmpty", __LINE__, (int)PQueueIsEmpty(pqueue), !(int)size);	
/*	printf("%d\n", *(int *)PQueuePeek(pqueue));*/

	PrintError("PQueueEnqueue", __LINE__, *(int *)PQueuePeek(pqueue), a23);
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
	
	PQueueDequeue(pqueue);
	--size;
	
	PrintError("PQueueEnqueue or PQueueDequeue", __LINE__, *(int *)PQueuePeek(pqueue), a2);
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);

	PQueueEnqueue(pqueue, &a23);
	PQueueEnqueue(pqueue, &a3);
	PQueueEnqueue(pqueue, &a35);	
	PQueueEnqueue(pqueue, &a2);
	PQueueEnqueue(pqueue, &a4);
	PQueueEnqueue(pqueue, &a1);
	size += 6;

	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
/*
	printf("%d\n", *(int *)PQueuePeek(pqueue));
	PQueueDequeue(pqueue);
	--size;	
*/

	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);

	PQueueClear(pqueue);
	size = 0;

	PQueueEnqueue(pqueue, &a23);
	PQueueEnqueue(pqueue, &a3);
	PQueueEnqueue(pqueue, &a35);
	PQueueEnqueue(pqueue, &a2);
	PQueueEnqueue(pqueue, &a4);
	PQueueEnqueue(pqueue, &a1);
	size += 6;
	
	/*	10 23 20 30 35 40	*/ 
	
	
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);	


	PrintError("PQueueErase", __LINE__, *(int *)PQueueErase(pqueue, IsMatch, &a1), a1);
	--size;	
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
	PrintError("PQueueErase or PQueuePeek", __LINE__, *(int *)PQueuePeek(pqueue), a23);	


	PrintError("PQueueErase", __LINE__, *(int *)PQueueErase(pqueue, IsMatch, &a4), a4);
	--size;	
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
	PrintError("PQueueErase or PQueuePeek", __LINE__, *(int *)PQueuePeek(pqueue), a23);	
	

	PrintError("PQueueErase", __LINE__, *(int *)PQueueErase(pqueue, IsMatch, &a23), a23);
	--size;	
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
	PrintError("PQueueErase or PQueuePeek", __LINE__, *(int *)PQueuePeek(pqueue), a2);	


	PrintError("PQueueErase", __LINE__, *(int *)PQueueErase(pqueue, IsMatch, &a2), a2);
	--size;	
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
	PrintError("PQueueErase or PQueuePeek", __LINE__, *(int *)PQueuePeek(pqueue), a3);	


	PrintError("PQueueErase", __LINE__, *(int *)PQueueErase(pqueue, IsMatch, &a3), a3);
	--size;	
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
	PrintError("PQueueErase or PQueuePeek", __LINE__, *(int *)PQueuePeek(pqueue), a35);	


	PrintError("PQueueErase", __LINE__, *(int *)PQueueErase(pqueue, IsMatch, &a35), a35);
	--size;	
	PrintError("PQueueSize", __LINE__, (int)PQueueSize(pqueue), (int)size);
	PrintError("PQueueIsEmpty", __LINE__, (int)PQueueIsEmpty(pqueue), !(int)size);	
	


	PQueueDestroy(pqueue);
	
	if (0 == failure)
	{
		printf("PriorityQueue - %s\n", SUCCESS);
	}
}


int Cmp(const void *rhs, const void *lhs)
{
	assert(rhs);
	assert(lhs);
	
	return (*(int *)rhs/10 - *(int *)lhs/10);
}

int IsMatch(const void *rhs, const void *lhs)
{
	assert(rhs);
	assert(lhs);
	
	return (*(int *)rhs == *(int *)lhs);
}


void PrintError(char *name, int line ,int function_result ,int should_be)
{
	if (function_result != should_be)
	{
		printf("%s - %s - in line %d - function result is: %d and should be: %d\n", name, FAILURE, line, function_result, should_be);
		failure = 1;
	}
}
