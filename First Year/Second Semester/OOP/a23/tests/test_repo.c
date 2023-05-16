#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/repo.h"

bool is_second(Material* testSubject, void* data)
{
    return (testSubject->quantity == 10);
}

int test_repo()
{
    BakeryStorage* repository = create_storage();

    // Initial conditions.
    assert(repository->data->currentSize == 0);
    assert(repository->data->storageCapacity == 1);
    assert(repository->data->data != NULL);

    // Add element and test results.
    Material testMaterial = {
        .name = "Test",
        .supplier = "Me",
        .quantity = 10,
        .whenExpires = {
            .day = 18,
            .month = 7,
            .year = 2022
        }
    };
    add_material(repository, &testMaterial);
    assert(repository->data->currentSize == 1);
    assert(repository->data->storageCapacity == 2);

    // Add duplicate material to test quantity change.
    add_material(repository, &testMaterial);
    assert(((Material*)repository->data->data[0])->quantity == 20);
    assert(repository->data->currentSize == 1);

    // Test delete.
    delete_material(repository, 0);
    assert(repository->data->currentSize == 0);

    // Test update.
    Material testMaterial2 = {
        .name = "Test2",
        .supplier = "Me2",
        .quantity = 30,
        .whenExpires = {
            .day = 30,
            .month = 12,
            .year = 2030
        }
    };
    add_material(repository, &testMaterial);
    update_material(repository, 0, &testMaterial2);
    assert(((Material*)repository->data->data[0])->quantity == testMaterial2.quantity);
    assert(equal_materials(repository->data->data[0], &testMaterial2));

    // Test filtering.
    add_material(repository, &testMaterial);
    BakeryStorage* filterResult = filter_material(repository, &is_second, NULL);
    assert(filterResult->data->currentSize == 1);
    

    // Final free and quit.
    free_storage(filterResult);
    free_storage(repository);
    return EXIT_SUCCESS;
}