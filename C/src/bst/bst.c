/************************************
* Developer:   Batel Levi           *
* Reviewer:    Abir                 *
*************************************/
#include <stdlib.h>	/*	for malloc	*/
#include <assert.h>	/*	for assert	*/


#include "bst.h"	/*	header file	*/


#define TO_NODE(x) ((node_t *)(x))
#define TO_ITER(x) ((bst_iterator_t)(x))
#define GET_END(x) ((x)->dummy_root)
#define GET_CMP_FUNC(x) ((x)->cmpfunc)
#define GET_PARENT(x) (TO_NODE(x)->parent)
#define GET_LEFT_CHILD(x) (TO_NODE(x)->children[LEFT])
#define GET_RIGHT_CHILD(x) (TO_NODE(x)->children[RIGHT])
#define GET_DATA(x) (TO_NODE(x)->data)
#define GET_DUMMY_PARENT(x) ((x)->dummy_root.parent)
#define GET_DUMMY_LEFT_CHILD(x) ((x)->dummy_root.children[LEFT])
#define GET_DUMMY_RIGHT_CHILD(x) ((x)->dummy_root.children[RIGHT])
#define GET_DUMMY_DATA(x) ((x)->dummy_root.data)
#define IS_LEFT_CHILD(x) (TO_NODE(x) == GET_LEFT_CHILD(GET_PARENT(TO_NODE(x))))
#define IS_RIGHT_CHILD(x) (TO_NODE(x) == GET_RIGHT_CHILD(GET_PARENT(TO_NODE(x))))
#define IS_ROOT(x) (GET_PARENT(GET_PARENT(x)) == NULL)


typedef struct node node_t;

enum child_node_pos
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
};

struct node
{
	node_t *parent;
	node_t *children[NUM_OF_CHILDREN];
	void *data;
};

struct bst
{
	node_t dummy_root;
	cmpfunc_t cmpfunc;
};


/*	utility functions	*/
static int InsertChild(node_t *node, int child_position, void *data);
static int Count(void *data, void *param);
/*	return the next iterator	*/
static bst_iterator_t RemoveLeaf(bst_iterator_t which);
static bst_iterator_t RemoveParentWithOneChild(bst_iterator_t which, int child_position);
static bst_iterator_t RemoveParentWithTwoChildren(bst_iterator_t which);
/*	connect parent to a child as left or right child	*/
static void ConnectTwoNodes(bst_iterator_t parent, bst_iterator_t child, int child_position);


bst_t *BSTCreate(cmpfunc_t cmp)
{
	bst_t *bst = (bst_t *)malloc(sizeof(bst_t));

	if (NULL == bst)
	{
		return NULL;
	}

	GET_DUMMY_PARENT(bst) = NULL;

	GET_DUMMY_LEFT_CHILD(bst) = NULL;
	GET_DUMMY_RIGHT_CHILD(bst) = NULL;

	GET_DUMMY_DATA(bst) = &bst;

	GET_CMP_FUNC(bst) = cmp;

	return (bst);
}

void BSTDestroy(bst_t *bst)
{
	node_t *node = NULL;

	assert(bst);
	
	node = BSTBegin(bst);

	while (!BSTIsSameIter(node, BSTEnd(bst)))
	{
		node = BSTRemove(node);
	}

	free(bst);
}

size_t BSTSize(const bst_t *bst)
{
	size_t count = 0;

	assert(bst);

	BSTForEach(BSTBegin(bst), BSTEnd(bst), Count, &count);

	return (count);
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);

	return (GET_DUMMY_LEFT_CHILD(bst) == NULL);
}

bst_iterator_t BSTInsert(bst_t *bst, void *data)
{
	node_t *node = NULL;
	
	assert(bst);
	assert(data);

	if (BSTIsEmpty(bst))
	{
		if (InsertChild(&GET_END(bst), LEFT, data))
		{
			return (BSTEnd(bst));
		}

		return (BSTBegin(bst));
	}

	node = GET_DUMMY_LEFT_CHILD(bst);

	while (1)
	{
		/*	as long as the data is smaller,
			move down left and insert when there is no left child	*/
		while (GET_CMP_FUNC(bst)(data, GET_DATA(node)) < 0)
		{
			if (NULL == GET_LEFT_CHILD(node))
			{
				if (InsertChild(node, LEFT, data))
				{
					return (BSTEnd(bst));
				}

				return (TO_ITER(GET_LEFT_CHILD(node)));
			}

			node = GET_LEFT_CHILD(node);
		}

		/*	as long as the data is bigger,
			move down right and insert when there is no right child	*/
		while (GET_CMP_FUNC(bst)(data, GET_DATA(node)) > 0)
		{
			if (NULL == GET_RIGHT_CHILD(node))
			{
				if (InsertChild(node, RIGHT, data))
				{
					return (BSTEnd(bst));
				}

				return (TO_ITER(GET_RIGHT_CHILD(node)));
			}

			node = GET_RIGHT_CHILD(node);
		}
	}
}

