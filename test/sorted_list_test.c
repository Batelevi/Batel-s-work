#include <stdio.h>
#include <assert.h>	/*	 for assert	*/

#include "sorted_list.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"


void TestSortedList();

void PrintList(sorted_list_t *sorted_list);

int CmpInts(const void *lhs, const void *rhs); 

int FindDividedBy(const void *lhs, const void *rhs);	/*	is match function	*/

int Add(void *lhs, void *rhs);	/*	action function	*/

int main ()
{
	TestSortedList();
	return (0);
}


void TestSortedList()
{
	sorted_list_t *sorted_list = SortedListCreate(&CmpInts);
	sorted_list_t *sorted_list2 = SortedListCreate(&CmpInts);
	sorted_list_iter_t iterator = {0};
	int a1 = 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	int a5 = 5;
	int b1 = 1;
	int b3 = 3;
	int b7 = 7;
	int b8 = 8;
	int data = 0;
	size_t size = 0;
	int failure = 0;
	
	if (NULL == sorted_list)
	{
		printf("SortedListCreate - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	if (SortedListSize(sorted_list) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}

	if (!SortedListIsEmpty(sorted_list))
	{
		printf("SortedListIsEmpty - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;	
	}	

	SortedListInsert(sorted_list, &a2);

	++size;
	
	if (a2 != *(int *)SortedListGetData(SortedListBegin(sorted_list)))
	{
		printf("SortedListInsert - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(SortedListBegin(sorted_list)), a2);
		failure = 1;	
	}
	
	if (SortedListSize(sorted_list) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}
	
	if (SortedListIsEmpty(sorted_list))
	{
		printf("SortedListIsEmpty - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;	
	}	

	SortedListInsert(sorted_list, &a1);

	++size;
	
	if (a1 != *(int *)SortedListGetData(SortedListBegin(sorted_list)))
	{
		printf("SortedListInsert - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(SortedListBegin(sorted_list)), a1);
		failure = 1;	
	}
	
	if (SortedListSize(sorted_list) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}
	
	if (SortedListIsEmpty(sorted_list))
	{
		printf("SortedListIsEmpty - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;	
	}
	
	iterator = SortedListPrevious(SortedListEnd(sorted_list));
		
	if (a2 != *(int *)SortedListGetData(iterator))
	{
		printf("SortedListInsert or SortedListPrevious - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), a2);
		failure = 1;	
	}

	SortedListInsert(sorted_list, &a4);
	++size;
	SortedListInsert(sorted_list, &a3);
	++size;

	if (SortedListSize(sorted_list) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}	

	data = *(int *)SortedListPopFront(sorted_list);
	--size;
	
	if (data != a1)
	{
		printf("SortedListPopFront - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, data, a1);
		failure = 1;		
	}

	data = *(int *)SortedListPopBack(sorted_list);
	--size;
	
	if (data != a4)
	{
		printf("SortedListPopBack - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, data, a4);
		failure = 1;		
	}	

	if (SortedListSize(sorted_list) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}
	
	
	SortedListRemove(SortedListPrevious(SortedListEnd(sorted_list)));
	--size;
	
	data = *(int *)SortedListPopBack(sorted_list);
	--size;
	
	if (data != a2)
	{
		printf("SortedListRemove - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, data, a2);
		failure = 1;		
	}	

	if (SortedListSize(sorted_list) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}	
	
	SortedListInsert(sorted_list, &a4);
	++size;
	SortedListInsert(sorted_list, &a1);
	++size;	
	SortedListInsert(sorted_list, &a2);
	++size;
	SortedListInsert(sorted_list, &a5);
	++size;
	SortedListInsert(sorted_list, &a3);
	++size;	

	data = a5;
	
	iterator = SortedListFind(sorted_list, SortedListBegin(sorted_list), SortedListEnd(sorted_list), &a5);

	if (data != *(int *)SortedListGetData(iterator))
	{
		printf("SortedListFind - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), data);
		failure = 1;	
	}	

	iterator = SortedListFindIf(SortedListBegin(sorted_list), SortedListEnd(sorted_list), &FindDividedBy, &a2);
	
	data = a2;

	if (data != *(int *)SortedListGetData(iterator))
	{
		printf("SortedListFindIf - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), data);
		failure = 1;	
	}	

	iterator = SortedListFindIf(SortedListNext(iterator), SortedListEnd(sorted_list), &FindDividedBy, &a2);
	
	data = a4;

	if (data != *(int *)SortedListGetData(iterator))
	{
		printf("SortedListFindIf - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), data);
		failure = 1;	
	}

	data = 1;

	SortedListForEach(SortedListBegin(sorted_list), SortedListEnd(sorted_list), &Add, &data);
	
	data = 6;
	iterator = SortedListPrevious(SortedListEnd(sorted_list));

	if (data != *(int *)SortedListGetData(iterator))
	{
		printf("SortedListForEach - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), data);
		failure = 1;	
	}

	if (SortedListSize(sorted_list) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}
		
	
	
	SortedListInsert(sorted_list2, &b3);
	SortedListInsert(sorted_list2, &b1);
	SortedListInsert(sorted_list2, &b7);
	SortedListInsert(sorted_list2, &b8);	
		
	SortedListMerge(sorted_list, sorted_list2);
	size += 4;

	if (SortedListSize(sorted_list) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}

	if (!SortedListIsEmpty(sorted_list2))
	{
		printf("SortedListIsEmpty - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;	
	}	

	iterator = SortedListPrevious(SortedListEnd(sorted_list));

	if (*(int *)SortedListPopBack(sorted_list) != b8)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), b8);
		failure = 1;			
	}

	if (*(int *)SortedListPopBack(sorted_list) != b7)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), b7);
		failure = 1;			
	}

	if (*(int *)SortedListPopBack(sorted_list) != a5)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), a5);
		failure = 1;			
	}

	if (*(int *)SortedListPopBack(sorted_list) != a4)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), a4);
		failure = 1;			
	}

	if (*(int *)SortedListPopBack(sorted_list) != a3)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), a3);
		failure = 1;			
	}

	if (*(int *)SortedListPopBack(sorted_list) != b3)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), b3);
		failure = 1;			
	}

	if (*(int *)SortedListPopBack(sorted_list) != a2)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), a2);
		failure = 1;			
	}

	if (*(int *)SortedListPopBack(sorted_list) != a1)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), a1);
		failure = 1;			
	}

	if (*(int *)SortedListPopBack(sorted_list) != b1)
	{
		printf("SortedListMerge - %s - in line %d - function result is: %d and should be: %d\n", FAILURE, __LINE__, *(int *)SortedListGetData(iterator), b1);
		failure = 1;			
	}

	size = 0;
	
	if (!SortedListIsEmpty(sorted_list))
	{
		printf("SortedListIsEmpty - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;	
	}	

	SortedListInsert(sorted_list, &a2);
	SortedListInsert(sorted_list, &a3);
	SortedListInsert(sorted_list, &a1);
	
	
	SortedListInsert(sorted_list2, &b3);
	SortedListInsert(sorted_list2, &b1);
	SortedListInsert(sorted_list2, &b7);	
	SortedListInsert(sorted_list2, &b8);	
	
	SortedListMerge(sorted_list2, sorted_list);
	size = 7;

	if (SortedListSize(sorted_list2) != size)
	{
		printf("SortedListSize - %s - in line %d - function result is: %lu and should be: %lu\n", FAILURE, __LINE__, SortedListSize(sorted_list), size);
		failure = 1;	
	}
/*
	PrintList(sorted_list);
	printf("\n\n");
	PrintList(sorted_list2);
*/
	SortedListDestroy(sorted_list);
	SortedListDestroy(sorted_list2);	
	
	if (0 == failure)
	{
		printf("Sorted List - %s\n", SUCCESS);
	}
}

int CmpInts(const void *lhs, const void *rhs)
{
	return (*(int *)lhs - *(int *)rhs);
}

void PrintList(sorted_list_t *sorted_list)
{
	sorted_list_iter_t iter = {0};
	
	assert(sorted_list);
	
	iter = SortedListBegin(sorted_list);
	
	while (!SortedListIsSameIter(iter, SortedListEnd(sorted_list)))
	{
		printf("%d\n", *(int *)SortedListGetData(iter));
		
		iter = SortedListNext(iter);
	}
	
	printf("\n");
}

int FindDividedBy(const void *lhs, const void *rhs)
{
	assert(lhs);
	assert(rhs);
	
	return (*(int *)lhs % *(int *)rhs == 0);
}

int Add(void *lhs, void *rhs)
{
	*(int *)lhs += *(int *)rhs;
	
	return (0);
}
