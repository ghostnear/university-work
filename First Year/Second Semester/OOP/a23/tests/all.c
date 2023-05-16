#include "macros.h"

int test_repo();

int test_undo_redo();

int main()
{
    RUN_TEST(test_repo);

    RUN_TEST(test_undo_redo);
    
    printf("\nAll tests passed!\n\n");
    return EXIT_SUCCESS;
}
