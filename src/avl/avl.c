/*********************************************
* Developer:      Batel Levi                 *
* Reviewer:       Idan                       *
**********************************************/
#include <assert.h>	/*	for assert	*/
#include <stdlib.h>	/*	for malloc	*/


#include "avl.h"	/*	header file	*/


#define LEFT_CHILD(x) ((x)->children[LEFT])
#define RIGHT_CHILD(x) ((x)->children[RIGHT])
#define GET_DATA(x) ((x)->data)
#define HEIGHT(x) ((x)->height)


typedef struct node node_t;


/*	utility functions	*/
static int CreateChild(node_t **node, void *data);
static int InsertChild(node_t *node, void *data, cmpfunc_t compar);

static ssize_t MaxHeight(node_t *left, node_t *right);

static void *Find(node_t *where, void *key,
				  int (*compar)(const void *lhs, const void *rhs));

static int ForEach(node_t *node, int (*action_func)(void *data, void *param),
			   	   void *param, int traversal_type);

static int Count(void *data, void *param);

static void CopyNode(node_t *dest, node_t *src);
static void RemoveRoot(avl_t *avl);
static void RemoveParentWithOneChild(node_t *node, cmpfunc_t compar);
static void RemoveParentWithTwoChildren(node_t *node, cmpfunc_t compar);
static void Remove(node_t *node, void *data, cmpfunc_t compar);
static node_t *GetLeftmost(node_t *node);

static void DestroyTree(node_t *node);

static int IsBalanced(node_t *node);
static void BalanceTree(avl_t *avl);
static void BalanceChild(node_t *node, node_t *child, int left_right);
static size_t AbsDiff(node_t *left, node_t *right);
/*	returns the new subtree root, 0 - left, 1 - right	*/
static node_t *Rotate(node_t *root, int left_right);


enum child_node_pos
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_CHILDREN = 2
};

struct node
{
	void *data;
	node_t *children[NUM_OF_CHILDREN];
	size_t height;
};

struct avl
{
    node_t *root;
    cmpfunc_t cmpfunc;
};


avl_t *AVLCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	avl_t *avl = (avl_t *)malloc(sizeof(avl_t));

	if (NULL == avl)
	{
		return NULL;
	}

	assert(cmp_func);

	avl->root = NULL;
	avl->cmpfunc = cmp_func;

	return (avl);
}

void AVLDestroy(avl_t *avl)
{
	assert(avl);

	if (!AVLIsEmpty(avl))
	{
		DestroyTree(avl->root);
	}

	free(avl);
	avl = NULL;
}

static void DestroyTree(node_t *node)
{
	if (NULL == node)
	{
		return;
	}

	DestroyTree(LEFT_CHILD(node));
	DestroyTree(RIGHT_CHILD(node));

	free(node);
	node = NULL;
}

size_t AVLSize(const avl_t *avl)
{
	size_t count = 0;
	assert(avl);

	ForEach(avl->root, Count, &count, PRE_ORDER);

	return (count);
}

ssize_t AVLHeight(const avl_t *avl)
{
	assert(avl);

	if (!AVLIsEmpty(avl))
	{
		return (HEIGHT(avl->root));
	}

	return (-1);
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);

	return (avl->root == NULL);
}

int AVLInsert(avl_t *avl, void *data)
{
	int res = 0;

	assert(avl);

	if (AVLIsEmpty(avl))
	{
		return (CreateChild(&avl->root, data));
	}

	res = InsertChild(avl->root, data, avl->cmpfunc);

	if (!IsBalanced(avl->root))
	{
		BalanceTree(avl);
	}

	return (res);
}

