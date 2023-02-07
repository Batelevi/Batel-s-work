#include <stdio.h>
#include <string.h>	/*	for strcmp	*/
#include <stdlib.h>	/* for malloc	*/


#include "dynamic_vector.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int TestVector();

int main ()
{
	TestVector();
	printf("\n");
	
						
	return (0);
}

int TestVector()
{
	vector_t *vector;
	int new_element = 0;
	char char_element[6] = {'\0'};
	float f_element = 0;
	int failure1 = 0;
	int failure2 = 0;
	int failure3 = 0;
	
/********************************* vector number 1	*********************************/
	printf("***********vector number 1 (int)***********\n\n");
	
	vector = VectorCreate(3, 4);

	if (NULL == vector)
	{
		printf("vectorCreate - %s\n", FAILURE);
		return (-1);
	}
	
	/*push element 1	*/
	new_element = 280;
	VectorPushBack(vector, &new_element);

	if (*(int *)VectorGetAccessToElement(vector, 0) != new_element)
	{
		printf("VectorPushBack or VectorGetAccessToElement - %s - new element 1 is %d and should be: %d\n", FAILURE, *(int *)VectorGetAccessToElement(vector, 0), new_element);
		failure1 = 1;
	}
	
	/*push element 2	*/
	new_element = 500;
	VectorPushBack(vector, &new_element);

	if (*(int *)VectorGetAccessToElement(vector, 1) != new_element)
	{
		printf("VectorPushBack or VectorGetAccessToElement - %s - new element 2 is %d and should be: %d\n", FAILURE, new_element, *(int *)VectorGetAccessToElement(vector, 1));
		failure1 = 1;
	}
	
	if (VectorSize(vector) != 2)
	{
		printf("VectorSize - %s - vector size is: %lu and should be: 2\n", FAILURE, VectorSize(vector));
		failure1 = 1;
	}
	
	if (0 != VectorIsEmpty(vector))
	{
		printf("VectorIsEmpty - %s - result is: %d and should be: 0\n", FAILURE, VectorIsEmpty(vector));
		failure1 = 1;
	}
	
	if (3 != VectorCapacity(vector))
	{
		printf("VectorCapacity - %s - capcity is: %ld and should be: 3\n", FAILURE, VectorCapacity(vector));
		failure1 = 1;
	}
	
	/*push element 3 and 4	*/
	new_element = 600;
	VectorPushBack(vector, &new_element);
	
	new_element = 700;
	VectorPushBack(vector, &new_element);

	if (6 != VectorCapacity(vector))
	{
		printf("VectorCapacity - %s - capcity is: %ld and should be: 6\n", FAILURE, VectorCapacity(vector));
		failure1 = 1;
	}	
		
	VectorPopBack(vector);
	
	if (3 != VectorSize(vector))
	{
		printf("VectorPopBack or VectorSize - %s - size is: %lu and should be: 3\n", FAILURE, VectorSize(vector));
		failure1 = 1;	
	}
	
	VectorShrink(vector);
	
	if (3 != VectorCapacity(vector))
	{
		printf("VectorShrink - %s - capcity is: %ld and should be: 3\n", FAILURE, VectorCapacity(vector));
		failure1 = 1;
	}

	VectorPushBack(vector, &new_element);
	
	VectorReserve(vector, 7);

	if (7 != VectorCapacity(vector))
	{
		printf("VectorShrink - %s - capcity is: %ld and should be: 7\n", FAILURE, VectorCapacity(vector));
		failure1 = 1;
	}	
		
	VectorDestroy(vector);
	
	if (0 == failure1)
	{
		printf("Vector int - %s\n", SUCCESS);
	}
	
	printf("\n");
	
/********************************* vector number 2	*********************************/
	printf("***********vector number 2 (string)***********\n\n");
	
	vector = VectorCreate(3, 6);

	if (NULL == vector)
	{
		printf("vectorCreate - %s\n", FAILURE);
		return (-1);
	}
	
	/*push element 1	*/
	strcpy(char_element, "batel");
	
	VectorPushBack(vector, char_element);
	
	if (0 != strcmp((char *)VectorGetAccessToElement(vector, 0), char_element))
	{
		printf("VectorPushBack or VectorGetAccessToElement - %s - new element 1 is %s and should be: %s\n", FAILURE, (char *)VectorGetAccessToElement(vector, 0), char_element);
		failure2 = 1;
	}
	
	/*push element 2	*/
	strcpy(char_element,"levi");
	
	VectorPushBack(vector, char_element);
	
	if (0 != strcmp((char *)VectorGetAccessToElement(vector, 1), char_element))
	{
		printf("VectorPushBack or VectorGetAccessToElement - %s - new element 1 is %s and should be: %s\n", FAILURE, (char *)VectorGetAccessToElement(vector, 1), char_element);
		failure2 = 1;
	}

	if (VectorSize(vector) != 2)
	{
		printf("VectorSize - %s - vector size is: %lu and should be: 2\n", FAILURE, VectorSize(vector));
		failure2 = 1;
	}

	if (0 != VectorIsEmpty(vector))
	{
		printf("VectorIsEmpty - %s - result is: %d and should be: 0\n", FAILURE, VectorIsEmpty(vector));
		failure2 = 1;
	}
	
	if (3 != VectorCapacity(vector))
	{
		printf("VectorCapacity - %s - capcity is: %ld and should be: 3\n", FAILURE, VectorCapacity(vector));
		failure2 = 1;
	}

	VectorPopBack(vector);
		
	if (1 != VectorSize(vector))
	{
		printf("VectorPopBack or VectorSize - %s - size is: %lu and should be: 1\n", FAILURE, VectorSize(vector));
		failure2 = 1;	
	}

	VectorShrink(vector);

	if (1 != VectorCapacity(vector))
	{
		printf("VectorShrink - %s - capcity is: %ld and should be: 1\n", FAILURE, VectorCapacity(vector));
		failure2 = 1;
	}

	VectorReserve(vector, 6);

	if (6 != VectorCapacity(vector))
	{
		printf("VectorShrink - %s - capcity is: %ld and should be: 6\n", FAILURE, VectorCapacity(vector));
		failure2 = 1;
	}	
			
	VectorDestroy(vector);
	
	if (0 == failure2)
	{
		printf("Vector string - %s\n", SUCCESS);
	}

	printf("\n");
	
/********************************* vector number 3	*********************************/
	printf("***********vector number 3 (float)***********\n\n");
	
	vector = VectorCreate(3, 4);

	if (NULL == vector)
	{
		printf("vectorCreate - %s\n", FAILURE);
		return (-1);
	}
	
	/*push element 1	*/
	f_element = 2.8;
	VectorPushBack(vector, &f_element);

	if (*(float *)VectorGetAccessToElement(vector, 0) != f_element)
	{
		printf("VectorPushBack or VectorGetAccessToElement - %s - new element 1 is %f and should be: %f\n", FAILURE, *(float *)VectorGetAccessToElement(vector, 0), f_element);
		failure3 = 1;
	}
	
	/*push element 2	*/
	f_element = 5.5;
	VectorPushBack(vector, &f_element);
	
	if (*(float *)VectorGetAccessToElement(vector, 1) != f_element)
	{
		printf("VectorPushBack or VectorGetAccessToElement - %s - new element 2 is %f and should be: %f\n", FAILURE, f_element, *(float *)VectorGetAccessToElement(vector, 1));
		failure3 = 1;
	}
	
	if (VectorSize(vector) != 2)
	{
		printf("VectorSize - %s - vector size is: %lu and should be: 2\n", FAILURE, VectorSize(vector));
		failure3 = 1;
	}
	
	if (0 != VectorIsEmpty(vector))
	{
		printf("VectorIsEmpty - %s - result is: %d and should be: 0\n", FAILURE, VectorIsEmpty(vector));
		failure3 = 1;
	}
	
	if (3 != VectorCapacity(vector))
	{
		printf("VectorCapacity - %s - capcity is: %ld and should be: 3\n", FAILURE, VectorCapacity(vector));
		failure3 = 1;
	}
	VectorPopBack(vector);
	
	if (VectorSize(vector) != 1)
	{
		printf("VectorSize - %s - vector size is: %lu and should be: 1\n", FAILURE, VectorSize(vector));
		failure3 = 1;
	}

	VectorShrink(vector);

	if (1 != VectorCapacity(vector))
	{
		printf("VectorShrink - %s - capcity is: %ld and should be: 1\n", FAILURE, VectorCapacity(vector));
		failure3 = 1;
	}
	
	VectorReserve(vector, 6);

	if (6 != VectorCapacity(vector))
	{
		printf("VectorShrink - %s - capcity is: %ld and should be: 6\n", FAILURE, VectorCapacity(vector));
		failure3 = 1;
	}	
	
	VectorDestroy(vector);
	
	if (0 == failure3)
	{
		printf("Vector float - %s\n", SUCCESS);
	}

	printf("\n");

	return (0);
}
