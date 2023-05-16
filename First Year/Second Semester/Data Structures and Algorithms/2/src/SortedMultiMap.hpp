#pragma once

#include <cstdio>
#include <vector>
#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;

#define NULL_TVALUE -111111
#define NULL_TELEM std::pair<TKey, TValue>(-111111, -111111);

// Forward declaration of the iterator stuff.
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class SortedMultiMap
{
    // Has access to private stuff.
	friend class SMMIterator;

private:
    std::size_t containerSize;

    struct DLLNode
    {
        TElem data;
        DLLNode* next = nullptr;
        DLLNode* previous = nullptr;
    } *root;

    Relation comparator;

    void free_linked_list(DLLNode* rootNode);
    void print_linked_list(DLLNode* rootNode);

public:

    // Constructor.
    SortedMultiMap(Relation r);

	// Adds a new key value pair to the sorted multi map.
    void add(TKey c, TValue v);

	// Returns the values belonging to a given key.
    std::vector<TValue> search(TKey c) const;

	// Removes a key value pair from the sorted multimap.
	// Returns true if the pair was removed (it was part of the multimap), false if nothing is removed.
    bool remove(TKey c, TValue v);

    // Returns the number of key-value pairs from the sorted multimap.
    int size() const;

    // Verifies if the sorted multi map is empty.
    bool isEmpty() const;

    // Returns an iterator for the sorted multimap. The iterator will return the pairs as required by the relation (given to the constructor).
    SMMIterator iterator() const;

    // Returns a vector with all the keys from the SortedMultiMap.
    std::vector<TKey> keySet() const;

    // Destructor.
    ~SortedMultiMap();
};
