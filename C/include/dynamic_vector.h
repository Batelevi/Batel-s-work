/*****************************************
* Developer:      Batel                  *
* Reviewer:       -                      *
* Version:        1.0                    *    
* Description: API for dynamic_vector.c  * 
******************************************/
#ifndef __OL134_VECTOR_H__
#define __OL134_VECTOR_H__

#include <stddef.h> /* for size_t */

typedef struct vector vector_t;

vector_t *VectorCreate(size_t capacity, size_t element_size);

void VectorDestroy(vector_t *vector);

int VectorPushBack(vector_t *vector, const void *new_element);

void VectorPopBack(vector_t *vector);

void *VectorGetAccessToElement(const vector_t *vector, size_t element_index);

int VectorReserve(vector_t *vector, size_t new_capacity);

int VectorShrink(vector_t *vector); /* shrinks vector to current size */

size_t VectorSize(const vector_t *vector);

int VectorIsEmpty(const vector_t *vector);

size_t VectorCapacity(const vector_t *vector);

#endif /* __OL134_VECTOR_H__*/

