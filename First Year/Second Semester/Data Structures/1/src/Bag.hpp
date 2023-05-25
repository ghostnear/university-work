#pragma once

#include <utility>
#include <cstddef>

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;

class BagIterator;

class Bag
{

private:
    // Data related to the bag.
    std::pair<TElem, int> *bagArray = nullptr;
    size_t bagSize, bagCapacity, elementCount;

    // Access to the private methods of the iterator.
    friend class BagIterator;

    // Resize the dynamic array.
    void resize(size_t newSize);

public:
    // Constructor.
    Bag();

    // Adds an element to the bag.
    void add(TElem e);

    // Removes one occurence of an element from a bag
    // returns true if an element was removed, false otherwise (if e was not part of the bag)
    bool remove(TElem e);

    // Checks if an element appearch is the bag
    bool search(TElem e) const;

    // Removes nr occurences of elem. If the element appears less than nr times, all occurences will be removed.
    // Returns the number of times the element was removed.
    // Throws an exception if nr is negative.
    int removeOccurences(int nr, TElem elem);

    // Returns the number of occurrences for an element in the bag
    int nrOccurrences(TElem e) const;

    // Returns the number of elements from the bag
    int size() const;

    // Returns an iterator for this bag
    BagIterator iterator() const;

    // Checks if the bag is empty
    bool isEmpty() const;

    // Destructor
    ~Bag();
};
