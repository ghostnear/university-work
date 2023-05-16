#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "service.h"

typedef struct
{
    bool ended;
    BakeryService* service;
} BakeryUI;

BakeryUI* create_ui(BakeryService* service);
char* read_string(int maxlength, char* message);
int read_integer(char* message);
void print_main_menu();
void print_material_menu();
void main_loop(BakeryUI* onWho);
void free_ui(BakeryUI* target);

Material* read_material();
void print_material(Material* what);

#endif
