#include <stdio.h>

#include "bst.h"	/*	header file	*/

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int failure = 0;

void TestBst();
void PrintError(char *name, int line ,long int function_result ,long int should_be);

int CmprFunc(const void *data, const void *param);


int main ()
{
	TestBst();
	
	return (0);
}


void TestBst()
{
	bst_t *bst = BSTCreate(CmprFunc);
	bst_iterator_t iter = {0};
	bst_iterator_t iter2 = {0};
	int a10 = 10;
	int a2 = 2;
	int a16 = 16;
	int a1 = 1;
	int a4 = 4;
	int a18 = 18;
	int a14 = 14;

	if (NULL == bst)
	{
		printf("BSTCreate - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;		
	}

	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 1);

	iter = BSTEnd(bst);

	PrintError("BSTEnd or IsSameIter", __LINE__, BSTIsSameIter(iter, BSTEnd(bst)), 1);

	iter = BSTInsert(bst, &a10);

	if (NULL == iter)
	{
		printf("BSTCreate - %s - in line %d\n", FAILURE, __LINE__);
		failure = 1;		
	}

	PrintError("BSTInsert or BSTGetData", __LINE__, *(int *)BSTGetData(iter), a10);

	iter2 = BSTInsert(bst, &a2);

	PrintError("BSTInsert or BSTGetData", __LINE__, *(int *)BSTGetData(iter2), a2);

	iter = BSTPrev(iter);

	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a2);

	iter = BSTNext(iter);

	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a10);

	iter = BSTBegin(bst);

	PrintError("BSTBegin", __LINE__, *(int *)BSTGetData(iter), a2);

	BSTInsert(bst, &a16);
	BSTInsert(bst, &a1);
	BSTInsert(bst, &a4);
	BSTInsert(bst, &a18);
	BSTInsert(bst, &a14);

	iter = BSTBegin(bst);

	PrintError("BSTBegin", __LINE__, *(int *)BSTGetData(iter), a1);	
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a2);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a4);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a10);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a14);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a16);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a18);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a16);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a14);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a10);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a4);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a2);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a1);


	iter = BSTFind(bst, &a14);
	PrintError("BSTFind", __LINE__, *(int *)BSTGetData(iter), a14);
	PrintError("BSTSize", __LINE__, (int)BSTSize(bst), 7);

	/*	remove tests	*/

	iter = BSTFind(bst, &a2);	
	iter = BSTRemove(iter);
	PrintError("BSTRemove", __LINE__, *(int *)BSTGetData(iter), a4);
	PrintError("BSTSizeor BSTRemove", __LINE__, (int)BSTSize(bst), 6);
	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 0);

	iter = BSTFind(bst, &a4);	
	iter = BSTRemove(iter);
	PrintError("BSTRemove", __LINE__, *(int *)BSTGetData(iter), a10);
	PrintError("BSTSizeor BSTRemove", __LINE__, (int)BSTSize(bst), 5);
	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 0);

	iter = BSTFind(bst, &a16);
	iter = BSTRemove(iter);
	PrintError("BSTRemove", __LINE__, *(int *)BSTGetData(iter), a18);
	PrintError("BSTSizeor BSTRemove", __LINE__, (int)BSTSize(bst), 4);
	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 0);

	iter = BSTFind(bst, &a14);
	iter = BSTRemove(iter);
	PrintError("BSTRemove", __LINE__, *(int *)BSTGetData(iter), a18);
	PrintError("BSTSizeor BSTRemove", __LINE__, (int)BSTSize(bst), 3);
	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 0);

	iter = BSTFind(bst, &a18);
	iter = BSTRemove(iter);
	PrintError("BSTRemove", __LINE__, BSTIsSameIter(iter, BSTEnd(bst)), 1);
	PrintError("BSTSizeor BSTRemove", __LINE__, (int)BSTSize(bst), 2);
	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 0);

	iter = BSTFind(bst, &a1);
	iter = BSTRemove(iter);
	PrintError("BSTRemove", __LINE__, *(int *)BSTGetData(iter), a10);
	PrintError("BSTSizeor BSTRemove", __LINE__, (int)BSTSize(bst), 1);
	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 0);

	iter = BSTFind(bst, &a10);
	iter = BSTRemove(iter);
	PrintError("BSTRemove", __LINE__, BSTIsSameIter(iter, BSTEnd(bst)), 1);
	PrintError("BSTSizeor BSTRemove", __LINE__, (int)BSTSize(bst), 0);
	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 1);


	BSTInsert(bst, &a10);
	BSTInsert(bst, &a16);
	BSTInsert(bst, &a1);
	BSTInsert(bst, &a4);
	BSTInsert(bst, &a18);
	BSTInsert(bst, &a14);
	BSTInsert(bst, &a2);

	iter = BSTFind(bst, &a10);
	iter = BSTRemove(iter);

	iter = BSTFind(bst, &a18);
	iter = BSTRemove(iter);

	iter = BSTFind(bst, &a14);
	iter = BSTRemove(iter);

	BSTInsert(bst, &a18);
	BSTInsert(bst, &a14);
	BSTInsert(bst, &a10);


	iter = BSTBegin(bst);
	PrintError("BSTBegin", __LINE__, *(int *)BSTGetData(iter), a1);	
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a2);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a4);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a10);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a14);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a16);
	iter = BSTNext(iter);
	PrintError("BSTNext", __LINE__, *(int *)BSTGetData(iter), a18);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a16);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a14);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a10);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a4);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a2);
	iter = BSTPrev(iter);
	PrintError("BSTPrev", __LINE__, *(int *)BSTGetData(iter), a1);

	iter = BSTBegin(bst);
	PrintError("BSTBegin", __LINE__, *(int *)BSTGetData(iter), a1);	
	PrintError("BSTSizeor BSTRemove", __LINE__, (int)BSTSize(bst), 7);
	PrintError("BSTIsEmpty", __LINE__, BSTIsEmpty(bst), 0);

	BSTDestroy(bst);

/*	PrintError("", __LINE__, ___, ___); */
	
	
	if (0 == failure)
	{
		printf("BST - %s\n", SUCCESS);
	}
}


void PrintError(char *name, int line ,long int function_result ,long int should_be)
{
	if (function_result != should_be)
	{
		printf("%s - %s - in line %d - function result is: %ld and should be: %ld\n", name, FAILURE, line, function_result, should_be);
		failure = 1;
	}
}

int CmprFunc(const void *data, const void *param)
{
	return (*(int *)data - *(int *)param);
}