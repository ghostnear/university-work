#ifndef SERVICE_H
#define SERVICE_H

#include "dynarray.h"
#include "repo.h"

typedef struct
{
    BakeryStorage* storage;
    DynamicArray* queue;
    size_t index;
} BakeryService;

BakeryService* create_service(BakeryStorage* storage);
void free_service(BakeryService* target);

void undo_service(BakeryService* target);
void redo_service(BakeryService* target);
DynamicArray* get_all_materials(BakeryService* target);
void add_material_to_service(BakeryService* target, Material* material);
void update_material_in_service(BakeryService* target, size_t index, Material* what);
void delete_material_from_service(BakeryService* target, size_t index);

#endif
