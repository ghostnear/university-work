#include "../src/ui/ui.hpp"

#include <iostream>
#include <cassert>

int main()
{
    Repository repository;
    Service service(repository);

    service.add_school(
        School(
            "Colegiul_Transilvania",
            {46.54, 24.57},
            {3, 5, 2023}
        )
    );

    assert(service.get_all_sorted().size() == 1);

    assert(
        service.remove_school(
            School(
                "Colegiul_Transilvania",
                {46.54, 24.57},
                {3, 5, 2023}
            )
        ) == true
    );

    assert(service.get_all_sorted().size() == 0);

    std::cout << "All tests passed!\n";

    return 0;
}