#ifndef __VECTOR_H
#define __VECTOR_H

#include <stdlib.h>

/* An implementation of a simple vector 
 *  where pointers to items are stored in a single
 *  allocated array on the heap.
 *
 *  It is up to the programmer to ensure to manage
 *   cleanup of items */

#define INITIAL_NUM_ELEMENTS 10

typedef struct {
    void** data;
    size_t capacity;
    size_t length;
} vector_t;


void vector_init(vector_t *v);

void vector_add(vector_t *v, void *item);
void* vector_pop(vector_t *v, size_t location);

void* vector_get(vector_t *v, size_t location);
void vector_set(vector_t *v, size_t location, void* item);

// Note does not free items
void vector_clear(vector_t *v);
void vector_free(vector_t *v);

#endif
