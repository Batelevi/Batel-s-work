#include <stdio.h>

#include "fsq.h"	/*	header file	*/

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int failure = 0;

void TestFSQ();
void PrintError(char *name, int line ,double function_result ,double should_be);


int main ()
{
	TestFSQ();
	
	return (0);
}


void TestFSQ()
{
	fsq_t *fsq = FSQCreate(10);

	PrintError("FSQCreate", __LINE__, !fsq, 0);
	PrintError("FSQCapacity", __LINE__, FSQCapacity(fsq), 10);
	PrintError("FSQIsEmpty", __LINE__, FSQIsEmpty(fsq), 1);
	PrintError("FSQSize", __LINE__, FSQSize(fsq), 0);


	if (0 == failure)
	{
		printf("FSQ - %s\n", SUCCESS);
	}
}


void PrintError(char *name, int line ,double function_result ,double should_be)
{
	if (function_result != should_be)
	{
		printf("%s - %s - in line %d - function result is: %.2f and should be: %.2f\n", name, FAILURE, line, function_result, should_be);
		failure = 1;
	}
}
