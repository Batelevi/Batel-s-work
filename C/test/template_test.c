#include <stdio.h>

#include "___.h"	/*	header file	*/

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

int failure = 0;

void Test___();
void PrintError(char *name, int line ,double function_result ,double should_be);


int main ()
{
	Test___();
	
	return (0);
}


void Test___()
{
	PrintError("", __LINE__, ___, ___);
	
	
	
	if (0 == failure)
	{
		printf("___ - %s\n", SUCCESS);
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
