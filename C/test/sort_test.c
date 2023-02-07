#include <stdio.h>
#include <stdlib.h>	/*	for rand	*/
#include <time.h>	/*	for time	*/
#include <assert.h>	/*	for assert	*/

#include "sort.h"	/*	header file	*/

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int failure = 0;

void TestBubbleSort();
void TestSelectionSort();
void TestInsertionSort();
void TestCountingSort();
void TestRadixSort();
void TestMergeSort();
void TestQuickSort();

void PrintError(char *name, int line ,long int function_result ,long int should_be);
void PrintArr(int arr[], size_t size);
int Compar(const void *n1, const void *n2);	/*	for qsort	*/
int IsSortedArr(int *arr, size_t size);


int main ()
{
	TestBubbleSort();
	printf("\n");
	TestSelectionSort();
	printf("\n");
	TestInsertionSort();
	printf("\n");
	TestCountingSort();
	printf("\n");
	TestRadixSort();
	printf("\n");
	TestMergeSort();
	printf("\n");
	TestQuickSort();

	return (0);
}


void TestBubbleSort()
{
	int arr[5000] = {0};
	int res[5000] = {0};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	size_t i = 0;
	clock_t start = 0;
	clock_t end = 0;
	


	/*---------------Test 1---------------*/	
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 5000;
		res[i] = arr[i];
	}

	start = clock();
	BubbleSort(arr, size);
	end = clock();
	
	printf("Complexity Time - test 1:\n");
	printf("BubbleSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	for (i = 0; i < size; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}
	
	
	if (1 == failure)
	{
		printf("BubbleSort test 1 - %s\n", FAILURE);
		printf("Function result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("qsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}


	/*---------------Test 2---------------*/	
	failure = 0;
	srand(time(NULL));
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 5000;
		res[i] = arr[i];
	}

	start = clock();
	BubbleSort(arr, size);
	end = clock();
	
	printf("\nComplexity Time - test 2:\n");
	printf("BubbleSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	
	for (i = 0; i < 20; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}

	if (1 == failure)
	{
		printf("BubbleSort test 2 - %s\n", FAILURE);
		printf("\nFunction result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("\nqsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}



/*	PrintError("", __LINE__, ___, ___);*/
	
	
	
	if (0 == failure)
	{
		printf("\nBubbleSort - %s\n", SUCCESS);
	}
}


void TestSelectionSort()
{
	int arr[5000] = {0};
	int res[5000] = {0};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	size_t i = 0;
	clock_t start = 0;
	clock_t end = 0;
	

	/*---------------Test 1---------------*/	
	failure = 0;
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 5000;
		res[i] = arr[i];
	}

	start = clock();
	SelectionSort(arr, size);
	end = clock();
	
	printf("Complexity Time - test 1:\n");
	printf("SelectionSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	for (i = 0; i < size; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}
	
	
	if (1 == failure)
	{
		printf("SelectionSort test 1 - %s\n", FAILURE);
		printf("Function result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("qsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}


	/*---------------Test 2---------------*/	
	failure = 0;
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = (time(NULL) + rand()) % 5000;
		res[i] = arr[i];
	}

	start = clock();
	SelectionSort(arr, size);
	end = clock();
	
	printf("\nComplexity Time - test 2:\n");
	printf("SelectionSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	
	for (i = 0; i < 20; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}

	if (1 == failure)
	{
		printf("SelectionSort test 2 - %s\n", FAILURE);
		printf("\nFunction result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("\nqsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}



/*	PrintError("", __LINE__, ___, ___);*/
	
	
	
	if (0 == failure)
	{
		printf("\nSelectionSort - %s\n", SUCCESS);
	}
}


void TestInsertionSort()
{
	int arr[5000] = {0};
	int res[5000] = {0};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	size_t i = 0;
	clock_t start = 0;
	clock_t end = 0;
	


	/*---------------Test 1---------------*/	
	failure = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 5000;
		res[i] = arr[i];
	}

	start = clock();
	InsertionSort(arr, size);
	end = clock();
	
	printf("Complexity Time - test 1:\n");
	printf("InsertionSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	for (i = 0; i < size; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}
	
	
	if (1 == failure)
	{
		printf("InsertionSort test 1 - %s\n", FAILURE);
		printf("Function result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("qsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}


	/*---------------Test 2---------------*/	
	failure = 0;
	srand(time(NULL));
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 5000;
		res[i] = arr[i];
	}

	start = clock();
	InsertionSort(arr, size);
	end = clock();
	
	printf("\nComplexity Time - test 2:\n");
	printf("InsertionSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	
	for (i = 0; i < 20; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}

	if (1 == failure)
	{
		printf("SelectionSort test 2 - %s\n", FAILURE);
		printf("\nFunction result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("\nqsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}



/*	PrintError("", __LINE__, ___, ___);*/
	
	
	
	if (0 == failure)
	{
		printf("\nInsertionSort - %s\n", SUCCESS);
	}
}


void TestCountingSort()
{
	int arr[5000] = {0};
	int res[5000] = {0};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	size_t i = 0;
	clock_t start = 0;
	clock_t end = 0;
	


	/*---------------Test 1---------------*/	
	failure = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 100 + 1;
		res[i] = arr[i];
	}

	start = clock();
	CountingSort(arr, size);
	end = clock();
	
	printf("Complexity Time - test 1:\n");
	printf("CountingSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	for (i = 0; i < size; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}
	
	
	if (1 == failure)
	{
		printf("CountingSort test 1 - %s\n", FAILURE);
		printf("Function result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("qsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}


	/*---------------Test 2---------------*/	
	failure = 0;
	srand(time(NULL));
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 100 + 1;
		res[i] = arr[i];
	}

	start = clock();
	CountingSort(arr, size);
	end = clock();
	
	printf("\nComplexity Time - test 2:\n");
	printf("CountingSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	
	for (i = 0; i < 20; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}

	if (1 == failure)
	{
		printf("CountingSort test 2 - %s\n", FAILURE);
		printf("\nFunction result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("\nqsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}



/*	PrintError("", __LINE__, ___, ___);*/
	
	
	
	if (0 == failure)
	{
		printf("\nCountingSort - %s\n", SUCCESS);
	}
}


void TestRadixSort()
{
	int arr[5000] = {0};
	int res[5000] = {0};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	size_t i = 0;
	clock_t start = 0;
	clock_t end = 0;
	


	/*---------------Test 1---------------*/	
	failure = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 10000000;
		res[i] = arr[i];
	}

	start = clock();
	RadixSort(arr, size);
	end = clock();
	
	printf("Complexity Time - test 1:\n");
	printf("RadixSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	for (i = 0; i < size; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}
	
	
	if (1 == failure)
	{
		printf("RadixSort test 1 - %s\n", FAILURE);
		printf("Function result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("qsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}


	/*---------------Test 2---------------*/	
	failure = 0;
	srand(time(NULL));
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 10000000;
		res[i] = arr[i];
	}

	start = clock();
	RadixSort(arr, size);
	end = clock();
	
	printf("\nComplexity Time - test 2:\n");
	printf("RadixSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();	
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
		
	
	for (i = 0; i < 20; ++i)
	{
		if (arr[i] != res[i])
		{
			failure = 1;
		}
	}

	if (1 == failure)
	{
		printf("RadixSort test 2 - %s\n", FAILURE);
		printf("\nFunction result array (the first 20 only):\n\n");
		PrintArr(arr, 20);
		printf("\nqsort function result array(the first 20 only):\n\n");
		PrintArr(res, 20);
	}

/*	PrintError("", __LINE__, ___, ___);*/
	
	if (0 == failure)
	{
		printf("\nRadixSort - %s\n", SUCCESS);
	}
}

void TestMergeSort()
{
	/*int arr[] = {25, 150, 0, 31, 12, 544};*/
	int arr[5000] = {0};
	int res[5000] = {0};
	/*int arr1[] = {10, 5, -60, 45, 30};*/
	size_t size = sizeof(arr) / sizeof(arr[0]);
	/*size_t size1 = sizeof(arr1) / sizeof(arr1[0]);*/
	size_t i = 0;
	clock_t start = 0;
	clock_t end = 0;
	
	failure = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 10000000;
		res[i] = arr[i];
	}

	start = clock();
	MergeSort(arr, size);
	end = clock();

	printf("MergeSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);
	

	/*MergeSort(arr, size);
	MergeSort(arr1, size1);*/


	PrintError("MergeSort", __LINE__, IsSortedArr(arr, size), 1);
	/*PrintError("MergeSort", __LINE__, IsSortedArr(arr1, size1), 1);*/

	if (0 == failure)
	{
		printf("\nMergeSort - %s\n", SUCCESS);
	}
	else
	{
		PrintArr(arr, size);
		/*PrintArr(arr1, size1);*/
	}
}

void TestQuickSort()
{
	/*int arr1[10] = {2, 5, 10, 6, 8, 9, 4, 3, 1, 0};*/
	int arr[5000] = {0};
	int res[5000] = {0};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
	clock_t start = 0;
	clock_t end = 0;

	failure = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = rand() % 10000000;
		res[i] = arr[i];
	}

	start = clock();
	QuickSort(arr, size, sizeof(int), Compar);
	end = clock();

	printf("QuickSort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);

	start = clock();
	qsort(res, size, sizeof(int), Compar);
	end = clock();

	printf("qsort function time is (in ms): %.10f\n", ((double)end - (double)start) / (double)CLOCKS_PER_SEC * 1000);


	PrintError("QuickSort", __LINE__, IsSortedArr(arr, size), 1);

	/*PrintArr(arr, size);*/

	if (0 == failure)
	{
		printf("\nQuickSort - %s\n", SUCCESS);
	}
	else
	{
		PrintArr(arr, size);
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

void PrintArr(int arr[], size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
	
	printf("\n");
}

int Compar(const void *n1, const void *n2)
{
	assert(n1);
	assert(n2);

	return ((*(int *)n1 > *(int *)n2) - (*(int *)n1 < *(int *)n2));
}


int IsSortedArr(int *arr, size_t size)
{
	while (size - 1)
	{
		if (*arr > *(arr + 1))
		{
			return (0);
		}
		--size;
		++arr;
	}

	return (1);
}