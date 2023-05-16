#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
int SortedMap::hash_key(TKey key) const
{
	if(key < 0)
		key = -key;
	
	return key % tableCapacity;
}

/*
 * Complexity:
 * 	Constant: Theta(n)
 */
SortedMap::SortedMap(Relation r)
{
	elementCount = 0;
	hashTable = new SLLNode*[tableCapacity];
	for(auto index = 0; index < tableCapacity; index++)
		hashTable[index] = nullptr;

	relation = r;
}

/*
 * Complexity:
 * 	Best: Theta(1) when there is no element with the specified hash in the hash table.
 * 	Worst: Theta(n) otherwise.
 * 	Total: Theta(n)
 */
TValue SortedMap::add(TKey k, TValue v)
{
	int position = hash_key(k);

	SLLNode* root = hashTable[position];

	// No element with that hash exists.
	if(root == nullptr)
	{
		root = new SLLNode();
		root->data = TElem(k, v);
		hashTable[position] = root;
		elementCount++;
		return NULL_TVALUE;
	}

	// Find if the element exists and if it does, replace it.
	SLLNode* current = root;
	while(current->next != nullptr)
	{
		if(current->data.first == k)
		{
			TValue oldValue = current->data.second;
			current->data.second = v;
			return oldValue;
		}
		current = current->next;
	}
	
	// Last check.
	if(current->data.first == k)
	{
		TValue oldValue = current->data.second;
		current->data.second = v;
		return oldValue;
	}

	// Look for the position in the map to add.
	current = root;
	SLLNode* previous = nullptr;
	while(current != nullptr && relation(current->data.first, k))
	{
		previous = current;
		current = current->next;
	}

	// Add the element.
	SLLNode* newNode = new SLLNode();
	newNode->data = TElem(k, v);
	newNode->next = current;
	if(previous == nullptr)
		hashTable[position] = newNode;
	else
		previous->next = newNode;

	elementCount++;
	return NULL_TVALUE;
}

/*
 * Complexity:
 * 	Best: Theta(1) when the element is found at the first position or there are no collisions.
 * 	Worst: Theta(n) otherwise.
 * 	Total: Theta(n)
 */
TValue SortedMap::search(TKey k) const
{
	int position = hash_key(k);

	SLLNode* root = hashTable[position];

	// Find the element and return it's value if it exists.
	while(root != nullptr)
	{
		if(root->data.first == k)
			return root->data.second;
		root = root->next;
	}

	return NULL_TVALUE;
}

/*
 * Complexity:
 * 	Best: Theta(1) when the element is found at the first position or there are no collisions.
 * 	Worst: Theta(n) otherwise.
 * 	Total: Theta(n)
 */
TValue SortedMap::remove(TKey k)
{
	int position = hash_key(k);

	SLLNode* root = hashTable[position];

	// No element with that hash exists.
	if(root == nullptr)
		return NULL_TVALUE;

	// Find if the element exists and if it does, remove it.
	SLLNode* current = root, *previous = nullptr;
	while(current->next != nullptr)
	{
		if(current->data.first == k)
		{
			TValue oldValue = current->data.second;
			if(previous == nullptr)
				hashTable[position] = current->next;
			else
				previous->next = current->next;
			delete current;
			elementCount--;
			return oldValue;
		}
		previous = current;
		current = current->next;
	}

	// Last check.
	if(current != nullptr && current->data.first == k)
	{
		TValue oldValue = current->data.second;
		if(previous == nullptr)
			hashTable[position] = current->next;
		else
			previous->next = current->next;
		delete current;
		elementCount--;
		return oldValue;
	}

	return NULL_TVALUE;
}

int SortedMap::size() const
{
	return elementCount;
}

bool SortedMap::isEmpty() const
{
	return (size() == 0);
}

SMIterator SortedMap::iterator() const
{
	return SMIterator(*this);
}

/*
 * Complexity:
 * 	Constant: Theta(n)
 */
SortedMap::~SortedMap()
{
	if(hashTable)
	{
		for(auto index = 0; index < tableCapacity; index++)
		{
			SLLNode* current = hashTable[index];
			while(current != nullptr)
			{
				SLLNode* next = current->next;
				delete current;
				current = next;
			}
		}
		delete[] hashTable;
	}
}
