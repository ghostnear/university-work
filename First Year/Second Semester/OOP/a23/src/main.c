#include "domain.h"
#include "repo.h"
#include "service.h"
#include "ui.h"

int main(void)
{
    BakeryStorage* storage = create_storage();
    BakeryService* service = create_service(storage);
    BakeryUI* ui = create_ui(service);

    // Add 10 entries to the bakery.
    Material testMaterial = {
        .name = "Peanuts",
        .supplier = "Yu",
        .quantity = 30,
        .whenExpires = {
            .day = 5,
            .month = 12,
            .year = 2015
        }
    };
    for(size_t index = 0; index < 10; index++)
    {
        add_material_to_service(service, copy_material(&testMaterial));
        testMaterial.quantity -= 2;
        testMaterial.whenExpires.day++;
    }
    

    main_loop(ui);

    free_ui(ui);
    free_service(service);
    free_storage(storage);
    
    return 0;
}
