#include "repo.h"
#include "domain.h"
#include "dynarray.h"

inline BakeryStorage* create_storage()
{
    BakeryStorage* result = (BakeryStorage*)malloc(sizeof(BakeryStorage));
    result->data = create_dynamic_array();

    return result;
}

void sort_storage(BakeryStorage* what, bool(*criteria)(Material*, Material*))
{
    for(size_t index = 0; index < what->data->currentSize; index++)
        for(size_t indexTheSequel = index + 1; indexTheSequel < what->data->currentSize; indexTheSequel++)
            if(criteria(what->data->data[index], what->data->data[indexTheSequel]))
            {
                // Good thing I made them pointers.
                static Material* auxiliary;
                auxiliary = what->data->data[index];
                what->data->data[index] = what->data->data[indexTheSequel];
                what->data->data[indexTheSequel] = auxiliary;
            }
}

BakeryStorage* copy_storage(BakeryStorage* target)
{
    BakeryStorage* result = create_storage();
    for(size_t index = 0; index < target->data->currentSize; index++)
        add_material(result, target->data->data[index]);
    return result;
}

inline void free_storage(void* what)
{
    static BakeryStorage* storage;
    storage = (BakeryStorage*)(what);
    free_array(storage->data, free_material);
    free(what);
}

DynamicArray* get_all(BakeryStorage* where)
{
    return where->data;
}

Material* get_material(BakeryStorage* where, size_t position)
{
    return (Material*)get_from_array(where->data, position);
}

size_t find_material(BakeryStorage* where, Material* what)
{
    for(size_t index = 0; index < where->data->currentSize; index++)
        if(equal_materials(get_from_array(where->data, index), what))
            return index;
    return -1;
}

void add_material(BakeryStorage* where, Material* what)
{
    static size_t materialPosition = 0;
    static Material* material = NULL;
    
    materialPosition = find_material(where, what);
    if(materialPosition != -1)
    {
        material = (Material*)(get_from_array(where->data, materialPosition));
        material->quantity += what->quantity;
        return;
    }

    add_to_array(where->data, copy_material(what));
}

void delete_material(BakeryStorage* where, size_t position)
{
    remove_from_array(where->data, position, free_material);
}

void update_material(BakeryStorage* where, size_t position, Material* what)
{
    static Material* target;
    
    target = (Material*)get_from_array(where->data, position);
    target->quantity = what->quantity;
    target->whenExpires = what->whenExpires;
    
    free(target->name);
    free(target->supplier);

    target->name = (char*)calloc(strlen(what->name) + 1, sizeof(char));
    target->supplier = (char*)calloc(strlen(what->supplier) + 1, sizeof(char));
    strcpy(target->name, what->name);
    strcpy(target->supplier, what->supplier);
}

BakeryStorage* filter_material(BakeryStorage* where, bool(*criteria)(Material*, void*), void* data)
{
    BakeryStorage* result = create_storage();
    static Material* material;

    for(int index = 0; index < where->data->currentSize; index++)
    {
        material = (Material*)get_from_array(where->data, index);
        if(criteria(material, data))
            add_material(result, material);
    }

    return result;
}
