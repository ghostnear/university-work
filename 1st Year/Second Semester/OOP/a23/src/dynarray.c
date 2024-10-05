#include "dynarray.h"

inline DynamicArray* create_dynamic_array()
{
    DynamicArray* result = (DynamicArray*)malloc(sizeof(DynamicArray));

    result->data = (void**)calloc(1, sizeof(void*));
    result->storageCapacity = 1;
    result->currentSize = 0;

    return result;
}

inline void resize_dynamic_array(DynamicArray* what, size_t newSize)
{
    what->data = (void**)realloc(what->data, newSize * sizeof(void*));
    what->storageCapacity = newSize;
}

void add_to_array(DynamicArray* where, void* what)
{
    where->data[where->currentSize++] = what;
    if(where->currentSize == where->storageCapacity)
        resize_dynamic_array(where, 2 * where->currentSize);
}

void* get_from_array(DynamicArray* where, size_t index)
{
    return where->data[index];
}

void remove_from_array(DynamicArray* where, size_t index, void(freeFunction)(void*))
{
    freeFunction(where->data[index]);

    for(size_t position = index; position < where->currentSize - 1; position++)
        where->data[position] = where->data[position + 1];
    where->currentSize--;

    if(where->currentSize < where->storageCapacity / 4)
        resize_dynamic_array(where, where->storageCapacity / 2);
}

void free_array(DynamicArray* where, void(freeFunction)(void*))
{
    for(size_t index = 0; index < where->currentSize; index++)
        freeFunction(where->data[index]);
    free(where->data);
    free(where);
}