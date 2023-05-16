#include "macros.hpp"

int test_dynamic_array();
int test_service();

int main()
{
    RUN_TEST(test_dynamic_array);
    RUN_TEST(test_service);

    printf("\nAll tests passed!\n\n");
    return EXIT_SUCCESS;
}
