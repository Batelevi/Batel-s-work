/*********************************************
* Developer:      Batel Levi                 *
* Reviewer:       Ovi                        *
**********************************************/

#include <stddef.h>	/*	for size_t	*/
#include <stdlib.h>	/*	for malloc	*/
#include <assert.h>	/*	for assert	*/
#include <stdio.h>

#include "sorted_list.h"	/*	header file	*/

#define TO_ITER(x) ((x).iter)


struct sorted_list
{
    dlist_t *dlist;
    sorted_list_cmp_fuction_t cmp;
};


static int IsBefore(const void *lhs, const void *rhs);	/*	utility function for insert and merge	*/


sorted_list_t *SortedListCreate(sorted_list_cmp_fuction_t cmp)
{
	sorted_list_t *sorted_list = NULL;

	assert(cmp);
		
	sorted_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	
	if (NULL == sorted_list)
	{
		return NULL;
	}
	
	sorted_list->dlist = DListCreate();
	
	if (NULL == sorted_list->dlist)
	{
		free(sorted_list);
		return NULL;
	}
	
	sorted_list->cmp = cmp;
	
	return (sorted_list);
}


void SortedListDestroy(sorted_list_t *sorted_list)
{
	DListDestroy(sorted_list->dlist);
	
	sorted_list->dlist = NULL;
	sorted_list->cmp = NULL;
	
	free(sorted_list);
	sorted_list = NULL;
}


sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t return_iter = {0};
	
	assert(sorted_list);
	
	TO_ITER(return_iter) = DListBegin(sorted_list->dlist);
	
	#ifndef NDEBUG
	return_iter.sorted_list = (sorted_list_t *)sorted_list;
	#endif	
	
	return (return_iter);
}

sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t return_iter = {0};
	
	assert(sorted_list);
	
	TO_ITER(return_iter) = DListEnd(sorted_list->dlist);

	#ifndef NDEBUG
	return_iter.sorted_list = (sorted_list_t *)sorted_list;
	#endif
    	
	return (return_iter);	
}

sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	sorted_list_iter_t where = {0};
	void *arr[2] = {0};	/*	will be sent as param to is_match func in FindIf	*/
    
	assert(sorted_list);
	assert(data);

	arr[0] = sorted_list;
	arr[1] = data;

	where = SortedListFindIf(SortedListBegin(sorted_list), SortedListEnd(sorted_list), IsBefore, arr);
    
	TO_ITER(where) = DListInsert(data, TO_ITER(where));

	#ifndef NDEBUG
	where.sorted_list = (sorted_list_t *)sorted_list;
	#endif	
	
	return (where);
}

sorted_list_iter_t SortedListRemove(sorted_list_iter_t which)
{
	assert(TO_ITER(which));
	
	TO_ITER(which) = DListRemove(TO_ITER(which));
	
	return (which);
}

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(sorted_list);
	
	return (DListPopFront(sorted_list->dlist));
}

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(sorted_list);
	
	return (DListPopBack(sorted_list->dlist));
}

void *SortedListGetData(sorted_list_iter_t from)
{
	assert(TO_ITER(from));
	
	return (DListGetData(TO_ITER(from)));
}

sorted_list_iter_t SortedListNext(sorted_list_iter_t curr)
{
	assert(TO_ITER(curr));
	
	TO_ITER(curr) = DListNext(TO_ITER(curr));
	
	return (curr);
}

sorted_list_iter_t SortedListPrevious(sorted_list_iter_t curr)
{
	assert(TO_ITER(curr));
	
	TO_ITER(curr) = DListPrev(TO_ITER(curr));
	
	return (curr);
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	assert(sorted_list);
	
	return (DListSize(sorted_list->dlist));
}

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(sorted_list);
	
	return (DListIsEmpty(sorted_list->dlist));	
}

int SortedListIsSameIter(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	assert(TO_ITER(iter1));
	assert(TO_ITER(iter2));
	
	return (TO_ITER(iter1) == TO_ITER(iter2));
}

sorted_list_iter_t SortedListFind( sorted_list_t *sorted_list,
								   sorted_list_iter_t from,
								   sorted_list_iter_t to,
								   const void *param )
{
	assert(sorted_list);
	assert(TO_ITER(from));
	assert(TO_ITER(to));
	assert(param);
	
	while (!SortedListIsSameIter(from, to))
	{
		if (0 == sorted_list->cmp(SortedListGetData(from), param))
		{
			return (from);
		}
		
		from = SortedListNext(from);
	}
	
	return (to);
} 

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
									sorted_list_iter_t to,
									int (*is_match)(const void *lhs, const void *rhs),
									const void *param)
{
	assert(TO_ITER(from));
	assert(TO_ITER(to));
	assert(param);
	
	TO_ITER(from) = DListFindData(TO_ITER(from), TO_ITER(to), is_match, (void *)param);
   		
	return (from);
}

int SortedListForEach(sorted_list_iter_t from,
					  sorted_list_iter_t to,
					  int (*action)(void *data, void *param),
					  void *param)
{
	assert(TO_ITER(from));
	assert(TO_ITER(to));
	assert(param);
	assert(from.sorted_list == to.sorted_list);
	
	return (DListForEach(TO_ITER(from), TO_ITER(to), action, param));
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_iter_t dest_where = {0};			
	sorted_list_iter_t src_from_iter = {0};	
	sorted_list_iter_t src_to_iter = {0};	
	void *arr[2] = {0};	/*	will be sent as param to is_match func in FindIf	*/
	
	assert(dest);
	assert(src);
	
	arr[0] = dest;
	
	src_from_iter = SortedListBegin(src);
	dest_where = SortedListBegin(dest);
	
	while (!SortedListIsSameIter(src_from_iter, SortedListEnd(src)))
	{
		arr[1] = SortedListGetData(src_from_iter);
		
		/*	find in dest where to splice	*/
		dest_where = SortedListFindIf(dest_where, SortedListEnd(dest), IsBefore, arr);
		
		/*	if to splice into the end of dest, set to to end of src	*/
		if (SortedListIsSameIter(dest_where, SortedListEnd(dest)))
		{
			src_to_iter = SortedListEnd(src);
		}
		else	/*	find in src until which iterator to splice into dest	*/
		{
			arr[1] = SortedListGetData(dest_where);
		
			src_to_iter = SortedListFindIf( SortedListNext(src_from_iter),
											SortedListEnd(src),
											IsBefore,
											arr );		
		}
		
		DListSplice( TO_ITER(src_from_iter),
					 TO_ITER(src_to_iter),
					 TO_ITER(dest_where) );
		
		src_from_iter = src_to_iter;
		dest_where = SortedListNext(dest_where);
	}
}

static int IsBefore(const void *lhs, const void *rhs)
{
	const void *param = *((void **)rhs + 1);	/*	rhs is an array of void *, rhs[1] == data	*/

	assert(lhs);
	assert(rhs);

	/*	(sorted_list_t *)*(void **)rhs == rhs[0]	*/
	return (((sorted_list_t *)*(void **)rhs)->cmp(lhs, param) > 0);
}
