/***********************************************
* Developer:   Batel Levi                      *
* Reviewer:    Aviv                            *
* Version:     1.0                             *
* Description: API for hash_table.c            *
************************************************/
#include <assert.h>	/*	for assert	*/
#include <stdlib.h> /*  for malloc  */
#include <sys/types.h>  /*  for ssize_t */
#include <math.h>   /*  for pow and sqrt    */


#include "hash_table.h"
#include "doubly_linked_list.h"

struct hash_table
{
    int (*is_match)(const void *key1, const void *key2);
    size_t (*hash_func)(const void *key);
    size_t size;
    size_t table_size;
    dlist_t **table;
};


hash_table_t *HashCreate(int (*is_match)(const void *lhs, const void *rhs),
                         size_t (*hash_func)(const void *key),
                         size_t table_size)
{
    hash_table_t *hash = (hash_table_t *)malloc(sizeof(hash_table_t));
    ssize_t i = 0;

    if (NULL == hash)
    {
        return NULL;
    }
    
    assert(is_match);
    assert(hash_func);
    assert(table_size > 0);

    hash->is_match = is_match;
    hash->hash_func = hash_func;
    hash->size = 0;
    hash->table_size = table_size;
    hash->table = (dlist_t **)malloc(table_size * sizeof(dlist_t *));

    if (NULL == hash->table)
    {
        free(hash);
        return NULL;
    }

    for (i = 0; i < (ssize_t)hash->table_size; ++i)
    {
        hash->table[i] = DListCreate();

        if (NULL == hash->table[i])
        {
            for (i = i - 1; i >= 0; --i)
            {
                DListDestroy(hash->table[i]);
            }
            free(hash->table);
            free(hash);

            return NULL;
        }
    }

    return (hash);
}

void HashDestroy(hash_table_t *hash)
{
    size_t i = 0;

    assert(hash);

    for (i = 0; i < hash->table_size; ++i)
    {
        DListDestroy(hash->table[i]);
    }
    
    free(hash->table);
    free(hash);
}

int HashInsert(hash_table_t *hash, void *data)
{
    size_t key = 0;
    int ret = 0;

    assert(hash);

    key = hash->hash_func(data);

    ret = DListIsSameIter(DListPushBack(hash->table[key], data),
                          DListEnd(hash->table[key]));

    hash->size += !ret;

    return (ret);
}

void *HashRemove(hash_table_t *hash, void *data)
{
    size_t key = 0;
    dlist_iterator_t iter_to_remove = {0};
    void *data_to_remove = NULL;

    assert(hash);

    key = hash->hash_func(data);
    iter_to_remove = DListFindData(DListBegin(hash->table[key]),
                                   DListEnd(hash->table[key]),
                                   hash->is_match,
                                   data);

    if (DListIsSameIter(DListEnd(hash->table[key]), iter_to_remove))
    {
        return NULL;
    }

    data_to_remove = DListGetData(iter_to_remove);
    
    DListRemove(iter_to_remove);

    hash->size -= 1;

    return (data_to_remove);
}

void *HashFind(hash_table_t *hash, void *data)
{
    size_t key = 0;
    dlist_iterator_t iter_data = {0};
    void *found_data = NULL;

    assert(hash);

    key = hash->hash_func(data);
    iter_data = DListFindData(DListBegin(hash->table[key]),
                              DListEnd(hash->table[key]),
                              hash->is_match,
                              data);

    if (DListIsSameIter(DListEnd(hash->table[key]),iter_data))
    {
        return NULL;
    }

    found_data = DListGetData(iter_data);
    
    if (DListIsSameIter(DListPushFront(hash->table[key], found_data),
                        DListEnd(hash->table[key])))
    {
        return (found_data);
    }

    DListRemove(iter_data);

    return (found_data);
}

size_t HashSize(const hash_table_t *hash)
{
    assert(hash);

    return (hash->size);
}

int HashIsEmpty(const hash_table_t *hash)
{
    assert(hash);

    return (hash->size == 0);
}

int HashForEach(hash_table_t *hash,
                int (*action_func)(void *data, void *param),
                void *param)
{
    size_t i = 0;
    int action_ret = 0;

    assert(hash);
    assert(action_func);

    for (i = 0; i < hash->table_size && !action_ret; ++i)
    {
        action_ret = DListForEach(DListBegin(hash->table[i]),
                                  DListEnd(hash->table[i]),
                                  action_func,
                                  param);
    }

    return (action_ret);
}

double HashLoad(const hash_table_t *hash)
{
    assert(hash);

    return ((double)hash->size / hash->table_size);
}

double HashSD(const hash_table_t *hash)
{
    size_t i = 0;
    double avg = 0;
    double sum_of_square_deviations = 0;

    assert(hash);

    avg = HashLoad(hash);

    for (i = 0; i < hash->table_size; ++i)
    {
        sum_of_square_deviations += pow(DListSize(hash->table[i]) - avg, 2);
    }

    return (sqrt(sum_of_square_deviations / hash->table_size));
}