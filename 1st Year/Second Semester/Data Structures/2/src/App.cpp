#include <cstdlib>
#include <cstdio>

#include "ShortTest.hpp"
#include "ExtendedTest.hpp"

int main()
{
    testAll();
	testAllExtended();

    printf("Finished SMM Tests!\n");
    return EXIT_SUCCESS;
}
