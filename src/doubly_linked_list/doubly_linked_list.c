/*********************************************
* Developer:   Batel Levi                    *
* Reviewer:    Yana                          *
**********************************************/

#include <stddef.h> /* for size_t */
#include <stdlib.h>	/*	for malloc	*/
#include <assert.h>	/*	for assert	*/


#include "doubly_linked_list.h"	/*	header file	*/

#define TO_ITER(x) ((dlist_iterator_t)(x))
#define TO_NODE(x) ((node_t *)(x))

#define UNUSED(x) (void)(x)

typedef struct node node_t;

struct node
{
	void *data;
	node_t *previous;
	node_t *next;
};

struct dlist
{
	node_t begin;
	node_t end;
};


static int Count(void *data, void *param);	/*	utility function for size	*/
static dlist_iterator_t GetEnd(dlist_iterator_t where);	/*	utility function	*/
static dlist_iterator_t CreateNode(void *data, node_t *previous, node_t *next);	/*	utility function	*/

dlist_t *DListCreate(void)
{
	dlist_t *dlist = (dlist_t *)malloc(sizeof(dlist_t));
	
	if (NULL == dlist)
	{
		return NULL;
	}

	dlist->begin.data = NULL;	
	dlist->begin.previous = NULL;
	dlist->begin.next = &dlist->end;

	dlist->end.data = NULL;		
	dlist->end.previous = &dlist->begin;
	dlist->end.next = NULL;
		
	return (dlist);
}


void DListDestroy(dlist_t *dlist)
{
	node_t *next = NULL;
	
	assert(dlist);

	while (!DListIsSameIter(DListBegin(dlist), DListEnd(dlist)))
	{
		next = TO_NODE(DListNext(DListBegin(dlist)));
		free(TO_NODE(DListBegin(dlist)));
		dlist->begin.next = next;
	}

	free(dlist);
	dlist = NULL;
}


dlist_iterator_t DListBegin(const dlist_t *dlist)
{
	assert(dlist);
	
	return (TO_ITER(dlist->begin.next));
}


dlist_iterator_t DListEnd(const dlist_t *dlist)
{
	assert(dlist);
	
	return (TO_ITER(&dlist->end));
}


dlist_iterator_t DListInsert(void *data, dlist_iterator_t where)
{
	dlist_iterator_t new = {0};
	
	assert(data);
	assert(TO_NODE(where));
	
	new = CreateNode(data, TO_NODE(DListPrev(where)), TO_NODE(where));
	
	if (NULL == new)
	{
		return (GetEnd(where));
	}
	
	TO_NODE(DListPrev(where))->next = new;

	TO_NODE(where)->previous = new;
	
	return (new);
}


dlist_iterator_t DListRemove(dlist_iterator_t which)
{
	dlist_iterator_t temp = {0};
	node_t *node_which = TO_NODE(which);
	
	assert(TO_NODE(which));
	assert(TO_NODE(which)->next);
	
	temp = DListNext(which);
	
	node_which->previous->next = node_which->next;
	node_which->next->previous = node_which->previous;
	
	free(TO_NODE(which));
	
	return (temp);
}


dlist_iterator_t DListPushFront(dlist_t *dlist, void *data)
{
	assert(dlist);
	assert(data);
	
	return (DListInsert(data, DListBegin(dlist)));
}


void *DListPopFront(dlist_t *dlist)
{
	void *data = NULL;
	
	assert(dlist);
	
	data = DListGetData(DListBegin(dlist));
	
	DListRemove(DListBegin(dlist));

	return (data);
}


dlist_iterator_t DListPushBack(dlist_t *dlist, void *data)
{
	assert(dlist);
	assert(data);
	
	return (DListInsert(data, DListEnd(dlist)));
}


void *DListPopBack(dlist_t *dlist)
{
	void *data = NULL;
	
	assert(dlist);
	
	data = DListGetData(DListPrev(DListEnd(dlist)));
	
	DListRemove(DListPrev(DListEnd(dlist)));
	
	return (data);
}


void DListSetData(dlist_iterator_t where, void *data)
{
	assert(TO_NODE(where));
	assert(TO_NODE(where)->next);
	assert(data);
	
	TO_NODE(where)->data = data;
}