bst_iterator_t BSTRemove(bst_iterator_t which)
{
	bst_iterator_t next = {0};

	assert(TO_NODE(which));

	if (NULL == GET_LEFT_CHILD(which) && NULL == GET_RIGHT_CHILD(which))
	{
		next = RemoveLeaf(which);

		return (next);
	}

	if (NULL != GET_LEFT_CHILD(which) && NULL == GET_RIGHT_CHILD(which))
	{
		next = RemoveParentWithOneChild(which, LEFT);
	
		return (next);
	}

	if (NULL != GET_RIGHT_CHILD(which) && NULL == GET_LEFT_CHILD(which))
	{
		next = RemoveParentWithOneChild(which, RIGHT);
	
		return (next);
	}

	next = RemoveParentWithTwoChildren(which);

	return (next);
}

bst_iterator_t BSTBegin(const bst_t *bst)
{
	node_t *node = NULL;

	assert(bst);

	if (BSTIsEmpty(bst))
	{	
		return (BSTEnd(bst));
	}

	node = GET_DUMMY_LEFT_CHILD(bst);

	while (NULL != GET_LEFT_CHILD(node))
	{
		node = GET_LEFT_CHILD(node);
	}

	return (TO_ITER(node));
}

bst_iterator_t BSTEnd(const bst_t *bst)
{
	assert(bst);

	return (TO_ITER(&GET_END(bst)));
}

bst_iterator_t BSTPrev(bst_iterator_t from)
{
	assert(TO_NODE(from));

	/* get the rightmost leaf of the left subtree	*/
	if (NULL != GET_LEFT_CHILD(from))
	{
		from = TO_ITER(GET_LEFT_CHILD(from));

		while (NULL != GET_RIGHT_CHILD(from))
		{
			from = TO_ITER(GET_RIGHT_CHILD(from));
		}

		return (from);
	}

	/*	go up until from becomes rigth child and return its parent	*/
	while (IS_LEFT_CHILD(from) && !IS_ROOT(from))
	{
			from = TO_ITER(GET_PARENT(from));
	}
	
	return (TO_ITER(GET_PARENT(from)));
}

bst_iterator_t BSTNext(bst_iterator_t from)
{
	assert(TO_NODE(from));

	/* get the leftmost leaf of the right subtree	*/
	if (NULL != GET_RIGHT_CHILD(from))
	{
		from = TO_ITER(GET_RIGHT_CHILD(from));

		while (NULL != GET_LEFT_CHILD(from))
		{
			from = TO_ITER(GET_LEFT_CHILD(from));
		}

		return (from);
	}

	/*	go up until from becomes left child and return its parent	*/
	while (IS_RIGHT_CHILD(from))
	{
			from = TO_ITER(GET_PARENT(from));
	}
	
	return (TO_ITER(GET_PARENT(from)));
}

int BSTIsSameIter(bst_iterator_t iter1, bst_iterator_t iter2)
{
	assert(TO_NODE(iter1));
	assert(TO_NODE(iter2));

	return (iter1 == iter2);
}

void *BSTGetData(bst_iterator_t from)
{
	assert(TO_NODE(from));

	return (GET_DATA(from));
}

bst_iterator_t BSTFind(const bst_t *bst, void *param)
{
	bst_iterator_t iter = {0};

	assert(bst);

	iter = GET_DUMMY_LEFT_CHILD(bst);

	while (NULL != iter)
	{
		if (GET_CMP_FUNC(bst)((void *)param, GET_DATA(iter)) == 0)
		{
			return (iter);
		}
	
		if (GET_CMP_FUNC(bst)((void *)param, GET_DATA(iter)) > 0)
		{
			iter = GET_RIGHT_CHILD(iter);

		}

		if (GET_CMP_FUNC(bst)((void *)param, GET_DATA(iter)) < 0)
		{
			iter = GET_LEFT_CHILD(iter);
		}
	}

	return (BSTEnd(bst));
}

