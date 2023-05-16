#include <stdio.h>
#include <stdlib.h>

/*
*   16) A string containing n binary representations on 8 bits is given as a character string.
*   Obtain the string containing the numbers corresponding to the given binary representations.
*   Example:
*   Given: '10100111b', '01100011b', '110b', '101011b'
*   Obtain: 10100111b, 01100011b, 110b, 101011b
*/

void convertToByteString(char** strings, char* result, int n);

int main(int argc, char* argv[])
{
    int n = 4;
    char** strings = malloc(n * sizeof(char*));
    strings[0] = "10100111b";
    strings[1] = "01100011b";
    strings[2] = "110b";
    strings[3] = "101011b";
    int* result = malloc(n * sizeof(int));
    convertToByteString(strings, result, n);
    for(int i = 0; i < n; i++)
        printf("result[%d] = %d (%X in hex)\n", i, result[i], result[i]);
}