static int InsertChild(node_t *node, void *data, cmpfunc_t compar)
{
	int left_right = 0;	/*	0 - left, 1 - right	*/
	int res = 0;

	assert(node);
	assert(compar(data, GET_DATA(node)) != 0);

	left_right = compar(data, GET_DATA(node)) > 0;

	if (NULL == node->children[left_right])
	{
		res = CreateChild(&node->children[left_right], data);
		HEIGHT(node) += (node->children[!left_right] == NULL) * !res;
		return (res);
	}

	res = InsertChild(node->children[left_right], data, compar);
	HEIGHT(node) = MaxHeight(LEFT_CHILD(node), RIGHT_CHILD(node)) + 1;
	
	if (!IsBalanced(node->children[left_right]))
	{
		BalanceChild(node, node->children[left_right], left_right);
	}

	return (res);
}

 void AVLRemove(avl_t *avl, void *data)
{
	int left_right = 0;	/*	0 - left, 1 - right	*/

	assert(avl);
	assert(data);

	if (!Find(avl->root, data, avl->cmpfunc))
	{
		return;
	}

	if (avl->cmpfunc(data, GET_DATA(avl->root)) == 0)
	{
		RemoveRoot(avl);

		if (!IsBalanced(avl->root))
		{
			BalanceTree(avl);
		}

		return;
	}

	Remove(avl->root, data, avl->cmpfunc);
	HEIGHT(avl->root) = MaxHeight(LEFT_CHILD(avl->root),
								  RIGHT_CHILD(avl->root)) + 1;
	
	if (!IsBalanced(avl->root))
	{
		BalanceTree(avl);
	}

	if (!IsBalanced(LEFT_CHILD(avl->root)) || !IsBalanced(RIGHT_CHILD(avl->root)))
	{
		left_right = !IsBalanced(RIGHT_CHILD(avl->root));

		BalanceChild(avl->root, avl->root->children[left_right], left_right);
	}
}
 
static void Remove(node_t *node, void *data, cmpfunc_t compar)
{
	int left_right = 0;	/*	0 - left, 1 - right	*/
	node_t *to_remove = NULL;

	if (NULL == node)
	{
		return;
	}

	if (compar(data, GET_DATA(node)) == 0)
	{
		free(node);
		node = NULL;
		return;
	}

	left_right = compar(data, GET_DATA(node)) > 0;

	if (compar(data, GET_DATA(node->children[left_right])) == 0)
	{
		to_remove = node->children[left_right];

		if (HEIGHT(to_remove) == 0)
		{
			Remove(to_remove, data, compar);
			node->children[left_right] = NULL;
			HEIGHT(node) -= node->children[!left_right] == NULL;
			return;
		}
		
		if (NULL == LEFT_CHILD(to_remove) ||
			NULL == RIGHT_CHILD(to_remove))
		{
			RemoveParentWithOneChild(to_remove, compar);
			HEIGHT(node) = MaxHeight(LEFT_CHILD(node),
								 	 RIGHT_CHILD(node)) + 1;
			return;
		}

		RemoveParentWithTwoChildren(to_remove, compar);
		HEIGHT(node) = MaxHeight(LEFT_CHILD(node),
								 RIGHT_CHILD(node)) + 1;	
		return;
	}

	Remove(node->children[left_right], data, compar);
	HEIGHT(node) = MaxHeight(LEFT_CHILD(node),
							 RIGHT_CHILD(node)) + 1;
	
	if (!IsBalanced(node->children[left_right]))
	{
		BalanceChild(node, node->children[left_right], left_right);
	}
}

void *AVLFind(const avl_t *avl, void *key)
{
	assert(avl);
	assert(key);

	if (AVLIsEmpty(avl))
	{
		return NULL;
	}
	
	return (Find(avl->root, key, avl->cmpfunc));
}

static void *Find(node_t *where, void *key,
				  int (*compar)(const void *lhs, const void *rhs))
{
	int left_right = 0;	/*	0 - left, 1 - right	*/

	if (where == NULL)
	{
		return NULL;
	}
	
	if (compar(key, GET_DATA(where)) == 0)
	{
		return (GET_DATA(where));
	}

	left_right = compar(key, GET_DATA(where)) > 0;

	return (Find(where->children[left_right], key, compar));
}

int AVLForEach(avl_t *avl, int (*action_func)(void *data, void *param),
			   void *param, int traversal_type)
{
	assert(avl);
	assert(avl->root);
	assert(action_func);

	return (ForEach(avl->root, action_func, param, traversal_type));
}

