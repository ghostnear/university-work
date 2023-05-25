#include <exception>
#include "BagIterator.hpp"
#include "Bag.hpp"

// O(1), worst = 1, best = 1
BagIterator::BagIterator(const Bag& c): bag(c)
{
    first();
}

// O(1), worst = 1, best = 1
void BagIterator::first()
{
    arrayPosition = 0;
    elementPosition = 1;
}

// O(1), worst = 1, best = 1
void BagIterator::next()
{
    if(valid() == false)
        throw std::exception();

    elementPosition++;
    if(bag.bagArray[arrayPosition].second < elementPosition)
    {
        arrayPosition++;
        elementPosition = 1;
    }
}

// O(1), worst = 1, best = 1
bool BagIterator::valid() const
{
    return arrayPosition < bag.bagSize;
}

// O(1), worst = 1, best = 1
TElem BagIterator::getCurrent() const
{
    if(valid() == false)
        throw std::exception();

    return bag.bagArray[arrayPosition].first;
}
