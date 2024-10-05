#include <cassert>
#include <cstdlib>
#include <exception>

#include "domain/event.hpp"
#include "repository/memory.hpp"
#include "service/all.hpp"
#include "service/service.hpp"

int test_service()
{
    MemoryRepository<Event> repository;
    MemoryRepository<User> users;
    Service service(&repository, &users);

    // Sanity checks.
    assert(service.event_count() == 0);
    assert(service.get_events().size() == 0);

    // CRUD checks.
    service.add_event("test", "moment", "https://google.ro/", Date(), Time());
    assert(service.event_count() == 1);
    assert(service.get_events().size() == 1);
    assert(service.get_events()[0].to_string() != "");

    try
    {
        service.add_event("test", "moment", "https://google.ro/", Date(), Time());
        assert(false); /* LCOV_EXCL_LINE */
    }
    catch(const std::exception&){ } // Add already existing event.

    try
    {
        service.update_event(10, "test1", "moment1", "https://google.ro/1/", Date(), Time());
        assert(false); /* LCOV_EXCL_LINE */
    }
    catch(const std::exception&){ } // Update non existing event.

    try
    {
        service.remove_event(10);
        assert(false); /* LCOV_EXCL_LINE */
    }
    catch(const std::exception&){ } // Remove non existing event.

    service.update_event(0, "test1", "moment1", "https://google.ro/1/", Date(), Time());
    assert(service.event_count() == 1);
    assert(service.get_events().size() == 1);
    assert(service.get_events()[0].to_string() != "");

    service.remove_event(0);
    assert(service.event_count() == 0);
    assert(service.get_events().size() == 0);

    // Filter checks.
    Event event = Event("test", "moment", "https://google.ro/", Date(), Time());
    service.add_event("test", "moment", "https://google.ro/", Date(), Time());
    assert(service.get_events_by_month(0).size() == 1);
    assert(service.get_events_by_month(5).size() == 0);
    assert(service.get_event(0) == event);

    // User interaction checks.
    service.set_user("Test");
    assert(service.get_user() == "Test");   // New user added.
    service.set_user("");
    assert(service.get_user() == "");   // User resetted.
    service.add_user_event(event);
    service.remove_user_event(event);
    assert(service.get_user_events().size() == 0);
    assert(service.check_user_event(event) == false);
    service.set_user("Test 2");
    service.set_user("Test");
    assert(service.get_user() == "Test");   // Previous user set.

    service.add_user_event(event);
    assert(service.get_user_events().size() == 1);
    assert(service.check_user_event(event) == true);
    service.remove_user_event(event);
    assert(service.get_user_events().size() == 0);
    assert(service.check_user_event(event) == false);

    return EXIT_SUCCESS;
}