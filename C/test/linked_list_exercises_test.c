#include <stdio.h>
#include <stdlib.h>	/*	for malloc	*/

#include "linked_list_exercises.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"


struct node
{
	void *data;
	struct node *next;
};


void TestLinkedListExercises();


int main ()
{
	TestLinkedListExercises();

	return (0);
}


void TestLinkedListExercises()
{
	node_t *first = (node_t *)malloc(sizeof(node_t));
	node_t *second = (node_t *)malloc(sizeof(node_t));
	node_t *third = (node_t *)malloc(sizeof(node_t));
	node_t *fourth = (node_t *)malloc(sizeof(node_t));
	node_t *fifth = (node_t *)malloc(sizeof(node_t));
	node_t *first2 = (node_t *)malloc(sizeof(node_t));	
	node_t *second2 = (node_t *)malloc(sizeof(node_t));
	node_t *third2 = (node_t *)malloc(sizeof(node_t));
	node_t *iterator = NULL;
	int first_data = 1;
	int second_data = 2;	
	int third_data = 3;
	int fourth_data = 4;	
	int fifth_data = 5;	
	int first2_data = 21;
	int second2_data = 22;	
	int third2_data = 23;
	int failure = 0;
		
	first->data = &first_data;
	first->next = second;
	
	second->data = &second_data;
	second->next = third;
	
	third->data = &third_data;
	third->next = fourth;
	
	fourth->data = &fourth_data;
	fourth->next = fifth;
	
	fifth->data = &fifth_data;
	fifth->next = NULL;
	
	iterator = Flip(first);
	
	if (iterator != fifth ||
		iterator->next != fourth ||
		iterator->next->next != third ||
		iterator->next->next->next != second ||
		iterator->next->next->next->next != first)
	{
		printf("Flip - %s\n", FAILURE);
		
		printf("First data: %d and should be: 5\n", *(int *)iterator->data);
		printf("Second data: %d and should be: 4\n", *(int *)iterator->next->data);
		printf("Third data: %d and should be: 3\n", *(int *)iterator->next->next->data);
		printf("Fourth data: %d and should be: 2\n", *(int *)iterator->next->next->next->data);
		printf("Fifth data: %d and should be: 1\n", *(int *)iterator->next->next->next->next->data);
		
		failure = 1;
	}
	
	if (HasLoop(fifth))
	{
		printf("HasLoop - %s - function result is: %d and should be: 0\n", FAILURE, HasLoop(fifth));
		failure = 1;
	}
	
	first->next = fourth;

	if (!HasLoop(fifth))
	{
		printf("HasLoop - %s - function result is: %d and should be: TRUE\n", FAILURE, HasLoop(fifth));
		failure = 1; 
	}
	
	iterator = Flip(fifth);
	
	if (iterator)
	{
		printf("Flip - %s - before flip the list was: 5 4 3 2 1 4 3 2 1 4 etc and after:\n", FAILURE);
		printf("iterator->data: %d\n", *(int *)iterator->data);
		printf("iterator->next->data: %d\n", *(int *)iterator->next->data);
		printf("iterator->next->next->data: %d\n", *(int *)iterator->next->next->data);
		printf("iterator->next->next->next->data: %d\n", *(int *)iterator->next->next->next->data);
		printf("iterator->next->next->next->next->data: %d\n", *(int *)iterator->next->next->next->next->data);
		printf("iterator->next->next->next->next->next->data: %d\n", *(int *)iterator->next->next->next->next->next->data);
		printf("iterator-next->next->next->next->next->next->data: %d\n", *(int *)iterator->next->next->next->next->next->next->data);
		printf("iterator-next->next->next->next->next->next->next->data: %d\n", *(int *)iterator->next->next->next->next->next->next->next->data);
		failure = 1;		
	}

	first->next = NULL;

	iterator = Flip(fifth);	

	first2->data = &first2_data;
	first2->next = second2;
	
	second2->data = &second2_data;
	second2->next = third2;
	
	third2->data = &third2_data;
	third2->next = fourth;
	
	
	if (FindIntersection(first, first2) != fourth)
	{
		printf("FindIntersection - %s\n", FAILURE);
		failure = 1;
	}
	
	third2->next = NULL;
	
	if (FindIntersection(first, first2))
	{
		printf("FindIntersection - %s\n", FAILURE);
		failure = 1;	
	}

	third2->next = first2;
	
	if (FindIntersection(first, first2))
	{
		printf("FindIntersection - %s\n", FAILURE);
		failure = 1;	
	}	
	
	
	if (0 == failure)
	{
		printf("%s\n", SUCCESS);
	}
	
	free(first);
	free(second);
	free(third);
	free(fourth);
	free(fifth);
	free(first2);
	free(second2);
	free(third2);
}
