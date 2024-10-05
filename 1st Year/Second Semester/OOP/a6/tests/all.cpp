#include "macros.hpp"

int test_service();
int test_domain();

int main()
{
    RUN_TEST(test_service);
    RUN_TEST(test_domain);

    printf("\nAll tests passed!\n\n");
    return EXIT_SUCCESS;
}
