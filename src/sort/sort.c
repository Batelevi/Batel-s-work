/*********************************************
 * Developer:      Batel Levi                 *
 * Reviewer:       Kostya                     *
 **********************************************/
#include <stdlib.h> /*	for malloc	*/
#include <assert.h>	/*	for assert	*/
#include <unistd.h>	/*	for ssize_t	*/
#include <string.h>	/*	for memcpy	*/

#include "sort.h" /*	header file	*/

#define DIGITS 10

/*	 utility functions	*/
static void SwapTwoInts(int *n1, int *n2);
static int CountingSortByDigit(int arr[], size_t size, int digit);
static int FindMaxNum(int arr[], size_t size);
static int *Merge(int *arr1, size_t size1, int *arr2, size_t size2);
static int *MyMergeSort(int *arr_to_sort, size_t num_elements);
static void MyQuickSort(char *arr, size_t element_size, ssize_t low, ssize_t high,
						int (*compar)(const void *lhs, const void *rhs));
static size_t Partition(char *arr, size_t element_size, ssize_t low, ssize_t high,
						int (*compar)(const void *lhs, const void *rhs));
static void Swap(char *n1, char *n2, size_t element_size);


void BubbleSort(int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 0;
	int sorted = 0;

	for (i = 0; (i < size - 1) && (1 != sorted); ++i)
	{
		sorted = 1;

		/*	traverse the array and swap two sequential elements
			if the first is bigger than the second	*/
		for (j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				SwapTwoInts(&arr[j], &arr[j + 1]);
				sorted = 0;
			}
		}
	}
}

void SelectionSort(int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 0;
	size_t min_idx = 0;

	for (i = 0; i < size - 1; ++i)
	{
		min_idx = i;

		/*	find the min element from the current element to the end
			and swap it with the current*/
		for (j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[min_idx])
			{
				min_idx = j;
			}
		}

		SwapTwoInts(&arr[i], &arr[min_idx]);
	}
}

void InsertionSort(int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 0;

	for (i = 1; i < size; ++i)
	{
		j = i;

		/*	keep swapping the current element with the one before
			as lons as the current is smaller	*/
		while ((arr[j] < arr[j - 1]) && (j > 0))
		{
			SwapTwoInts(&arr[j], &arr[j - 1]);
			--j;
		}
	}
}

int CountingSort(int arr[], size_t size)
{
	size_t *count = NULL;
	size_t range = 0;
	size_t sorted_i = 0;
	size_t sorted_count = 0;
	size_t i = 0;

	range = (size_t)FindMaxNum(arr, size);

	count = (size_t *)calloc(range + 1, sizeof(size_t));

	if (NULL == count)
	{
		return (1);
	}

	/*	count appearances of each element
		and store it in count	*/
	for (i = 0; i < size; ++i)
	{
		++count[arr[i]];
	}

	for (i = 0; i <= range; ++i)
	{
		if (i > 0)
		{
			sorted_i = count[i - 1];
		}

		sorted_count = count[i];

		while (sorted_count)
		{
			arr[sorted_i] = i;
			++sorted_i;
			--sorted_count;
		}

		if (i > 0)
		{
			count[i] += count[i - 1];
		}
	}

	free(count);

	return (0);
}

int RadixSort(int arr[], size_t size)
{
	size_t i = 1;
	size_t max_num = 0;

	max_num = (size_t)FindMaxNum(arr, size);

	while (i <= max_num)
	{
		if (CountingSortByDigit(arr, size, i))
		{
			return (1);
		}

		i *= 10;
	}

	return (0);
}

