#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/service.h"

int test_undo_redo()
{
    BakeryStorage* storage = create_storage();
    BakeryService* service = create_service(storage);

    free_service(service);
    free_storage(storage);
    return EXIT_SUCCESS;
}