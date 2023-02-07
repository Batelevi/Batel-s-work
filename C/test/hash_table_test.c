#define  _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"	/*	header file	*/

#define SUCCESS "\033[1;32mSUCCESS\033[0m"
#define FAILURE "\033[1;31mFAILURE\033[0m"

#define DIGITS 10
#define N_WORDS 102401
#define HASH_SIZE 133122

int failure = 0;

void TestHashTable();
void PrintError(char *name, int line ,double function_result ,double should_be);

int IsMatch(const void *key1, const void *key2);

/*	each key gets its tens digit as an index	*/
size_t HashFunc(const void *key);

int IsMatchDict(const void *key1, const void *key2);
size_t HashFuncDict(const void *key);

int Action(void *data, void *param);

int main ()
{
	TestHashTable();
	
	return (0);
}


void TestHashTable()
{
	hash_table_t *hash = HashCreate(IsMatch, HashFunc, DIGITS);
	int a15 = 15;
	int a23 = 23;
	int a16 = 16;
	FILE *dict = NULL;
	size_t i = 0;
	char *dictionary[N_WORDS] = {0};
	size_t line = 0;
	char *find = NULL;

	PrintError("HashCreate", __LINE__, !hash, 0);
	PrintError("HashSize", __LINE__, HashSize(hash), 0);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 1);

	PrintError("HashInsert", __LINE__, HashInsert(hash, &a15), 0);
	PrintError("HashSize", __LINE__, HashSize(hash), 1);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);
	PrintError("HashFind", __LINE__, *(int *)HashFind(hash, &a15), a15);

	PrintError("HashRemove", __LINE__, *(int *)HashRemove(hash, &a15), a15);
	PrintError("HashSize", __LINE__, HashSize(hash), 0);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 1);
	/*PrintError("HashFind", __LINE__, (size_t)HashFind(hash, &a15), 0);*/

	PrintError("HashInsert", __LINE__, HashInsert(hash, &a15), 0);
	PrintError("HashSize", __LINE__, HashSize(hash), 1);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);
	PrintError("HashFind", __LINE__, *(int *)HashFind(hash, &a15), a15);

	PrintError("HashForEach", __LINE__, HashForEach(hash, Action, &a15), 0);
	PrintError("HashFind", __LINE__, *(int *)HashFind(hash, &a15), a15);
	a15 -= 1; /*	to get it back to 15 after ForEach test	*/
	PrintError("HashFind", __LINE__, *(int *)HashFind(hash, &a15), a15);

	PrintError("HashInsert", __LINE__, HashInsert(hash, &a23), 0);
	PrintError("HashSize", __LINE__, HashSize(hash), 2);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);
	PrintError("HashFind", __LINE__, *(int *)HashFind(hash, &a23), a23);

	PrintError("HashInsert", __LINE__, HashInsert(hash, &a16), 0);
	PrintError("HashSize", __LINE__, HashSize(hash), 3);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);
	PrintError("HashFind", __LINE__, *(int *)HashFind(hash, &a16), a16);

	PrintError("HashRemove", __LINE__, *(int *)HashRemove(hash, &a15), a15);
	PrintError("HashSize", __LINE__, HashSize(hash), 2);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);
	/*PrintError("HashFind", __LINE__, (size_t)HashFind(hash, &a15), 0);*/

	PrintError("HashRemove", __LINE__, *(int *)HashRemove(hash, &a16), a16);
	PrintError("HashSize", __LINE__, HashSize(hash), 1);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);
	/*PrintError("HashFind", __LINE__, (size_t)HashFind(hash, &a16), 0);*/

	PrintError("HashInsert", __LINE__, HashInsert(hash, &a15), 0);
	PrintError("HashSize", __LINE__, HashSize(hash), 2);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);
	PrintError("HashFind", __LINE__, *(int *)HashFind(hash, &a15), a15);

	PrintError("HashInsert", __LINE__, HashInsert(hash, &a16), 0);
	PrintError("HashSize", __LINE__, HashSize(hash), 3);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);
	PrintError("HashFind", __LINE__, *(int *)HashFind(hash, &a16), a16);

	PrintError("HashLoad", __LINE__, (float)HashLoad(hash), (float)3 / 10);
	PrintError("HashSD", __LINE__, (float)HashSD(hash), (float)sqrt(0.41));

	PrintError("HashRemove", __LINE__, *(int *)HashRemove(hash, &a15), a15);
	PrintError("HashRemove", __LINE__, *(int *)HashRemove(hash, &a16), a16);
	PrintError("HashRemove", __LINE__, *(int *)HashRemove(hash, &a23), a23);
	PrintError("HashSize", __LINE__, HashSize(hash), 0);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 1);

	HashDestroy(hash);

	hash = HashCreate(IsMatchDict, HashFuncDict, HASH_SIZE);

	dict = fopen("/etc/dictionaries-common/words", "r");

	if (NULL == dict)
	{
		printf("Couldn't open dictionary file\n");
	}


	while (getline(&dictionary[i], &line, dict) != EOF && i < N_WORDS)
	{
		HashInsert(hash, (void *)dictionary[i]);
		++i;
	}

	fclose(dict);

	PrintError("HashSize", __LINE__, HashSize(hash), 102401);
	PrintError("HashIsEmpty", __LINE__, HashIsEmpty(hash), 0);

	PrintError("HashFind", __LINE__,
			   strcmp((char *)HashFind(hash, (void *)dictionary[4000]), dictionary[4000]),
			   0);

	PrintError("HashFind", __LINE__,
			   strcmp((char *)HashFind(hash, (void *)dictionary[51450]), dictionary[51450]),
			   0);

	find = "zucchini\n";
	PrintError("HashFind", __LINE__,
			   strcmp((char *)HashFind(hash, find), "zucchini\n"),
			   0);

	printf("HashLoad is: %f and HashSD is %f\n", HashLoad(hash), HashSD(hash));

	i = 0;
	while (i < N_WORDS)
	{
		free(dictionary[i]);
		++i;
	}

	HashDestroy(hash);

	if (0 == failure)
	{
		printf("Hash Table - %s\n", SUCCESS);
	}
}

int IsMatch(const void *key1, const void *key2)
{
	assert(key1);
	assert(key2);

	return (*(int *)key1 == *(int *)key2);
}

int IsMatchDict(const void *key1, const void *key2)
{
	assert(key1);
	assert(key2);

	return (strcmp((char *)key1, (char *)key2) == 0);
}

size_t HashFunc(const void *key)
{
	assert(key);

	return (*(int *)key / 10);
}

size_t HashFuncDict(const void *key)
{
	size_t hash = 0;
	size_t p = 8;
	size_t i = 0;
	size_t len = 0;

	assert(key);

	len = strlen((char *)key);
	hash = len;

	while (len)
	{
		hash += *((char *)key + i) * pow(p, i);
		++i;
		--len;
	}

	return (hash % HASH_SIZE);
}

int Action(void *data, void *param)
{
	(void)param;

	*(int *)data += 1;

	return (0);
}

void PrintError(char *name, int line ,double function_result ,double should_be)
{
	if (function_result != should_be)
	{
		printf("%s - %s - in line %d - function result is: %.2f and should be: %.2f\n", name, FAILURE, line, function_result, should_be);
		failure = 1;
	}
}