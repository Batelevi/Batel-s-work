/*********************************************
* Developer:      Batel Levi                 *
* Reviewer:       Ovi                        * 
**********************************************/

#include <stddef.h> /* for size_t */
#include <assert.h>	/*	for assert	*/
#include <stdlib.h>	/*	for malloc	*/

#include "singly_linked_list.h"	/*	header file	*/


#define TO_NODE(x) (node_t *)(x)
#define TO_ITER(x) (list_iterator_t)(x)
#define TO_LIST(x) (list_t *)(x)
#define UNUSED(x) (void)(x)

typedef struct node node_t;

static int Count(void *data, void *param);	/*	for ListSize function	*/
static int IsDummy(node_t *position);	/*	utility function	*/
static node_t *CreateNode(void *data, node_t *next);	/*	utility function	*/


struct node
{
	void *data;
	node_t *next;
};

struct list
{
	node_t *head;
	node_t *tail;
};


list_t *ListCreate(void)
{
	list_t *list = (list_t *)malloc(sizeof(list_t));

	if (NULL == list)
	{
		return NULL;
	}
	
	list->head = CreateNode(list, NULL);
	
	if (NULL == list->head)
	{
		free(list);
		return NULL;
	}
	
	list->tail = list->head;
	
	return (list);
}

void ListDestroy(list_t *list)
{
	node_t *temp = NULL;
	
	assert(list);
	
	while (!ListIsSame(list->head, list->tail))
	{
		temp = list->head->next;
		free(list->head);
		list->head = temp;
	}

	free(list->head);
	free(list);
}

list_iterator_t ListHead(const list_t *list)
{
	assert(list);
	
	return (TO_ITER(list->head));
}

list_iterator_t ListTail(const list_t *list)
{
	assert(list);
	
	return (TO_ITER(list->tail));
}

list_iterator_t ListInsert(void *data, list_iterator_t position)
{
	node_t *new = NULL;

	assert(data);
	assert(position);
	
	new = CreateNode(TO_NODE(position)->data, TO_NODE(position)->next);
	
	if (NULL == new)
	{
		while (!IsDummy(position))
		{
			position = TO_NODE(position)->next;
		}
		
		return (position);
	}
	
	(TO_NODE(position))->data = data;
	(TO_NODE(position))->next = new;
	
	if (IsDummy(new))
	{
		(TO_LIST(new->data))->tail = new;
	}
	
	return (position);
}

list_iterator_t ListNext(list_iterator_t position)
{
	assert(position);
	
	return (TO_ITER(TO_NODE(position)->next));
}

list_iterator_t ListRemove(list_iterator_t position)
{
	node_t *temp = NULL;

	assert(position);
	
	temp = (TO_NODE(position))->next;
	
	(TO_NODE(position))->data = temp->data;
	(TO_NODE(position))->next = temp->next;
	
	if (IsDummy(position))
	{
		(TO_LIST(position->data))->tail = position;
	}
	
	free(temp);
	
	return (position);
}

void ListSetData(void *data, list_iterator_t position)
{
	assert(data);
	assert(position);
	
	(TO_NODE(position))->data = data;
}

void *ListGetData(list_iterator_t position)
{
	assert(position);
	
	return ((TO_NODE(position))->data);
}

size_t ListSize(const list_t *list)
{
	size_t count = 0;
	action_function_t list_count = Count;
	
	assert(list);

	ListForEach(TO_ITER(list->head), ListTail(TO_LIST(list)), list_count, &count);

	return (count);
}

int ListIsEmpty(const list_t *list)
{
	assert(list);
	
	return (list->head->next == NULL);
}

int ListIsSame(list_iterator_t iter1, list_iterator_t iter2)
{
	return (iter1 == iter2);
}

list_iterator_t ListFindData(list_iterator_t from, list_iterator_t to, is_match_function_t function, void *param)
{
	node_t *temp = NULL;

	assert(from);
	assert(to);
	assert(param);
		
	temp = TO_NODE(from);
	
	while (!ListIsSame(temp, to))
	{
		if (function(TO_NODE(temp)->data, param))
		{
			return (temp);
		}
		
		temp = temp->next;
	}
	
	return (to);
}

int ListForEach(list_iterator_t from, list_iterator_t to, action_function_t function, void *param)
{
	node_t *temp = NULL;
	int status = 0;

	assert(from);
	assert(to);
	assert(param);
		
	temp = TO_NODE(from);
	
	while (!ListIsSame(temp, to))
	{
		status = function(temp->data, param);
		
		if (status)
		{
			return (status);
		}
		
		temp = temp->next;
	}
	
	return (0);
}

static int Count(void *data, void *param)
{ 
	UNUSED(data);
	assert(param);
	
	++*(size_t *)param;
	
	return (0);
}

static int IsDummy(node_t *position)
{
	assert(position);
	
	return (NULL == position->next);
}

static node_t *CreateNode(void *data, node_t *next)
{
	node_t *new = (node_t *)malloc(sizeof(node_t));
	
	if (NULL == new)
	{
		return NULL;
	}
	
	new->data = data;
	new->next = next;
	
	return (new);
}

void ListAppend(list_t *dest, list_t *src)
{
	assert(dest);
	assert(src);
	
	src->tail->data = dest;
	
	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;
	
	dest->tail = src->tail;
	
	src->head->data = src;
	src->head->next = NULL;
	src->tail = src->head;
}