int BSTForEach(	bst_iterator_t from, bst_iterator_t to, 
				int (*action_func)(void *data, void *param), void *param )
{
	int status = 0;

	assert(TO_NODE(from));
	assert(TO_NODE(to));
	assert(action_func);
	
	while (!BSTIsSameIter(from, to))
	{
		status = action_func(GET_DATA(from), param);
		
		if (status)
		{
			return (status);
		}

		from = BSTNext(from);
	}

	return (0);
}


static int InsertChild(node_t *node, int child_position, void *data)
{
	assert(node);

	if (LEFT == child_position)
	{
		GET_LEFT_CHILD(node) = (node_t *)malloc(sizeof(node_t));

		if (NULL == GET_LEFT_CHILD(node))
		{
			return (1);
		}

		GET_DATA(GET_LEFT_CHILD(node)) = data;
		GET_PARENT(GET_LEFT_CHILD(node)) = node;
		GET_LEFT_CHILD(GET_LEFT_CHILD(node)) = NULL;
		GET_RIGHT_CHILD(GET_LEFT_CHILD(node)) = NULL;
	}

	if (RIGHT == child_position)
	{
		GET_RIGHT_CHILD(node) = (node_t *)malloc(sizeof(node_t));

		if (NULL == GET_RIGHT_CHILD(node))
		{
			return (1);
		}

		GET_DATA(GET_RIGHT_CHILD(node)) = data;
		GET_PARENT(GET_RIGHT_CHILD(node)) = node;
		GET_LEFT_CHILD(GET_RIGHT_CHILD(node)) = NULL;
		GET_RIGHT_CHILD(GET_RIGHT_CHILD(node)) = NULL;
	}

	return (0);
}


static int Count(void *data, void *param)
{
	(void)data;

	*(size_t *)param += 1;

	return (0);
}


static bst_iterator_t RemoveLeaf(bst_iterator_t which)
{
	bst_iterator_t next = {0};
	node_t *parent = NULL;

	assert(TO_NODE(which));

	next = BSTNext(which);
	parent = GET_PARENT(which);

	if (IS_LEFT_CHILD(which))
	{
		GET_LEFT_CHILD(parent) = NULL;
	}
	else
	{
		GET_RIGHT_CHILD(parent) = NULL;
	}

	free(TO_NODE(which));
	
	return (next);
}

static bst_iterator_t RemoveParentWithOneChild(bst_iterator_t which, int child_position)
{
	bst_iterator_t next = {0};

	assert(TO_NODE(which));

	next = BSTNext(which);

	if (LEFT == child_position)
	{
		if (IS_LEFT_CHILD(which))
		{
			ConnectTwoNodes(GET_PARENT(which), GET_LEFT_CHILD(which), LEFT);
		}
		else
		{
			ConnectTwoNodes(GET_PARENT(which), GET_LEFT_CHILD(which), RIGHT);
		}
	}

	if (RIGHT == child_position)
	{
		if (IS_LEFT_CHILD(which))
		{
			ConnectTwoNodes(GET_PARENT(which), GET_RIGHT_CHILD(which), LEFT);
		}
		else
		{
			ConnectTwoNodes(GET_PARENT(which), GET_RIGHT_CHILD(which), RIGHT);
		}
	}

	free(TO_NODE(which));
	
	return (next);
}

static bst_iterator_t RemoveParentWithTwoChildren(bst_iterator_t which)
{
	bst_iterator_t next = {0};

	assert(TO_NODE(which));

	next = TO_NODE(BSTNext(which));

	if (IS_LEFT_CHILD(next))
	{
		ConnectTwoNodes(GET_PARENT(next), GET_RIGHT_CHILD(next), LEFT);
	}
	else
	{
		ConnectTwoNodes(GET_PARENT(next), GET_RIGHT_CHILD(next), RIGHT);
	}

	if (IS_LEFT_CHILD(which))
	{
		ConnectTwoNodes(GET_PARENT(which), next, LEFT);
	}
	else
	{
		ConnectTwoNodes(GET_PARENT(which), next, RIGHT);
	}

	ConnectTwoNodes(next, GET_LEFT_CHILD(which), LEFT);
	ConnectTwoNodes(next, GET_RIGHT_CHILD(which), RIGHT);

	free(TO_NODE(which));

	return (next);
}

static void ConnectTwoNodes(bst_iterator_t parent, bst_iterator_t child, int child_position)
{
	assert(TO_NODE(parent));

	if (LEFT == child_position)
	{
		GET_LEFT_CHILD(parent) = child;
	}

	if (RIGHT == child_position)
	{
		GET_RIGHT_CHILD(parent) = child;
	}

	if (NULL != child)
	{
		GET_PARENT(child) = parent;
	}
}