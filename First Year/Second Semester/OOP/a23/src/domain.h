#ifndef DOMAIN_H
#define DOMAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    size_t day;
    size_t month;
    size_t year;
} Date;

bool equal_dates(Date* first, Date* second);
bool greater_dates(Date* first, Date* second);

typedef struct
{
    char* name;
    char* supplier;
    size_t quantity;
    Date whenExpires;
} Material;

Material* copy_material(Material* source);
bool equal_materials(Material* first, Material* second);
void free_material(void* what);

#endif
