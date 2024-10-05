#include "domain/domain.hpp"
#include "ui/ui.hpp"

int main()
{
    Repository repository;
    Service service(repository);
    service.add_school(
        School(
            "Avram_Iancu",
            {46.77, 23.60},
            {15, 4, 2023}
        )
    );
    service.add_school(
        School(
            "George_Cosbuc",
            {46.77, 23.58},
            {8, 4, 2023}
        )
    );
    service.add_school(
        School(
            "Alexandru_Vaida_Voievod",
            {46.77, 23.63},
            {23, 4, 2023}
        )
    );
    service.add_school(
        School(
            "Romulus_Guga",
            {46.53, 24.57},
            {4, 5, 2023}
        )
    );
    service.add_school(
        School(
            "Colegiul_Transilvania",
            {46.54, 24.57},
            {3, 5, 2023}
        )
    );
    UI ui(service);

    ui.run();

    return 0;
}