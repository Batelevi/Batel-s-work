#include <stdio.h>
#include <stdlib.h>	/* for malloc	*/
#include <string.h>	/*	for strcmp	*/

#include "singly_linked_list.h"	/*	header file	*/


#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"


int TestSinglyLinkedList();
int IsNumMatch(const void *data, void *criteria);
int AddNum(void *data, void *param);


int main ()
{
	TestSinglyLinkedList();
	printf("\n");
	
						
	return (0);
}

int TestSinglyLinkedList()
{
	list_t *list = NULL;
	list_iterator_t iterator = NULL;
	char *s = "batel";
	int n = 280;
	float f = 5.5555;
	int failure = 0;
	is_match_function_t is_num_match = IsNumMatch;
	action_function_t add_num = AddNum;
	float add = 1;
	float f2 = 280;
	float f3 = 5.5555 + add;
	float f4 = 780.5;
	
	list = ListCreate();
	
	if (0 != ListSize(list))
	{
		printf("ListCreate or ListSize - %s, size is: %ld and should be: 0\n", FAILURE, ListSize(list));
		failure = 1;
	}
	
	if (!ListIsEmpty(list))
	{
		printf("ListIsEmpty - %s, size is: %ld and should be: 0\n", FAILURE, ListSize(list));
		failure = 1;
	}	
	
	iterator = ListHead(list);

	iterator = ListInsert(s, iterator);	/* head - s "batel"	*/
	
	if (0 != strcmp(s, (char *)ListGetData(iterator)))
	{
		printf("ListInsert - %s - iterator is: %s and should be: %s\n", FAILURE, (char *)ListGetData(iterator), s);
		failure = 1;
	}
	
	if (1 != ListSize(list))
	{
		printf("ListHead or ListInsert or ListSize - %s, size is: %ld and should be: 1\n", FAILURE, ListSize(list));
		failure = 1;
	}

	if (ListIsEmpty(list))
	{
		printf("ListIsEmpty - %s, size is: %ld and should be: 0\n", FAILURE, ListSize(list));
		failure = 1;
	}	
	
		
	iterator = ListInsert(&n, iterator);	/* head - n 280, second - s "batel"	*/

	if (n != *(int *)ListGetData(iterator))
	{
		printf("ListInsert - %s - iterator is: %d and should be: %d\n", FAILURE, *(int *)ListGetData(iterator), n);
		failure = 1;
	}

	if (2 != ListSize(list))
	{
		printf("ListInsert or ListSize - %s, size is: %ld and should be: 2\n", FAILURE, ListSize(list));
		failure = 1;
	}
	
	ListRemove(iterator);	/* head - s "batel"	*/

	if (1 != ListSize(list))
	{
		printf("ListRemove or ListSize - %s, size is: %ld and should be: 1\n", FAILURE, ListSize(list));
		failure = 1;
	}
	
	iterator = ListHead(list);	
	
	ListSetData(&f, iterator);	/* head - f 5.5555	*/
	
	if (f != *(float *)ListGetData(iterator))
	{
		printf("ListSetData - %s - iterator is: %f and should be: %f\n", FAILURE, *(float *)ListGetData(iterator), f);
		failure = 1;
	}

	iterator = ListInsert(&n, iterator);	/* head - n 280, second - f 5.5555	*/

	if (*(float *)ListGetData(ListNext(ListHead(list)))!= f)
	{
		printf("ListNext - %s\n", FAILURE);
		failure = 1;
	}

	iterator = ListInsert(&f, iterator);	/* head - f 5.5555, second n 280, third - f 5.5555	*/
	
	if (3 != ListSize(list))
	{
		printf("ListRemove or ListSize - %s, size is: %ld and should be: 3\n", FAILURE, ListSize(list));
		failure = 1;
	}

	if (*(int *)ListGetData(ListNext(ListHead(list)))!= n)
	{
		printf("ListNext - %s\n", FAILURE);
		failure = 1;
	}

	iterator = ListNext(ListHead(list));
	
	ListSetData(&f4, iterator);
	
	iterator = ListFindData(ListHead(list), ListTail(list), is_num_match, &f);
	
	if (f != *(float *)ListGetData(iterator))
	{
		printf("ListFindData - %s - iterator is: %f and should be: %f\n", FAILURE, *(float *)ListGetData(iterator), f);
		failure = 1;
	}

	ListSetData(&f2, ListHead(list));	/* head - f2 280, second n 280, third - f 5.5555	*/

	ListForEach(ListHead(list), ListTail(list), add_num, &add);
	
	if (280 + add != *(float *)ListGetData(ListHead(list)))
	{
	printf("ListForEach - %s - Head iterator is: %f and should be: %f\n", FAILURE, *(float *)ListGetData(ListHead(list)), 280 + add);
	failure = 1;
	}

	iterator = ListNext(ListHead(list));
	
	if (780.5 + add != *(float *)ListGetData(iterator))
	{
	printf("ListForEach - %s - second element is: %f and should be: %f\n", FAILURE, *(float *)ListGetData(iterator), 780.5 + add);
	failure = 1;
	}	

	iterator = ListNext(iterator);
	
	if (f3 != *(float *)ListGetData(iterator))
	{
	printf("ListForEach - %s - third element is: %f and should be: %f\n", FAILURE, *(float *)ListGetData(iterator), f3);
	failure = 1;
	}

	ListDestroy(list);


	if (0 == failure)
	{
		printf("%s\n", SUCCESS);
	}

	return (0);
}

int IsNumMatch(const void *data, void *criteria)
{
	return (*(double *)data == *(double *)criteria);
}

int AddNum(void *data, void *param)
{
	*(float *)data += *(float *)param;
	
	return(0);
}
