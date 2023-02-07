/*********************************************
* Developer:      Batel Levi                 *
* Reviewer:       Kostya                     *
* Version:        1.0                        *
* Description:    API for sort.c             *
**********************************************/
#ifndef __OL134_SORT_H__
#define __OL134_SORT_H__


#include <stddef.h>	/*	for size_t	*/

/*------------------------------------------------------------------------*/

/* BubbleSort:

	Time Complexity:	
					O(n^2)
*/
void BubbleSort(int arr[], size_t size);

/*------------------------------------------------------------------------*/

/* SelectionSort:

	Time Complexity:	
					O(n^2)
*/
void SelectionSort(int arr[], size_t size);

/*------------------------------------------------------------------------*/

/* InsertionSort:

	Time Complexity:	
					O(n^2)
*/
void InsertionSort(int arr[], size_t size);

/*------------------------------------------------------------------------*/

/* CountingSort:

	return:
		success: 0
		failure: 1
	
	Time Complexity:	
					O(n + k) where k is the range of nums in the array	*/
int CountingSort(int arr[], size_t size);

/*------------------------------------------------------------------------*/

/* RadixSort:

	return:
		success: 0
		failure: 1

	Time Complexity:	
					O(n * k) where k is the max num of digits	*/
int RadixSort(int arr[], size_t size);

/*------------------------------------------------------------------------*/

/* MergeSort:

	return:
		success: 0
		failure: 1

	Time Complexity:	
					O(n log n)
	Space Complexity:
					O(n)	*/
int MergeSort(int *arr_to_sort, size_t num_elements);

/*------------------------------------------------------------------------*/

/* QuickSort:

	Time Complexity:	
					O(n log n)	*/
void QuickSort(void *base, size_t nmemb, size_t size,
			   int (*compar)(const void *lhs, const void *rhs));
/*------------------------------------------------------------------------*/


#endif /* __OL134_SORT_H__*/