void *DListGetData(dlist_iterator_t from)
{
	assert(TO_NODE(from));
	
	return (TO_NODE(from)->data);
}


dlist_iterator_t DListNext(dlist_iterator_t current)
{
	assert(TO_NODE(current));
	
	return (TO_ITER(TO_NODE(current)->next));
}


dlist_iterator_t DListPrev(dlist_iterator_t current)
{
	assert(TO_NODE(current));
	
	return (TO_ITER(TO_NODE(current)->previous));
}


size_t DListSize(const dlist_t *dlist)
{
	size_t count = 0;
	
	assert(dlist);
	
	DListForEach(DListBegin(dlist), DListEnd(dlist), Count, &count);
	
	return (count);
}


int DListIsEmpty(const dlist_t *dlist)
{
	assert(dlist);
	
	return (DListIsSameIter(DListBegin(dlist), DListEnd(dlist)));
}


int DListIsSameIter(dlist_iterator_t iter1, dlist_iterator_t iter2)
{
	assert(TO_NODE(iter1));
	assert(TO_NODE(iter2));
	
	return (iter1 == iter2);
}


dlist_iterator_t DListFindData( dlist_iterator_t from,
                                dlist_iterator_t to, 
								int (*is_match)(const void *lhs, const void *rhs),
								void *params )
{
	assert(TO_NODE(from));
	assert(TO_NODE(to));
	assert(params);
	
	while (!DListIsSameIter(from, to))
	{
		if (is_match(DListGetData(from), params))
		{
			return (from);
		}
		
		from = DListNext(from);
	}
	
	return (to);
}


int DListForEach( dlist_iterator_t from,
				  dlist_iterator_t to,
				  int (*action)(void *data, void *param),
				  void *param )
{
	int status = 0;

	assert(TO_NODE(from));
	assert(TO_NODE(to));
	assert(param);
	
	while (!DListIsSameIter(from, to))
	{
		status = action(DListGetData(from), param);

		if (status)
		{
			return (status);
		}
		
		from = DListNext(from);
	}
	
	return (0);
}
				  


int DListMultifind( dlist_iterator_t from,
                    dlist_iterator_t to, 
					int (*is_match)(const void *lhs, const void *rhs), 
					void *param,
					dlist_t *output_list )
{
	dlist_iterator_t iterator = {0};

	assert(TO_NODE(from));
	assert(TO_NODE(to));
	assert(param);
	assert(output_list);
	
	while (!DListIsSameIter(from, to))
	{
		if (is_match(DListGetData(from), param))
		{
			iterator = DListInsert(DListGetData(from), DListEnd(output_list));
			
			if (DListIsSameIter(iterator, DListEnd(output_list)))
			{
				return (1);
			}
		}
		
		from = DListNext(from);
	}
	
	return (0);
}


void DListSplice(dlist_iterator_t from, dlist_iterator_t to, dlist_iterator_t where)
{
	dlist_iterator_t temp = {0};
	node_t *node_from = TO_NODE(from);
	node_t *node_to = TO_NODE(to);
	node_t *node_where = TO_NODE(where);
	
	assert(node_from);
	assert(node_to);
	assert(node_where);

	temp = DListPrev(from);

	node_from->previous->next = node_to;
	
	node_where->previous->next = node_from;
	node_from->previous = TO_NODE(where)->previous;
	
	node_to->previous->next = TO_NODE(where);
	node_where->previous = node_to->previous;
	
	node_to->previous = TO_NODE(temp);
}


static int Count(void *data, void *param)
{
	UNUSED(data);
	assert(param);
	
	*(int *)param += 1;
	
	return (0);
}

static dlist_iterator_t GetEnd(dlist_iterator_t where)
{
	while (DListNext(where) != NULL)
	{
		where = DListNext(where);
	}
		
	return (where);
}

static dlist_iterator_t CreateNode(void *data, node_t *previous, node_t *next)
{
	node_t *new = (node_t *)malloc(sizeof(node_t));
	
	if (NULL == new)
	{
		return NULL;
	}
	
	new->data = data;
	new->previous = previous;
	new->next = next;
	
	return (TO_ITER(new));
}
