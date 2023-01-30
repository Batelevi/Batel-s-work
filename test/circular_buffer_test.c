#include <stdio.h>

#include "circular_buffer.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"


void TestCircularBuffer();

int main ()
{
	TestCircularBuffer();
	
	return (0);
}

void TestCircularBuffer()
{
	circular_buffer_t *buff = NULL;
	size_t capacity = 16;
	size_t size = 0;
	int num = 0;
	int num2 = 0;
	int num3 = 0;
	size_t num4 = 0;
	size_t bytes = 0;
	int failure = 0;
	
	buff = CBufferCreate(capacity);
	
	if (NULL == buff)
	{
		printf("CBufferCreate - %s - in line %d - function returns NULL\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	if (CBufferFreeSpace(buff) != capacity)
	{
		printf("CBufferCreate or CBufferFreeSpace - %s - in line %d - free space should be: %lu and function result is: %lu\n", FAILURE, __LINE__, capacity, CBufferFreeSpace(buff));
		failure = 1;	
	}

	if (CBuffersiz(buff) != 0)
	{
		printf("CBuffersiz - %s - in line %d - function result should be: %d and function result is: %lu\n", FAILURE, __LINE__, 0, CBuffersiz(buff));
		failure = 1;	
	}

	if (!CBufferIsEmpty(buff))
	{
		printf("CBufferIsEmpty - %s - in line %d - function result should be: TRUE and function result is: %d\n", FAILURE, __LINE__, CBufferIsEmpty(buff));
		failure = 1;	
	}


	num = 280;
	num2 = 0;
	
	CBufferWrite(buff, &num, 4);

	size += 4;
	if (CBuffersiz(buff) != size)
	{
		printf("CBuffersiz - %s - in line %d - function result should be: %lu and function result is: %lu\n", FAILURE, __LINE__, size, CBuffersiz(buff));
		failure = 1;
	}
	
	CBufferRead(buff, &num2, 4);

	size -= 4;
	if (CBuffersiz(buff) != size)
	{
		printf("CBuffersiz - %s - in line %d - function result should be: %lu and function result is: %lu\n", FAILURE, __LINE__, size, CBuffersiz(buff));
		failure = 1;	
	}
		
	if (num != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num, num2);
		failure = 1;
	}

	num = 30;
	num2 = 0;
	
	CBufferWrite(buff, &num, 4);

	size += 4;

	CBufferRead(buff, &num2, 4);

	size -= 4;

	if (num != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num, num2);
		failure = 1;
	}

	num = 500;
	num2 = 0;
	num3 = 600;
	
	CBufferWrite(buff, &num, 4);
	CBufferWrite(buff, &num3, 4);

	size += 4;
	size += 4;
	
	if (CBuffersiz(buff) != size)
	{
		printf("CBuffersiz - %s - in line %d - function result should be: %lu and function result is: %lu\n", FAILURE, __LINE__, size, CBuffersiz(buff));
		failure = 1;
	}
		
	CBufferRead(buff, &num2, 4);

	size -= 4;

	if (num != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num, num2);
		failure = 1;
	}

	num2 = 0;
	
	CBufferRead(buff, &num2, 4);

	size -= 4;
	
	if (CBuffersiz(buff) != size)
	{
		printf("CBuffersiz - %s - in line %d - function result should be: %lu and function result is: %lu\n", FAILURE, __LINE__, size, CBuffersiz(buff));
		failure = 1;
	}
	
	if (num3 != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num3, num2);
		failure = 1;
	}
	
	num = 500;
	num2 = 0;
	num3 = 600;
	
	CBufferWrite(buff, &num, 4);
	CBufferWrite(buff, &num3, 4);
	
	size += 4;
	size += 4;
	
	CBufferRead(buff, &num2, 4);
	
	size -= 4;
		
	if (num != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num, num2);
		failure = 1;
	}

	num2 = 0;
	
	CBufferRead(buff, &num2, 4);

	size -= 4;
		
	if (num3 != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num3, num2);
		failure = 1;
	}

	num = 500;
	num2 = 0;
	num3 = 600;
	
	CBufferWrite(buff, &num, 4);
	CBufferWrite(buff, &num3, 4);

	size += 4;
	size += 4;
		
	CBufferRead(buff, &num2, 4);

	size -= 4;
		
	if (num != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num, num2);
		failure = 1;
	}

	num2 = 0;
	
	CBufferRead(buff, &num2, 4);

	size -= 4;	

	if (num3 != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num3, num2);
		failure = 1;
	}

	/* size == 0	*/
	
	num = 500;
	num2 = 0;
	num3 = 600;
	
	CBufferWrite(buff, &num, 4);
	CBufferWrite(buff, &num3, 4);
	CBufferWrite(buff, &num, 4);
	CBufferWrite(buff, &num, 4);
	CBufferWrite(buff, &num, 4);

	size += 4 * 4;

	if (CBuffersiz(buff) != size)
	{
		printf("CBuffersiz - %s - in line %d - function result should be: %lu and function result is: %lu\n", FAILURE, __LINE__, size, CBuffersiz(buff));
		failure = 1;
	}
			
	CBufferRead(buff, &num2, 4);

	size -= 4;	
		
	if (num != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num, num2);
		failure = 1;
	}

	if (CBufferFreeSpace(buff) != capacity - size)
	{
		printf("CBufferFreeSpace - %s - in line %d - function result should be: %lu and function result is: %lu\n", FAILURE, __LINE__, capacity - size, CBufferFreeSpace(buff));
		failure = 1;
	}

	num2 = 0;

	/* size == 12 (remaining to write: 4)	*/
	
	num4 = 50;
	
	bytes = CBufferWrite(buff, &num4, 8);
	
	if (bytes != 4)
	{
		printf("CBufferWrite - %s - in line %d - function result should be: %d and function result is: %lu\n", FAILURE, __LINE__, 4, bytes);
		failure = 1;
	}

	size += 4;	
		
	CBufferRead(buff, &num2, 4);
	
	size -= 4;
		
	if (num3 != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num3, num2);
		failure = 1;
	}

	CBufferRead(buff, &num2, 4);
	
	if (num != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num, num2);
		failure = 1;
	}	

	CBufferRead(buff, &num2, 4);
	
	if (num != num2)
	{
		printf("CBufferWrite or CBufferRead - %s - in line %d - function result should be: %d and function result is: %d\n", FAILURE, __LINE__, num, num2);
		failure = 1;
	}	
		
	CBufferDestroy(buff);

	if (0 == failure)
	{
		printf("Circular Buffer - %s\n", SUCCESS);
	}
}
