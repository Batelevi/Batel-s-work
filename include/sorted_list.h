/*********************************************
* Developer:      Batel Levi                 *
* Reviewer:       --                         *
* Version:        2.0                        *
* Description: API for sorted_linked_list.c  *
**********************************************/
#ifndef __OL134_SORTED_LINKED_LIST_H__
#define __OL134_SORTED_LINKED_LIST_H__

#include <stddef.h>	/*	for size_t	*/

#include "doubly_linked_list.h"	/*	header file	*/

typedef struct sorted_list sorted_list_t; 

typedef int (*sorted_list_cmp_fuction_t)(const void *lhs, const void *rhs);


/* DO NOT USE INTERNAL MEMBERS OF THE STRUCT!!!! */
typedef struct sorted_list_iter
{
	dlist_iterator_t iter;
	#ifndef NDEBUG
	sorted_list_t *sorted_list;
	#endif
} sorted_list_iter_t;


/*-----------------------------------------------------*/

/* SortedListCreate:

	Parameters:
	    is_match - function supplies by the user to match criteria
	Returns:
		success : return new SortedList
		Failure : return NULL
	Complexity:	
		O(1)
*/
sorted_list_t *SortedListCreate(sorted_list_cmp_fuction_t cmp);

/*-----------------------------------------------------*/

/* SortedListDestroy:

	Parameters:
		sorted_list - list to destroy
	Returns:
		none
	Complexity:	
		O(n)
*/
void SortedListDestroy(sorted_list_t *sorted_list);

/*-----------------------------------------------------*/

/* SortedListBegin:

	Parameters:
		sorted_list - list from user
	Returns:
		Iterator to first element
		List is empty : return List end
	Complexity:	
		O(1)
*/
sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list);

/*------------------------------------------------------*/

/* SortedListEnd:

	Parameters:
		sorted_list - list from user
	Returns:
		List end
	Complexity:	
		O(1)
*/
sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list);

/*-----------------------------------------------------*/

/* SortedListInsert:
    Description: inserts the given @data
	Parameters:
	    sorted_list - list from user
		data - data to insert
	Returns:
		success - newly created node
		fail - List end
	Complexity:	
	    	O(N)
*/
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data);

/*-----------------------------------------------------*/

/* SortedListRemove:

	Parameters:
		which - which data indicated by iterator to remove
	Returns:
		iterator to the data after the one that was removed 
	Complexity:	
		O(1)
*/
sorted_list_iter_t SortedListRemove(sorted_list_iter_t which);

/*-----------------------------------------------------*/
/* SortedListPopFront:
	Parameters:
		sorted_list - list from user
	Returns:
		return data of the removed iterator
	Complexity:	
		O(1)
*/

void *SortedListPopFront(sorted_list_t *sorted_list);

/*-----------------------------------------------------*/
/* SortedListPopBack:
	Parameters:
		sorted_list - list from user
	Returns:
		return data of the removed iterator
	Complexity:
		O(1)
*/

void *SortedListPopBack(sorted_list_t *sorted_list);

/*-----------------------------------------------------*/
/* SortedListGetData:

	Parameters:
		from - from where to get the data
	Returns:
		returns the data
	Complexity:	
		O(1)
*/
void *SortedListGetData(sorted_list_iter_t from);

/*-----------------------------------------------------*/
/* sorted_listNext:

	Parameters:
		current - current where to go
	Returns:
		next iterator
	Complexity:	
		O(1)
*/
sorted_list_iter_t SortedListNext(sorted_list_iter_t curr);

/*-----------------------------------------------------*/

/* SortedListPrevious:

	Parameters:
		curr - current where to go
	Returns:
		previous iterator
	Complexity:	
		O(1)
*/
sorted_list_iter_t SortedListPrevious(sorted_list_iter_t curr);

/*-----------------------------------------------------*/

/* SortedListSize:

	Parameters:
		sorted_list - list to check
	Returns:
		Number of element in the list 
	Complexity:	
		O(N)
*/
size_t SortedListSize(const sorted_list_t *sorted_list);

/*-----------------------------------------------------*/

/* SortedKistIsEmpty:
	Parameters:
		sorted_list - list to check
	Returns:
		returns 1 if the list is empty, 0 if not
	Complexity:	
		O(1)
*/
int SortedListIsEmpty(const sorted_list_t *sorted_list);

/*-----------------------------------------------------*/

/* SortedListIsSameIter:

	Parameters:
		iter1 - first element 
		iter2 - secoend element 
	Returns:
		returns 1 if the iterators are same, 0 if not
	Complexity:	
		O(1)
*/
int SortedListIsSameIter(sorted_list_iter_t iter1, sorted_list_iter_t iter2);

/*-----------------------------------------------------*/

/* SortedListFind:
    Description :
        the function find the first element with matching given data.
	Parameters:
	   sorted_list - the sorted list for the compare function 
	   	from - starting iterator (included)
		to - ending iterator (excluded)
	   param - parameter to find
	Returns:
		returns iterator to the first matching element
		Not found : return "to" iterator  
	Complexity:	
		O(N)
		
*/
sorted_list_iter_t SortedListFind( sorted_list_t *sorted_list,
								   sorted_list_iter_t from,
								   sorted_list_iter_t to,
								   const void *param ); 

/*-----------------------------------------------------*/
/* SortedListFindIf:
    Description:
        the function find the first matching element by given data.
	Parameters:
		from - starting iterator (included)
		to - ending iterator (excluded)
		function - is match function, compare right to left
		    lhs/rhs - left/right hand side
		param - parameter to find
		creteria - term that must exsist in the node
	Returns:
		returns matching iterator
		Not found : return iterator to "to" 
	Complexity:	
		O(N)
*/
sorted_list_iter_t SortedListFindIf( sorted_list_iter_t from,
									 sorted_list_iter_t to,
									 int (*is_match)(const void *lhs, const void *rhs),
									 const void *param);

/*-----------------------------------------------------*/

/* SortedListForEach 

	Parameters:
		from - starting iterator (included)
		to - ending iterator (excluded)
		function - action function 
		param - parameter sent by user
	Returns:
		returns action function status
	Complexity:	
		O(N)
	Note : the func stop running on first action function failure
	**Attention** : changing the underlying sorted 'member' 
	                 will couse undefined behiver
*/
int SortedListForEach( sorted_list_iter_t from,
					   sorted_list_iter_t to,
					   int (*action)(void *data, void *param),
					   void *param ); 

/*-----------------------------------------------------*/
/* SortedListMerge

	Parameters:
        dest - the 1st list for merging
        src - the 2nd list for merging    
	Complexity:	
		O(N + M)
	Note : after action, the src list will be empty
*/
void SortedListMerge(sorted_list_t *dest, sorted_list_t *src); 

/*-----------------------------------------------------*/
#endif /* __OL134_SORTED_LINKED_LIST_H__*/
