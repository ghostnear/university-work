#include "ui.h"
#include "domain.h"
#include "dynarray.h"
#include "repo.h"
#include "service.h"
#include <stdio.h>

BakeryUI* create_ui(BakeryService* service)
{
    BakeryUI* result = (BakeryUI*)calloc(1, sizeof(BakeryUI));

    result->ended = false;
    result->service = service;

    return result;
}

char* read_string(int maxlength, char* message)
{
    char* result = (char*)calloc(maxlength, sizeof(char));

    if(message != NULL)
        printf("%s", message);

    fgets(result, maxlength, stdin);

    strstr(result, "\n")[0] = '\0';

    return result;
}

inline bool is_digit(char character)
{
    return character >= '0' && character <= '9';
}

int read_integer(char* message)
{
    static int result;

    if(message != NULL)
        printf("%s", message);

    char* text = read_string(50, NULL);

    char* end;
    result = strtol(text, &end, 10);
    if(end == text)
    {
        printf("\nNon-integer input entered!\n");
        free(text);
        return read_integer(message);
    }
        
    free(text);

    return result;
}

void print_main_menu()
{
    printf("\nWelcome to your Bakery!\n\n");
    printf("\t1. Manage materials.\n");
    printf("\t2. List all materials.\n");
    printf("\t3. Show expired items containing a string.\n");
    printf("\t4. Display all materials from a given supplier, which are in short supply, sorted ascending by their quantities.\n");
    printf("\t5. Undo.\n");
    printf("\t6. Redo.\n");
    printf("\t7. Exit.\n");
}

void print_material_menu()
{
    printf("\nMaterial managing:\n\n");
    printf("\t1. Add a material.\n");
    printf("\t2. Delete a material by index.\n");
    printf("\t3. Update a material by index.\n");
    printf("\t4. Go back.\n");
}

static Date* today = NULL;

bool expired_has_string_to_look_for(Material* material, void* data)
{
    return strstr(material->name, (char*)data) != NULL && greater_dates(today, &material->whenExpires);
}

bool provider_has_string_to_look_for(Material* material, void* data)
{
    return strcmp(material->supplier, (char*)data) == 0;
}

bool quantity_has_enough(Material* material, void* data)
{
    return material->quantity < *((int*)data);
}

bool compare_by_quantity(Material* a, Material* b)
{
    return a->quantity > b->quantity;
}

void main_loop(BakeryUI* onWho)
{
    while(!onWho->ended)
    {
        print_main_menu();

        static int choice;
        choice = read_integer("\nAction > ");

        switch(choice)
        {
        case 1:
            print_material_menu();
            choice = read_integer("\nAction > ");

            switch(choice)
            {
            case 1:
                add_material_to_service(onWho->service, read_material());
                break;

            case 2:
            {
                static size_t index;

                index = read_integer("Index: ");

                if(index >= onWho->service->storage->data->currentSize)
                {
                    printf("Can't delete element at index %ld when size is %ld.\n", index, onWho->service->storage->data->currentSize);
                    break;
                }

                delete_material_from_service(onWho->service, index);
                break;
            }

            case 3:
            {
                static size_t index;

                index = read_integer("Index: ");

                if(index >= onWho->service->storage->data->currentSize)
                {
                    printf("Can't update element at index %ld when size is %ld.\n", index, onWho->service->storage->data->currentSize);
                    break;
                }

                update_material_in_service(onWho->service, index, read_material());
                break;
            }
                
            case 4:
                break;
            }

            break;

        case 2:
        {
            DynamicArray* data = get_all_materials(onWho->service);

            if(data->currentSize == 0)
                printf("\nStorage is currently empty.\n\n");
            else
            {
                printf("Current materials in storage:\n\n");
                for(int index = 0; index < data->currentSize; index++)
                {
                    printf("Index %d.\n", index);
                    print_material((Material*)get_from_array(data, index));
                    printf("\n");
                }
            }
            
            break;
        }

        case 3:
        {
            static BakeryStorage* filterResults;

            if(today == NULL)
            {
                today = (Date*)calloc(1, sizeof(Date));
                printf("Enter today's date (it will be asked only once per session).\n");
                today->day = read_integer("Day: ");
                today->month = read_integer("Month: ");
                today->year = read_integer("Year: ");
            }

            printf("Today is: %ld.%ld.%ld\n\n", today->day, today->month, today->year);

            static char* stringToLookFor;
            stringToLookFor = read_string(50, "What string to look for (max 50 ch): ");

            filterResults = filter_material(onWho->service->storage, expired_has_string_to_look_for, (void*)stringToLookFor);

            printf("\nResults:\n\n");
            if(filterResults->data->currentSize == 0)
                printf("There are no results matching your criteria.\n");
            else
                for(int index = 0; index < filterResults->data->currentSize; index++)
                    print_material(filterResults->data->data[index]);

            free(stringToLookFor);
            free_storage(filterResults);

            break;
        }

        case 4:
        {
            static BakeryStorage *filterResults, *oldResults;

            static char* stringToLookFor;
            stringToLookFor = read_string(50, "What provider to look for (max 50 ch): ");
            oldResults = filter_material(onWho->service->storage, provider_has_string_to_look_for, (void*)stringToLookFor);

            static int quantityToLookFor;
            quantityToLookFor = read_integer("Below what quantity is it considered short supply: ");
            filterResults = filter_material(oldResults, quantity_has_enough, &quantityToLookFor);
            free_storage(oldResults);

            sort_storage(filterResults, compare_by_quantity);

            printf("\nResults:\n\n");
            if(filterResults->data->currentSize == 0)
                printf("There are no results matching your criteria.\n");
            else
                for(int index = 0; index < filterResults->data->currentSize; index++)
                    print_material(filterResults->data->data[index]);

            free(stringToLookFor);
            free_storage(filterResults);
            break;
        }

        case 5:
            undo_service(onWho->service);
            break;

        case 6:
            redo_service(onWho->service);
            break;
            
        case 7:
            onWho->ended = true;
            break;

        default:
            printf("\nUnknown input %d entered! Try again.\n", choice);
            break;
        }
    }

    if(today != NULL)
        free(today);
}

Material* read_material()
{
    Material* result = (Material*)calloc(1, sizeof(Material));

    result->name = read_string(50, "Material name (max 50 ch): ");
    result->supplier = read_string(50, "Material suplier (max 50 ch): ");
    result->quantity = read_integer("Material quantity: ");
    printf("\nMaterial expiry date\n");
    result->whenExpires.day = read_integer("Day: ");
    result->whenExpires.month = read_integer("Month: ");
    result->whenExpires.year = read_integer("Year: ");

    return result;
}

void print_material(Material* what)
{
    printf(
        "Name: %s\nProvider: %s\nQuantity: %ld\nExpiry date:\n\tDay: %ld\n\tMonth: %ld\n\tYear: %ld\n",
        what->name,
        what->supplier,
        what->quantity,
        what->whenExpires.day,
        what->whenExpires.month,
        what->whenExpires.year
    );
}

void free_ui(BakeryUI* target)
{
    free(target);
}