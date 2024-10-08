#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1
#define UNUSED(X) (void)(X)

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    printf("Hello world!\n");

    return EXIT_SUCCESS;
}
