#include "Bag.hpp"
#include "BagIterator.hpp"
#include <exception>
#include <cstdlib>

Bag::Bag()
{
    // Init the stuff. Bag starts as empty.
    bagSize = elementCount = 0;
    bagCapacity = 1;
    bagArray = (std::pair<TElem, int>*)calloc(1, sizeof(std::pair<TElem, int>*));
}

void Bag::resize(size_t newSize)
{
    // Update size and reallocate the array.
    bagCapacity = newSize;
    bagArray = (std::pair<TElem, int>*)realloc(bagArray, bagCapacity * sizeof(std::pair<TElem, int>*));
}

/*
 *  O(bagSize)
 *  worst = theta(2 * bagSize)
 *  when the element is not found in the bag and the container needs resizing.
 *
 *  best = theta(1)
 *  when the element is found early in the bag.
 */ 
void Bag::add(TElem elem)
{
    // Update element count.
    elementCount++;

    // Check if it exists and update if so.
    for(int index = 0; index < bagSize; index++)
        if(bagArray[index].first == elem)
        {
            bagArray[index].second++;
            return;
        }
    
    // Does not exist, add it.
    bagArray[bagSize++] = std::make_pair(elem, 1);

    // Resize if needed.
    if(bagSize == bagCapacity)
        resize(bagSize * 2);
}

/*
 *  O(bagSize)
 *  worst = theta(2 * bagSize)
 *  when the element is found late in the bag and / or in need of removal and the bag needs resizing.
 *
 *  best = theta(1)
 *  when the element is found early in the bag and does not need removal.
 */ 
int Bag::removeOccurences(int nr, TElem elem)
{
    if(nr < 0)
        throw std::exception();
    
    for(int index = 0; index < bagSize; index++)
        if(bagArray[index].first == elem)
        {
            if(bagArray[index].second > nr)
            {
                bagArray[index].second -= nr;
                return nr;
            }
            else
            {
                int result = bagArray[index].second;

                // Remove from the array.
                bagSize--;
                for(int deleteIndex = index; deleteIndex < bagSize; deleteIndex++)
                    bagArray[deleteIndex] = bagArray[deleteIndex + 1];
                
                // Reallocate if needed.
                if(bagSize < bagCapacity / 4)
                    resize(bagCapacity / 2);

                return result;
            }
        }

    return 0;
}

/*
 *  O(bagSize)
 *  worst = theta(bagSize)
 *  when the element is found late in the bag and / or in need of removal.
 *
 *  best = theta(1)
 *  when the element is found early in the bag and does not need removal.
 */ 
bool Bag::remove(TElem elem)
{
    // Search for the element.
    for(int index = 0; index < bagSize; index++)
        if(bagArray[index].first == elem)
        {
            // Remove the element.
            bagArray[index].second--;
            elementCount--;

            // No elements of that type left.
            if(bagArray[index].second == 0)
            {
                // Remove from the array.
                bagSize--;
                for(int deleteIndex = index; deleteIndex < bagSize; deleteIndex++)
                    bagArray[deleteIndex] = bagArray[deleteIndex + 1];
                
                // Reallocate if needed.
                if(bagSize < bagCapacity / 4)
                    resize(bagCapacity / 2);
            }

            // Done.
            return true;
        }

    // Not found.
    return false;
}

/*
 *  O(bagSize)
 *  worst = theta(bagSize)
 *  when the element is found late in the bag.
 *
 *  best = theta(1)
 *  when the element is found early in the bag.
 */ 
bool Bag::search(TElem elem) const
{
    return nrOccurrences(elem) != 0;
}

/*
 *  O(bagSize)
 *  worst = theta(bagSize)
 *  when the element is found late in the bag.
 *
 *  best = theta(1)
 *  when the element is found early in the bag.
 */ 
int Bag::nrOccurrences(TElem elem) const
{
    for(int index = 0; index < bagSize; index++)
        if(bagArray[index].first == elem)
            return bagArray[index].second;
    return 0;
}

/*
 *  theta(1)
 */ 
int Bag::size() const
{
    return elementCount;
}

/*
 *  theta(1)
 */ 
bool Bag::isEmpty() const
{
    return size() == 0;
}

BagIterator Bag::iterator() const
{
    return BagIterator(*this);
}

Bag::~Bag()
{
    free(bagArray);
}
