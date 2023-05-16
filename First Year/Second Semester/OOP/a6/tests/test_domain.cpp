#include <cassert>
#include <cstdlib>
#include <exception>

#include "domain/all.hpp"

int test_domain()
{
    // Create a user.
    User tester;
    tester.set_name("Tester");
    assert(tester.get_name() == "Tester");

    // Create a date.
    Date date = Date(1, 1, 1970); // Unix epoch.
    assert(date.get_month() == 1);

    // Create a time.
    Time time = Time(10, 30, 20);
    assert(time.to_string() == "20:30:10");

    // Check default event.
    Event event;
    assert(event == Event("<unnamed>", "<empty>", "localhost", Date(1, 1, 1970), Time(0, 0, 0)));
    event.increment_participant_count();
    event.decrement_participant_count();
    assert(event.get_link() == "localhost");

    return EXIT_SUCCESS;
}