static int ForEach(node_t *node, int (*action_func)(void *data, void *param),
				   void *param, int traversal_type)
{
	int res = 0;

	if (NULL == node)
	{
		return (0);
	}

	if (POST_ORDER == traversal_type)
	{
		res = ForEach(LEFT_CHILD(node), action_func, param, POST_ORDER);

		if (res)
		{
			return (res);
		}

		res = ForEach(RIGHT_CHILD(node), action_func, param, POST_ORDER);
		
		if (res)
		{
			return (res);
		}
		
		return (action_func(GET_DATA(node), param));
	}

	if (PRE_ORDER == traversal_type)
	{
		res = action_func(GET_DATA(node), param);

		if (res)
		{
			return (res);
		}

		res = ForEach(LEFT_CHILD(node), action_func, param, PRE_ORDER);

		if (res)
		{
			return (res);
		}

		return (ForEach(RIGHT_CHILD(node), action_func, param, PRE_ORDER));
	}

	if (IN_ORDER == traversal_type)
	{
		res = ForEach(LEFT_CHILD(node), action_func, param, IN_ORDER);

		if (res)
		{
			return (res);
		}

		res = action_func(GET_DATA(node), param);

		if (res)
		{
			return (res);
		}

		return (ForEach(RIGHT_CHILD(node), action_func, param, IN_ORDER));
	}
	
	return (0);
}

static int CreateChild(node_t **node, void *data)
{
	assert(node);

	*node = (node_t *)malloc(sizeof(node_t));

	if (NULL == node)
	{
		return (1);
	}

	GET_DATA(*node) = data;
	LEFT_CHILD(*node) = NULL;
	RIGHT_CHILD(*node) = NULL;
	HEIGHT(*node) = 0;

	return (0);
}

static void RemoveRoot(avl_t *avl)
{
	if (HEIGHT(avl->root) == 0)
	{
		free(avl->root);
		avl->root = NULL;
		return;
	}

	if ((NULL == LEFT_CHILD(avl->root)) ||
		 NULL == RIGHT_CHILD(avl->root))
	{
		RemoveParentWithOneChild(avl->root, avl->cmpfunc);
		return;
	}

	RemoveParentWithTwoChildren(avl->root, avl->cmpfunc);
	HEIGHT(avl->root) = MaxHeight(LEFT_CHILD(avl->root),
								  RIGHT_CHILD(avl->root)) + 1;
}

static void RemoveParentWithOneChild(node_t *node, cmpfunc_t compar)
{
	node_t *temp = NULL;
	int left_right = 0;	/*	0 - left, 1 - right	*/

	left_right = NULL != RIGHT_CHILD(node);
	temp = node->children[left_right];
	
	CopyNode(node, temp);
	
	Remove(temp, GET_DATA(temp), compar);
	HEIGHT(node) = MaxHeight(LEFT_CHILD(node),
							 RIGHT_CHILD(node)) + 1;
}

static void RemoveParentWithTwoChildren(node_t *node, cmpfunc_t compar)
{
	int has_left_child = 0;
	node_t *leftmost = NULL;
	node_t *temp = NULL;

	leftmost = GetLeftmost(RIGHT_CHILD(node));
	has_left_child = LEFT_CHILD(RIGHT_CHILD(node)) != NULL;
	temp = RIGHT_CHILD(leftmost);
	
	GET_DATA(node) = GET_DATA(leftmost);
	Remove(RIGHT_CHILD(node), GET_DATA(leftmost), compar);
	
	if (!has_left_child)
	{
		RIGHT_CHILD(node) = temp;
	}
	
	HEIGHT(node) = MaxHeight(LEFT_CHILD(node),
							 RIGHT_CHILD(node)) + 1;

	if (!IsBalanced(RIGHT_CHILD(node)))
	{
		BalanceChild(node, RIGHT_CHILD(node), RIGHT);
	}
}

static void CopyNode(node_t *dest, node_t *src)
{
	assert(dest);
	assert(src);

	GET_DATA(dest) = GET_DATA(src);
	LEFT_CHILD(dest) = LEFT_CHILD(src);
	RIGHT_CHILD(dest) = RIGHT_CHILD(src);
	HEIGHT(dest) = HEIGHT(src);
}

