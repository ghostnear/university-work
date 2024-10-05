#include "all.hpp"
#include "domain/event.hpp"
#include "domain/user.hpp"
#include "repository/memory.hpp"

int main()
{
    MemoryRepository<Event> repository;
    MemoryRepository<User> userRepository;
    Service service(&repository, &userRepository);
    service.add_event(
        "Vasile",
        "merge la cules.",
        "https://google.ro/",
        Date(1, 1, 1970),
        Time(10, 10, 10)
    );
    service.add_event(
        "Marcel",
        "se apuca de politica.",
        "https://facebook.com/",
        Date(10, 10, 2010),
        Time(45, 30, 6)
    );
    service.add_event(
        "Steve",
        "se apuca de sapat.",
        "https://minecraft.net/",
        Date(10, 5, 2009),
        Time(5, 5, 15)
    );
    service.add_event(
        "Pufi",
        "se lasa de lol.",
        "https://google.ro/",
        Date(31, 2, 2023),
        Time(0, 0, 0)
    );
    service.add_event(
        "Actual event",
        "with no stuff happening.",
        "https://reddit.com/",
        Date(5, 5, 2005),
        Time(9, 9, 9)
    );
    service.add_event(
        "Ion",
        "se apuca de dat cu sapa.",
        "https://versuri.ro/",
        Date(8, 8, 2008),
        Time(7, 7, 7)
    );
    service.add_event(
        "Am ramas fara nume",
        "Si fara idei de eveniment.",
        "https://lordinu.ro/",
        Date(10, 10, 2009),
        Time(10, 10, 10)
    );
    service.add_event(
        "Party",
        "mereu pe Piezisa.",
        "http://google.ro/",
        Date(29, 3, 2023),
        Time(2, 51, 22)
    );
    service.add_event(
        "Merge the branch",
        "without reviewing the changes.",
        "https://github.com/",
        Date(20, 2, 2021),
        Time(6, 6, 6)
    );
    service.add_event(
        "Nasterea lui Iisus",
        "All my christian homies were here.",
        "https://biblia.ro/",
        Date(1, 1, 0),
        Time(6, 6, 6)
    );
    UI ui(&service);
    
    ui.main_loop();

    return EXIT_SUCCESS;
}
