#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <iostream>
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class DynamicArray
{
private:
    int _size, _capacity;
    TValue* _elements;

public:
    DynamicArray();
    ~DynamicArray();
    int size();
    int capacity();
    void push_back(TValue value);
    void resize(int newCapacity);
    void pop_back();
    TValue& operator[](int pos);
};

class SortedMultiMap
{
	friend class SMMIterator;

private:
    int _size = 0;
    struct TreeNode
    {
        TKey key;
        DynamicArray data;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
    }*_root = nullptr;

    void free_tree(TreeNode* node);
    void add_tree(TreeNode* &node, TKey c, TValue v);
    TreeNode* search_tree(TreeNode* node, TKey c) const;

    Relation _relation;

public:
    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    std::vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
