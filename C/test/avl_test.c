#include <stdio.h>
#include <assert.h>	/*	for assert	*/

#include "avl.h"	/*	header file	*/

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

#define LEFT_CHILD(x) ((x)->children[LEFT])
#define RIGHT_CHILD(x) ((x)->children[RIGHT])
#define HEIGHT(x) ((x)->height)

int failure = 0;

void TestAvl();
void PrintError(char *name, int line ,long int function_result ,long int should_be, avl_t *avl);

int Compar(const void *n1, const void *n2);
int PrintTree(void *data, void *param);

typedef struct node node_t;

static int IsBalancedTree(node_t *node);
static size_t AbsDiff(node_t *left, node_t *right);
void print2DUtil(node_t* root, int space);

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

int main ()
{
	TestAvl();
	
	return (0);
}


void TestAvl()
{
	avl_t *avl = AVLCreate(Compar);
	int a10 = 10;
	int a15 = 15;
	int a7 = 7;
	int a5 = 5;
	int a3 = 3;
	int a6 = 6;
	int a14 = 14;
	int a12 = 12;
	int a11 = 11;
	int a13 = 13;

	PrintError("AVLCreate", __LINE__, !avl, 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 1, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), -1, avl);


	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a10), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a10), a10, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 0, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 1, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a15), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a15), a15, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 1, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 2, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a7), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a7), a7, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 1, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 3, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a5), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a5), a5, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 4, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a3), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a3), a3, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 5, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a6), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a6), a6, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 6, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a14), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a14), a14, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 7, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a12), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a12), a12, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 8, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a11), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a11), a11, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 9, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a14);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a14), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 8, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a5);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a5), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 7, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a3);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a3), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 6, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a10);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a10), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 5, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a7);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a7), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 4, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a15);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a15), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 1, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 3, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	/* only 12 as root and 6 as its left child are left	*/

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a15), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a15), a15, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 4, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a7), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a7), a7, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 5, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a10), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a10), a10, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 6, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);
	
	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a3), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a3), a3, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 7, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a5), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a5), a5, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 8, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a14), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a14), a14, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 9, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a13), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a13), a13, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 10, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);


	AVLRemove(avl, &a10);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a10), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 9, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a3);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a3), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 8, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a12);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a12), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 7, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	PrintError("AVLInsert", __LINE__, AVLInsert(avl, &a12), 0, avl);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a12), a12, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 8, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a11);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a11), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 7, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLDestroy(avl);
	avl = AVLCreate(Compar);

	AVLInsert(avl, &a3);
	AVLInsert(avl, &a5);
	AVLInsert(avl, &a6);
	AVLInsert(avl, &a7);
	AVLInsert(avl, &a10);
	AVLInsert(avl, &a11);
	AVLInsert(avl, &a12);
	AVLInsert(avl, &a13);
	AVLInsert(avl, &a14);
	AVLInsert(avl, &a15);

	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a15), a15, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 10, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a7);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a7), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 9, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a10);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a10), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 8, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a11);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a11), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 7, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a14);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a14), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 6, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a12);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a12), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 5, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a6);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a6), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 2, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 4, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a13);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a13), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 1, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 3, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a5);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a5), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 1, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 2, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a15);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a15), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 0, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 1, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLRemove(avl, &a3);
	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 1, avl);
	PrintError("AVLFind", __LINE__, (size_t)AVLFind(avl, &a3), 0, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), -1, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 0, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);

	AVLInsert(avl, &a15);
	AVLInsert(avl, &a14);
	AVLInsert(avl, &a13);
	AVLInsert(avl, &a12);
	AVLInsert(avl, &a11);
	AVLInsert(avl, &a10);
	AVLInsert(avl, &a7);
	AVLInsert(avl, &a6);
	AVLInsert(avl, &a5);
	AVLInsert(avl, &a3);

	PrintError("AVLIsEmpty", __LINE__, AVLIsEmpty(avl), 0, avl);
	PrintError("AVLFind", __LINE__, *(int *)AVLFind(avl, &a15), a15, avl);
	PrintError("AVLHeight", __LINE__, AVLHeight(avl), 3, avl);
	PrintError("AVLSize", __LINE__, AVLSize(avl), 10, avl);
	PrintError("Is Balanced", __LINE__, IsBalancedTree(avl->root), 1, avl);


	/*AVLForEach(avl, PrintTree, NULL, IN_ORDER);*/

	if (0 == failure)
	{
		print2DUtil(avl->root, 0);
		printf("AVL - %s\n", SUCCESS);
	}
	
	AVLDestroy(avl);
}


void PrintError(char *name, int line ,long int function_result ,long int should_be, avl_t *avl)
{
	if (function_result != should_be)
	{
		printf("%s - %s - in line %d - function result is: %ld and should be: %ld\n", name, FAILURE, line, function_result, should_be);
		failure = 1;
		print2DUtil(avl->root, 0);
	}
}

int Compar(const void *n1, const void *n2)
{
	assert(n1);
	assert(n2);

	return ((*(int *)n1 > *(int *)n2) - (*(int *)n1 < *(int *)n2));
}

int PrintTree(void *data, void *param)
{
	(void)param;

	printf("%d ", *(int *)data);

	return (0);
}

void print2DUtil(node_t* root, int space)
{
    int i = 10;

    if (root == NULL)
    return;

    space += 10;

    print2DUtil(root->children[RIGHT], space);

    printf("\n");
    for (i = 10; i < space; i++)
    {
        printf(" ");
    }

    printf("%d\n", *(int *)root->data);

    print2DUtil(root->children[LEFT], space);
} 

static int IsBalancedTree(node_t *node)
{
	if (NULL == node)
	{
		return (1);
	}

	if (AbsDiff(LEFT_CHILD(node), RIGHT_CHILD(node)) > 1)
	{
		return (0);
	}

	if (!IsBalancedTree(LEFT_CHILD(node)))
	{
		return (0);
	}

	if (!IsBalancedTree(RIGHT_CHILD(node)))
	{
		return (0);
	}

	return (1);
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