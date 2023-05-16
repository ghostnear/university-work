#include "tests.hpp"
#include "Bag.hpp"

#include <cstdio>

int main(int argc, char* argv[])
{
    testAll();

    printf("Short tests over.\n");

    testAllExtended();

    printf("All tests ended.\n");
}
