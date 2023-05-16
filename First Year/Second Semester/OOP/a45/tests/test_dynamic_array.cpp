#include <cassert>
#include <cstdlib>
#include <exception>

#include "domain/all.hpp"

int test_dynamic_array()
{
    // Sanity checks.
    DynamicArray<int> subject;
    assert(subject.get_length() == 0);
    assert(subject.get_capacity() == 1);
    try
    {
        subject[5];
        subject.remove_element(5);
        assert(false);
    }
    catch(std::exception const&){}

    // Function checks.
    subject.add_element(5);
    assert(subject.get_length() == 1);
    assert(subject.get_capacity() == 2);
    assert(subject[0] == 5);

    subject.remove_element(0);
    assert(subject.get_length() == 0);
    assert(subject.get_capacity() == 2);
    
    while(subject.get_length() != 0)
        subject.remove_element(subject.get_length() - 1);
    assert(subject.get_length() == 0);
    assert(subject.get_capacity() == 2);

    subject.add_element(5);
    subject[0] = 10;
    assert(subject[0] == 10);
    subject.remove_element(0);

    // Internals checks.
    for(size_t index = 0; index < 100; index++)
        subject.add_element(index);
    assert(subject.get_length() == 100);
    assert(subject.get_capacity() == 128);

    return EXIT_SUCCESS;
}