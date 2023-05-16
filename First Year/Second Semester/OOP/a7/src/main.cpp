#include "all.hpp"
#include "repository/all.hpp"

int main()
{
    int result = 0;
    while(result < 1 || result > 2)
    {
        std::cout << "\nWhat type of data storage do you want to use?\n";
        std::cout << "1. CSV\n";
        std::cout << "2. HTML\n";
        result = UI::read_integer("Your choice > ");

        if(result < 1 || result > 2)
            std::cout << "\nInvalid choice!\n";
    }

    ExportType repositoryType = ExportType::Memory;
    if(result == 1)
        repositoryType = ExportType::CSV;
    else
        repositoryType = ExportType::HTML;

    MemoryRepository<User> userRepository;
    FileRepository<Event> repository("events.txt");
    Service service(repository, userRepository, repositoryType);
    UI ui(service);
    ui.main_loop();

    return EXIT_SUCCESS;
}
