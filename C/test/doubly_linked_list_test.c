#include <stdio.h>
#include <assert.h>	/*	for assert	*/


#include "doubly_linked_list.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

#define UNUSED(x) (void)(x)

void TestDoublyLinkedList();
int PrintList(void *data, void *param);
int IsIntsMatch(const void *lhs, const void *rhs);

int main ()
{
	TestDoublyLinkedList();
	
	return (0);
}

void TestDoublyLinkedList()
{
	dlist_t *dlist = DListCreate();
	dlist_t *dlist2 = DListCreate();
	int failure = 0;
	int a1 = 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	int a5 = 5;
	size_t size = 0;
	dlist_iterator_t iterator = 0;
	
	if (NULL == dlist)
	{
		printf("DListCreate - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	if (!DListIsEmpty(dlist))
	{
		printf("DListIsEmpty - %s - in line %d - function result is: %d and should be: TRUE\n", FAILURE, __LINE__, DListIsEmpty(dlist));
		failure = 1;		
	}
	
	if (DListSize(dlist) != size)
	{
		printf("DListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, DListSize(dlist), size);
		failure = 1;
	}
	
	iterator = DListEnd(dlist);

	iterator = DListInsert(&a1, iterator);
	
	++size;

	if (*(int *)DListGetData(iterator) != a1)
	{
		printf("DListInsert - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(iterator), a1);
		failure = 1;	
	}
	
	if (DListSize(dlist) != size)
	{
		printf("DListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, DListSize(dlist), size);
		failure = 1;
	}

	iterator = DListEnd(dlist);
		
	DListInsert(&a2, iterator);
	DListInsert(&a3, iterator);
	DListInsert(&a4, iterator);
	
	size += 3;
	
	if (DListSize(dlist) != size)
	{
		printf("DListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, DListSize(dlist), size);
		failure = 1;
	}

	
	if (*(int *)DListGetData(DListBegin(dlist)) != a1)
	{
		printf("DListBegin - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(DListBegin(dlist)), a1);
		failure = 1;	
	}
	
	DListPushFront(dlist, &a5);

	++size;
	
	if (*(int *)DListGetData(DListBegin(dlist)) != a5)
	{
		printf("DListBegin - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(DListBegin(dlist)), a5);
		failure = 1;	
	}	
	
	if (*(int *)DListPopFront(dlist) != a5)
	{
		printf("DListPopFront - %s - in line %d - function result should be: %d\n", FAILURE, __LINE__, a5);
		failure = 1;	
	}
	
	--size;
	
	iterator = DListPushBack(dlist, &a5);

	++size;
	
	if (*(int *)DListGetData(iterator) != a5)
	{
		printf("DListPushBack - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(iterator), a5);
		failure = 1;	
	}	
	
	iterator = DListRemove(iterator);

	--size;
	
	if (iterator != DListEnd(dlist))
	{
		printf("DListRemove - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;	
	}

	if (DListSize(dlist) != size)
	{
		printf("DListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, DListSize(dlist), size);
		failure = 1;
	}
	
	if (*(int *)DListPopBack(dlist) != a4)
	{
		printf("DListPopBack - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;			
	}
	
	--size;
	
	iterator = DListBegin(dlist);
	
	if (*(int *)DListGetData(DListNext(iterator)) != a2)
	{
		printf("DListNext - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(DListNext(iterator)), a2);
		failure = 1;		
	}
	
	iterator = DListEnd(dlist);
	iterator = DListPrev(iterator);

	if (*(int *)DListGetData(iterator) != a3)
	{
		printf("DListPrev - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(iterator), a3);
		failure = 1;		
	}
	
	DListSetData(iterator, &a2);

	if (*(int *)DListGetData(iterator) != a2)
	{
		printf("DListPrev - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(iterator), a2);
		failure = 1;		
	}
	
	DListSetData(iterator, &a3);	

	iterator = DListFindData(DListBegin(dlist), DListEnd(dlist), &IsIntsMatch, &a4);
	
	if (!DListIsSameIter(iterator, DListEnd(dlist)))
	{
		printf("DListFindData - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;	
	}
	
	a4 = a2;

	iterator = DListFindData(DListBegin(dlist), DListEnd(dlist), &IsIntsMatch, &a4);
	
	if (*(int *)DListGetData(iterator) != a2)
	{
		printf("DListFindData - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(iterator), a2);
		failure = 1;		
	}

	DListInsert(&a4, DListEnd(dlist));
	
	++size;

	DListMultifind(DListBegin(dlist), DListEnd(dlist), &IsIntsMatch, &a4, dlist2);
	
	if (DListSize(dlist2) != 2)
	{
		printf("DListMultifind - %s - in line %d \n", FAILURE, __LINE__);
		failure = 1;	
	}

/*
	DListForEach(DListBegin(dlist2), DListEnd(dlist2), &PrintList, &a1);	
	printf("\n");
	DListForEach(DListBegin(dlist), DListEnd(dlist), &PrintList, &a1);
	printf("\n");
*/
	DListSplice(DListBegin(dlist2), DListEnd(dlist2), DListBegin(dlist));
	
	size += 2;
/*
	DListForEach(DListBegin(dlist), DListEnd(dlist), &PrintList, &a1);
	printf("\n");
*/	
	if (*(int *)DListGetData(DListBegin(dlist)) != a2)
	{
		printf("DListSplice - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)DListGetData(DListBegin(dlist)), a2);
		failure = 1;		
	}

	if (DListSize(dlist) != size)
	{
		printf("DListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, DListSize(dlist), size);
		failure = 1;
	}
/*
	DListForEach(DListBegin(dlist), DListEnd(dlist), &PrintList, &a1);
	printf("\n");	
*/	
	DListDestroy(dlist);

	DListDestroy(dlist2);

/*	printf("line %d\n", __LINE__);*/
		
	if (0 == failure)
	{
		printf("Doubly Linked List - %s\n", SUCCESS);
	}
}

int PrintList(void *data, void *param)
{
	assert(data);
	UNUSED(param);
	
	printf("%d\n", *(int *)data);
	
	return (0);
}

int IsIntsMatch(const void *lhs, const void *rhs)
{
	assert(lhs);
	assert(rhs);
	
	return (*(int *)lhs == *(int *)rhs);
}
