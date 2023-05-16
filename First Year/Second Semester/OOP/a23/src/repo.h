#ifndef REPO_H
#define REPO_H

#include "domain.h"
#include "dynarray.h"

typedef struct
{
    DynamicArray* data;
} BakeryStorage;

BakeryStorage* create_storage();
void sort_storage(BakeryStorage* what, bool(*criteria)(Material*, Material*));
void free_storage(void* what);

BakeryStorage* copy_storage(BakeryStorage* target);

DynamicArray* get_all(BakeryStorage* where);
Material* get_material(BakeryStorage* where, size_t position);
size_t find_material(BakeryStorage* where, Material* what);
void add_material(BakeryStorage* where, Material* what);
void delete_material(BakeryStorage* where, size_t position);
void update_material(BakeryStorage* where, size_t position, Material* what);
BakeryStorage* filter_material(BakeryStorage* where, bool(*criteria)(Material*, void*), void* data);

#endif
