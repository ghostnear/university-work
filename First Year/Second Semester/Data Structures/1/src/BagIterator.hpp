#pragma once

#include "Bag.hpp"

class BagIterator
{
    // Access to the private methods of the main class.
    friend class Bag;

private:
    const Bag& bag;

    // The current position we are at. (in the repetitions as well.)
    size_t arrayPosition, elementPosition;

    // Private constructor so iterator can't be made outside class.
    BagIterator(const Bag& c);

public:
    // Go to the beginning.s
    void first();

    // Advance.
    void next();

    // Get current element value.
    TElem getCurrent() const;

    // Check if the iterator is valid. (i.e not outside the vector)
    bool valid() const;
};
