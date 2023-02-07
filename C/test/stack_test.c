#include <stdio.h>
#include <string.h>	/*	for strcmp	*/
#include <stdlib.h>	/* for malloc	*/


#include "stack.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int TestStack();

int main ()
{
	TestStack();
	printf("\n");
	
						
	return (0);
}

int TestStack()
{
	stack_t *stack;
	int new_element = 0;
	char char_element[6] = {'\0'};
	float f_element = 0;
	
/********************************* stack number 1	*********************************/
	printf("***********stack number 1 (int)***********\n\n");
	
	stack = StackCreate(3, 4);

	if (NULL == stack)
	{
		printf("StackCreate - %s\n", FAILURE);
		return (-1);
	}
	
	/*push element 1	*/
	new_element = 280;
	StackPush(stack, &new_element);
	
	printf("new element 1 is %d\n", *(int *)StackPeek(stack));

	/*push element 2	*/
	new_element = 500;
	StackPush(stack, &new_element);
	
	printf("new element 2 is %d\n", *(int *)StackPeek(stack));

	printf("StackSize is: %lu\n", StackSize(stack));

	printf("StackIsEmpty is: %d\n", StackIsEmpty(stack));

	printf("StackCapacity is: %ld\n", StackCapacity(stack));
	
	StackPop(stack);
	
	printf("StackSize after 1 time pop is: %lu\n", StackSize(stack));	

	printf("Peek element after 1 time pop is %d\n", *(int *)StackPeek(stack));

	StackDestroy(stack);
	
	printf("\n");
	
/********************************* stack number 2	*********************************/
	printf("***********stack number 2 (strings)***********\n\n");
	
	stack = StackCreate(3, 6);

	if (NULL == stack)
	{
		printf("StackCreate - %s\n", FAILURE);
		return (-1);
	}
	
	/*push element 1	*/
	strcpy(char_element, "batel");
	
	StackPush(stack, char_element);
	
	printf("new element 1 is \"%s\"\n", (char *)StackPeek(stack));

	/*push element 2	*/
	strcpy(char_element,"levi");
	
	StackPush(stack, char_element);
	
	printf("new element 2 is \"%s\"\n", (char *)StackPeek(stack));

	printf("StackSize is: %lu\n", StackSize(stack));

	printf("StackIsEmpty is: %d\n", StackIsEmpty(stack));

	printf("StackCapacity is: %ld\n", StackCapacity(stack));
	
	StackPop(stack);
	
	printf("StackSize after 1 time pop is: %lu\n", StackSize(stack));	

	printf("Peek element after 1 time pop is \"%s\"\n", (char *)StackPeek(stack));

	StackDestroy(stack);

	printf("\n");
	
/********************************* stack number 3	*********************************/
	printf("***********stack number 3 (float)***********\n\n");
	
	stack = StackCreate(3, 4);

	if (NULL == stack)
	{
		printf("StackCreate - %s\n", FAILURE);
		return (-1);
	}
	
	/*push element 1	*/
	f_element = 2.8;
	StackPush(stack, &f_element);
	
	printf("new element 1 is %f\n", *(float *)StackPeek(stack));

	/*push element 2	*/
	f_element = 5.5;
	StackPush(stack, &f_element);
	
	printf("new element 2 is %f\n", *(float *)StackPeek(stack));

	printf("StackSize is: %lu\n", StackSize(stack));

	printf("StackIsEmpty is: %d\n", StackIsEmpty(stack));

	printf("StackCapacity is: %ld\n", StackCapacity(stack));
	
	StackPop(stack);
	
	printf("StackSize after 1 time pop is: %lu\n", StackSize(stack));	

	printf("Peek element after 1 time pop is %f\n", *(float *)StackPeek(stack));

	StackDestroy(stack);
	
	printf("\n");

	return (0);
	
}
