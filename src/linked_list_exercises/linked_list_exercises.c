/*********************************************
* Developer:      Batel Levi                 *
* Reviewer:       Aviv                       * 
**********************************************/

#include <assert.h>	/*	for assert	*/
#include <stddef.h>	/*	for NULL	*/

#include "linked_list_exercises.h"	/*	header file	*/


struct node
{
	void *data;
	struct node *next;
};


node_t *Flip(node_t *head)
{
	node_t *previous = NULL;
	node_t *current = NULL;
	node_t *next = NULL;
	
	assert(head);
	
	current = head;
	
	if (!HasLoop(head))
	{
		while (NULL != current)
		{
			next = current->next;
			current->next = previous;
			previous = current;
			current = next;
		}
	}
		
	return (previous);
}

int HasLoop(const node_t *head)
{
	node_t *slow_p = NULL;
	node_t *fast_p = NULL;
	
	assert(head);
	
	slow_p = (node_t *)head;
	fast_p = (node_t *)head;
	
	while (NULL != slow_p && NULL != fast_p && NULL != fast_p->next)
	{
		slow_p = slow_p->next;
		fast_p = fast_p->next->next;
		
		if (slow_p == fast_p)
		{
			return (1);
		}
	}
	
	return (0);
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *temp_1 = NULL;
	node_t *temp_2 = NULL;

	assert(head_1);
	assert(head_2);
	
	temp_1 = head_1;
	temp_2 = head_2;
	
	if (HasLoop(head_1) || HasLoop(head_2))
	{
		return NULL;
	}
	
	while (temp_1 != temp_2)
	{
		temp_1 = temp_1->next;
		temp_2 = temp_2->next;
		
		if (temp_1 == temp_2)
		{
			return (temp_1);
		}
		
		if (NULL == temp_1)
		{
			temp_1 = head_2;
		}
		
		if (NULL == temp_2)
		{
			temp_2 = head_1;
		}
	}
	
	return (temp_1);
}
