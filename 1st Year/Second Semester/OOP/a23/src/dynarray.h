#ifndef DYNARRAY_H
#define DYNARRAY_H

#include "domain.h"

typedef struct 
{
    size_t storageCapacity, currentSize;
    void** data;
}DynamicArray;

DynamicArray* create_dynamic_array();
void add_to_array(DynamicArray* where, void* what);
void* get_from_array(DynamicArray* where, size_t index);
void remove_from_array(DynamicArray* where, size_t index, void(freeFunction)(void*));
void free_array(DynamicArray* where, void(freeFunction)(void*));

#endif