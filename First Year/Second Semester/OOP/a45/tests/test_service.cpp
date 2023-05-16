#include <cassert>
#include <cstdlib>
#include <exception>

#include "service/all.hpp"
#include "service/service.hpp"

int test_service()
{
    MemoryRepository<Event> repository;
    Service service(&repository, nullptr);

    // Sanity checks.
    assert(service.event_count() == 0);
    assert(service.get_events().get_length() == 0);

    // CRUD checks.
    service.add_event("test", "moment", "https://google.ro/", Date(), Time());
    assert(service.event_count() == 1);
    assert(service.get_events().get_length() == 1);
    assert(service.get_events()[0].to_string() != "");

    service.update_event(0, "test1", "moment1", "https://google.ro/1/", Date(), Time());
    assert(service.event_count() == 1);
    assert(service.get_events().get_length() == 1);
    assert(service.get_events()[0].to_string() != "");

    service.remove_event(0);
    assert(service.event_count() == 0);
    assert(service.get_events().get_length() == 0);

    return EXIT_SUCCESS;
}