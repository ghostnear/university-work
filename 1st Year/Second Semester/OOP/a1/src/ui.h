#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>

void printMenu(void);
int* readArray(int* size);
void printArray(int* what, int size);
void readInteger(int* where, char* message);
void readCharacter(char* where, char* message);

#endif