static node_t *GetLeftmost(node_t *node)
{
	if (NULL == LEFT_CHILD(node))
	{
		return (node);
	}

	return (GetLeftmost(LEFT_CHILD(node)));
}

static ssize_t MaxHeight(node_t *left, node_t *right)
{
	if (NULL == left && NULL == right)
	{
		return (-1);
	}
	
	if (NULL == left)
	{
		return (HEIGHT(right));
	}
	
	if (NULL == right)
	{
		return (HEIGHT(left));
	}

	return (HEIGHT(right) > HEIGHT(left) ?
			HEIGHT(right) : HEIGHT(left));
}

static int Count(void *data, void *param)
{
	(void)data;

	++*(size_t *)param;

	return (0);
}

static int IsBalanced(node_t *node)
{
	if (NULL == node)
	{
		return (1);
	}

	return (AbsDiff(LEFT_CHILD(node), RIGHT_CHILD(node)) <= 1);
}

static size_t AbsDiff(node_t *left, node_t *right)
{
	if (NULL == left && NULL == right)
	{
		return (0);
	}

	if (NULL == left)
	{
		return (HEIGHT(right) + 1);
	}

	if (NULL == right)
	{
		return (HEIGHT(left) + 1);
	}

	return (HEIGHT(left) > HEIGHT(right) ?
			HEIGHT(left) - HEIGHT(right) :
			HEIGHT(right) - HEIGHT(left));
}

static node_t *Rotate(node_t *root, int left_right)
{
	node_t *new_root = NULL;
	node_t *child = NULL;

	assert(root);

	new_root = root->children[!left_right];
	child = new_root->children[left_right];

	new_root->children[left_right] = root;
	root->children[!left_right] = child;

	HEIGHT(root) = MaxHeight(LEFT_CHILD(root),
							 RIGHT_CHILD(root)) + 1;

	HEIGHT(new_root) = MaxHeight(LEFT_CHILD(new_root),
								 RIGHT_CHILD(new_root)) + 1;

	return (new_root);
}

static void BalanceTree(avl_t *avl)
{
	int rot_left_right = 0;	/* 0 - left, 1 - right	*/
	int rot_left_right2 = 0;	/* 0 - left, 1 - right	*/
	node_t *child = NULL;

	if (NULL != LEFT_CHILD(avl->root))
	{
		rot_left_right = MaxHeight(LEFT_CHILD(avl->root), RIGHT_CHILD(avl->root))
						 == (ssize_t)HEIGHT(LEFT_CHILD(avl->root));
	}

	child = avl->root->children[!rot_left_right];
	
	rot_left_right2 = !rot_left_right;

	if (NULL != child->children[!rot_left_right2] &&
		MaxHeight(LEFT_CHILD(child), RIGHT_CHILD(child))
		== (ssize_t)HEIGHT(child->children[!rot_left_right2]))
	{
		avl->root->children[!rot_left_right] = Rotate(child, rot_left_right2);
	}

	avl->root = Rotate(avl->root, rot_left_right);
}

static void BalanceChild(node_t *node, node_t *child, int left_right)
{
	int rot_left_right = 0;	/* 0 - left, 1 - right	*/
	int rot_left_right2 = 0;	/* 0 - left, 1 - right	*/
	node_t *child2 = NULL;

	child = node->children[left_right];

	if (NULL != LEFT_CHILD(child))
	{
		rot_left_right = MaxHeight(LEFT_CHILD(child), RIGHT_CHILD(child))
						 == (ssize_t)HEIGHT(LEFT_CHILD(child));
	}

	child2 = child->children[!rot_left_right];

	rot_left_right2 = !rot_left_right;

	if (NULL != child2->children[!rot_left_right2] &&
		MaxHeight(LEFT_CHILD(child2), RIGHT_CHILD(child2))
		== (ssize_t)HEIGHT(child2->children[!rot_left_right2]))
	{
		child->children[!rot_left_right] = Rotate(child2, rot_left_right2);
	}
	
	node->children[left_right] = Rotate(child, rot_left_right);

	HEIGHT(node) = MaxHeight(LEFT_CHILD(node), RIGHT_CHILD(node)) + 1;
}