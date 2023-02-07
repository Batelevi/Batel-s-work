/***********************************************
* Developer:   Batel Levi                      *
* Reviewer:                                    *
* Version:     1.0                             *
* Description: API for hash_table.c            *
************************************************/
#ifndef __OL134_HASH_TABLE_H__
#define __OL134_HASH_TABLE_H__

#include <stddef.h>	/*	For size_t	*/

typedef struct hash_table hash_table_t;

/*---------------------------------------------------------------------------*/
/*	HashCreate:
		Description:
			Create hash DS
		Params:
			is_match	- compares data's within the list
			hash_func	- provides the hash function key for the table
			table_size	- maximum number of keys in the hash table 
		Return:
			Success - Pointer to hash table DS
			Failure - NULL
		Complexity:
			Time - O(N) where N is table size
*/
hash_table_t *HashCreate(int (*is_match)(const void *lhs, const void *rhs),
						 size_t (*hash_func)(const void *data),
                		 size_t table_size);

/*---------------------------------------------------------------------------*/
/*	hashDestroy:
		Description:
			Destroy DS
		Params:
			Hash table to destroy
		Complexity:
			Time - O(N)
*/
void HashDestroy(hash_table_t *hash);

/*---------------------------------------------------------------------------*/
/*	HashInsert:
		Description:
			Pushes the data into the hash
		Return:
			Success - 0
			Failure - 1
		Complexity:
			Time - O(1)
*/
int HashInsert(hash_table_t *hash, void *data);

/*---------------------------------------------------------------------------*/
/*	HashRemove:
		Params:
			hash table
			data to removed
		Return:
			The removed data
		Complexity:
			Time - O(1)
*/
void *HashRemove(hash_table_t *hash, void *data);

/*---------------------------------------------------------------------------*/
/*	HashFind:
		Params:
			data - data to be found
		Return:
			Success - the data
			Failure - NULL if element doesn't exist
		Complexity:
			Time - O(1)
*/
void *HashFind(hash_table_t *hash, void *data);

/*---------------------------------------------------------------------------*/
/*	HashSize:
		Params:
			hash table
		Return:
			Number of elements
		Complexity:
			Time - O(1)
*/
size_t HashSize(const hash_table_t *hash);

/*---------------------------------------------------------------------------*/
/*	HashIsEmpty:
		Params:
			hash table 
		Return:
			1 - empty
			0 - not empty
		Complexity:
			Time - O(1)
*/
int HashIsEmpty(const hash_table_t *hash);

/*---------------------------------------------------------------------------*/
/*	HashForEach:
		Params:
			action_func	- action function on the data
			param		- argument for action function
		Return:
			Action function status (0 is success)
		Note:
			If action function fails, foreach stops
		Complexity:
			Time - O(N)
*/
int HashForEach(hash_table_t *hash,
				int (*action_func)(void *data, void *param),
				void *param);

/*---------------------------------------------------------------------------*/
/*	HashLoad:
		Params:
			hash table
		Return:
			the hashload
		Complexity:
			Time - O(1)
*/
double HashLoad(const hash_table_t *hash);

/*---------------------------------------------------------------------------*/
/*	HashSD:
		Params:
			hash table
		Return:
			returns the Standard deviation of the hash table
		Complexity:
			Time - O(N)
*/
double HashSD(const hash_table_t *hash);

#endif /* __OL134_HASH_TABLE_H__*/