static void SwapTwoInts(int *n1, int *n2)
{
	int temp = 0;

	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

static int CountingSortByDigit(int arr[], size_t size, int digit)
{
	size_t count[DIGITS] = {0};
	size_t sorted_i = 0;
	size_t i = 0;
	int *output = (int *)malloc(sizeof(int) * size);

	if (NULL == output)
	{
		return (1);
	}

	for (i = 0; i < size; ++i)
	{
		++count[(arr[i] / digit) % 10];
	}

	for (i = 1; i < DIGITS; ++i)
	{
		count[i] += count[i - 1];
	}

	for (i = DIGITS - 1; i > 0; --i)
	{
		count[i] = count[i - 1];
	}

	count[0] = 0;

	for (i = 0; i < size; ++i)
	{
		sorted_i = count[(arr[i] / digit) % 10];
		output[sorted_i] = arr[i];
		++count[(arr[i] / digit) % 10];
	}

	for (i = 0; i < size; ++i)
	{
		arr[i] = output[i];
	}

	free(output);

	return (0);
}

static int FindMaxNum(int arr[], size_t size)
{
	size_t i = 0;
	int max = 0;

	for (i = 0; i < size; ++i)
	{
		if (max < arr[i])
		{
			max = arr[i];
		}
	}

	return (max);
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	assert(arr_to_sort);

	if (!MyMergeSort(arr_to_sort, num_elements))
	{
		return (1);
	}

	return (0);
}

static int *MyMergeSort(int *arr_to_sort, size_t num_elements)
{
	int *arr1 = NULL;
	int *arr2 = NULL;
	size_t size1 = 0;
	size_t size2 = 0;

	assert(arr_to_sort);

	if (1 == num_elements)
	{
		return (arr_to_sort);
	}

	arr1 = arr_to_sort;
	size1 = num_elements / 2;
	arr2 = arr1 + size1;
	size2 = num_elements - size1;

	arr1 = MyMergeSort(arr1, size1);
	arr2 = MyMergeSort(arr2, size2);

	return Merge(arr1, size1, arr2, size2);
}

static int *Merge(int *arr1, size_t size1, int *arr2, size_t size2)
{
	size_t i = 0;
	size_t j = 0;
	size_t res = 0;
	int *temp = (int *)malloc(sizeof(int) * (size1 + size2));

	if (NULL == temp)
	{
		return NULL;
	}

	while (i < size1 && j < size2)
	{
		res = arr1[i] < arr2[j];
		temp[i + j] = arr1[i] * res + arr2[j] * !res;
		i += res;
		j += !res;
	}

	while (i < size1 || j < size2)
	{
		temp[i + j] = arr1[i] * (i < size1) + arr2[j] * (j < size2);
		i += i < size1;
		j += j < size2;
	}

	memcpy(arr1, temp, (size1 + size2) * sizeof(int));

	free(temp);

	return (arr1);
}

void QuickSort(void *base, size_t nmemb, size_t size,
			   int (*compar)(const void *lhs, const void *rhs))
{
	assert(base);
	assert(compar);

	MyQuickSort(base, size, 0, nmemb - 1, compar);
}

static void MyQuickSort(char *arr, size_t element_size, ssize_t low, ssize_t high,
						int (*compar)(const void *lhs, const void *rhs))
{
	size_t pivot_i = 0;

	assert(arr);
	assert(compar);

	if (low < high)
	{
		pivot_i = Partition(arr, element_size, low, high, compar);

		MyQuickSort(arr, element_size, low, pivot_i - 1, compar);
		MyQuickSort(arr, element_size, pivot_i + 1, high, compar);
	}
}

static size_t Partition(char *arr, size_t element_size, ssize_t low, ssize_t high, int (*compar)(const void *lhs, const void *rhs))
{
	size_t pivot = high * element_size;
	ssize_t i = low;
	ssize_t j = low;

	assert(arr);
	assert(compar);

	for (j = low; j < high; ++j)
	{
		if (compar(&arr[j * element_size] ,&arr[pivot]) < 0)
		{
			Swap(&arr[i * element_size], &arr[j * element_size], element_size);
			++i;
		}
	}

	Swap(&arr[i * element_size], &arr[pivot], element_size);

	return (i);
}

static void Swap(char *n1, char *n2, size_t element_size)
{
	char temp = '\0';

	assert(n1);
	assert(n2);

	if (element_size)
	{
		temp = *n1;
		*n1 = *n2;
		*n2 = temp;

		Swap(n1 + 1, n2 + 1, element_size - 1);
	}
}