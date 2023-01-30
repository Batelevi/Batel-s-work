#include <stdio.h>

#include "queue.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"


void TestQueue();

int main ()
{
	TestQueue();
	
	return (0);
}

void TestQueue()
{
	queue_t *queue = QueueCreate();
	queue_t *queue2 = QueueCreate();
	int a1 = 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	int b1 = 1;
	int b2 = 2;
	int failure = 0;
	
	if (NULL == queue)
	{
		printf("QueueCreate - %s - in line: %d\n", FAILURE, __LINE__);	
	}
	
	if (0 != QueueEnqueue(queue, &a1))
	{
		printf("QueueEnqueue - %s - in line: %d\n",FAILURE, __LINE__);
		failure = 1;
	}
		
	if (*(int *)QueuePeek(queue) != a1)
	{
		printf("QueueEnqueue or QueuePeek - %s - in line: %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	QueueEnqueue(queue, &a2);

	if (*(int *)QueuePeek(queue) != a1)
	{
		printf("QueueEnqueue or QueuePeek - %s - in line: %d\n", FAILURE, __LINE__);
		failure = 1;
	}

	if (2 != QueueSize(queue))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 2);
		failure = 1;
	}
	
	if (QueueIsEmpty(queue))
	{
		printf("QueueIsEmpty - %s - in line: %d - function result is: %d and should be: 0\n", FAILURE, __LINE__, QueueIsEmpty(queue));
		failure = 1;
	}
	
	QueueEnqueue(queue, &a3);
	
	if (3 != QueueSize(queue))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 3);
		failure = 1;
	}

	QueueEnqueue(queue, &a4);
	
	if (4 != QueueSize(queue))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 4);
		failure = 1;
	}

	QueueDequeue(queue);
	
	if (*(int *)QueuePeek(queue) != a2)
	{
		printf("QueueDequeue or QueuePeek - %s - in line: %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	if (3 != QueueSize(queue))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 3);
		failure = 1;
	}	

	QueueDequeue(queue);
	
	if (*(int *)QueuePeek(queue) != a3)
	{
		printf("QueueDequeue or QueuePeek - %s - in line: %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	if (2 != QueueSize(queue))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 2);
		failure = 1;
	}	

	QueueEnqueue(queue2, &b1);
	QueueEnqueue(queue2, &b2);
	
	if (*(int *)QueuePeek(queue2) != b1)
	{
		printf("QueueDequeue or QueuePeek - %s - in line: %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	QueueAppend(queue, queue2);

	if (*(int *)QueuePeek(queue) != a3)
	{
		printf("QueueDequeue or QueuePeek - %s - in line: %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	if (4 != QueueSize(queue))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 4);
		failure = 1;
	}	

	QueueDequeue(queue);
	QueueDequeue(queue);
	
	if (*(int *)QueuePeek(queue) != b1)
	{
		printf("QueueDequeue or QueuePeek - %s - in line: %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	if (2 != QueueSize(queue))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 2);
		failure = 1;
	}	
	
	QueueDequeue(queue);
	
	if (*(int *)QueuePeek(queue) != b2)
	{
		printf("QueueDequeue or QueuePeek - %s - in line: %d\n", FAILURE, __LINE__);
		failure = 1;
	}
	
	if (1 != QueueSize(queue))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 2);
		failure = 1;
	}	
	
	QueueEnqueue(queue2, &b1);
	QueueEnqueue(queue2, &b2);	
	
	if (2 != QueueSize(queue2))
	{
		printf("QueueSize - %s - in line: %d - function result is: %ld and should be: %d\n", FAILURE, __LINE__, QueueSize(queue), 2);
		failure = 1;
	}	
	
	QueueDestroy(queue);
	QueueDestroy(queue2);
	
	if (0 == failure)
	{
		printf("Queue - %s\n", SUCCESS);
	}	
}
