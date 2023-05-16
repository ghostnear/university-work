#include "domain.h"

inline bool equal_dates(Date* first, Date* second)
{
    return first->day == second->day && first->month == second->month && first->year == second->year;
}

bool greater_dates(Date* first, Date* second)
{
    if(first->year != second->year)
        return first->year > second->year;

    if(first->month != second->month)
        return first->month > second->month;

    if(first->day != second->day)
        return first->day > second->day;

    return false;
}

Material* copy_material(Material* source)
{
    Material* result = (Material*)calloc(1, sizeof(Material));

    result->name = (char*)calloc(strlen(source->name) + 1, sizeof(char));
    strcpy(result->name, source->name);

    result->supplier = (char*)calloc(strlen(source->supplier) + 1, sizeof(char));
    strcpy(result->supplier, source->supplier);

    result->quantity = source->quantity;
    result->whenExpires = source->whenExpires;

    return result;
}

inline bool equal_materials(Material* first, Material* second)
{
    // Same name, supplier and expiration date.
    return !strcmp(first->name, second->name) && !strcmp(first->supplier, second->supplier) && equal_dates(&first->whenExpires, &second->whenExpires); 
}

inline void free_material(void* what)
{
    Material* material = (Material*) what;
    free(material->name);
    free(material->supplier);
    free(material);
}