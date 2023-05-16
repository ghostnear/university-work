#include "service.h"
#include "dynarray.h"
#include "repo.h"

BakeryService* create_service(BakeryStorage* storage)
{
    BakeryService* result = (BakeryService*)calloc(1, sizeof(BakeryService));
    result->storage = storage;

    result->queue = create_dynamic_array();
    add_to_array(result->queue, copy_storage(storage));
    add_to_array(result->queue, copy_storage(storage));

    result->index = 0;

    return result;
}

void add_state_to_queue(BakeryService* target)
{
    DynamicArray* finalQueue = create_dynamic_array();
    for(int index = 0; index < target->index; index++)
        add_to_array(finalQueue, copy_storage(target->queue->data[index]));

    free_array(target->queue, free_storage);
    target->queue = finalQueue;

    add_to_array(target->queue, copy_storage(target->storage));
    target->index++;
}

DynamicArray* get_all_materials(BakeryService* target)
{
    return get_all(target->storage);
}

void undo_service(BakeryService* target)
{
    if(target->index > 1)
        target->index--;
    target->storage = target->queue->data[target->index - 1];
}

void redo_service(BakeryService* target)
{
    if(target->index < target->queue->currentSize)
        target->index++;
    target->storage = target->queue->data[target->index - 1];
}

void free_service(BakeryService* target)
{
    free_array(target->queue, free_storage);
    free(target);
}

void add_material_to_service(BakeryService* target, Material* material)
{
    add_material(target->storage, material);

    free_material(material);

    add_state_to_queue(target);
}

void delete_material_from_service(BakeryService* target, size_t index)
{
    delete_material(target->storage, index);

    add_state_to_queue(target);
}

void update_material_in_service(BakeryService* target, size_t index, Material* what)
{
    update_material(target->storage, index, what);

    free_material(what);

    add_state_to_queue(target);
}