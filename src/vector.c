#include "vector.h"

void vector_init(vector_t *v)
{
    // Setup initial conditions
    v->data = NULL;
    v->capacity = 0;
    v->length = 0;
}

void vector_add(vector_t *v, void *item)
{
    // If the first item
    if (v->data == NULL)
    {
        v->capacity = INITIAL_NUM_ELEMENTS;
        v->data = malloc(sizeof(void*) * v->capacity);
    }

    // Array is full
    //  need to expand (i.e. reallocate) the array
    if (v->length == v->capacity)
    {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(void*) * v->capacity);
    }

    // Add the pointer to the array
    v->data[v->length++] = item;
}

void* vector_pop(vector_t* v, size_t location)
{
    size_t i;
    void* toreturn = NULL;

    if (location < v->length)
    {
        toreturn = v->data[location];

        for (i=location; i<v->length+1; i++)
        {
            v->data[i] = v->data[i+1];
        }

        // Ensure the last pointer is reset to NULL
        v->data[v->length] = NULL;
        v->length--;
    }

    return toreturn;
}

void* vector_get(vector_t *v, size_t location)
{
    void *toreturn = NULL;

    if (location < v->length)
    {
        toreturn = v->data[location];
    }

    return toreturn;
}

void vector_set(vector_t *v, size_t location, void* item)
{
    if (location < v->length)
    {
        v->data[location] = item;
    }
}

void vector_clear(vector_t *v)
{
    v->length = 0;
}

void vector_free(vector_t *v)
{
    v->length = 0;
    v->capacity = 0;

    // Free the data;
    free(v->data);
    v->data = NULL;
}

/*void vector_free_contents(vector_t* v)
{
    size_t i;

    for (i=0; i<v->length; i++)
    {
        free(v->data[i]);
        v->data[i] = NULL;
    }
}*/

