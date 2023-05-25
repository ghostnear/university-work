#include "SMMIterator.hpp"
#include "SortedMultiMap.hpp"

#include <vector>
#include <exception>

SortedMultiMap::SortedMultiMap(Relation r)
{
	root = nullptr;
	containerSize = 0;
	comparator = r;
}

/*
 *	Complexity:
 *	O(containerSize)
 *	Best: theta(1) - list is empty.
 *	Worst: theta(containerSize) - new element is added to the list at the end. 
 */
void SortedMultiMap::add(TKey c, TValue v)
{
	// Mark as added.
	containerSize++;

	// Empty container, just add node.
	if(root == nullptr)
	{
		root = new DLLNode();
		root->data = TElem(c, v);
		return;
	}

	DLLNode* currentElement = root;
	while(currentElement->next != nullptr && comparator(currentElement->next->data.first, c))
		currentElement = currentElement->next;

	// Add at the end of the array.
	if(currentElement->next == nullptr && comparator(currentElement->data.first, c))
	{
		currentElement->next = new DLLNode();
		currentElement->next->data = TElem(c, v);
		currentElement->next->previous = currentElement;
		return;
	}

	// Add at the beginning.
	if(currentElement == root)
	{
		// If needs to be added at the front of the root.
		if(comparator(c, root->data.first))
		{
			root = new DLLNode();
			root->data = TElem(c, v);
			root->next = currentElement;
			currentElement->previous = root;
			return;
		}

		// After the root.
		DLLNode* newNode = new DLLNode();
		newNode->data = TElem(c, v);
		newNode->previous = root;
		newNode->next = root->next;
		if(root->next)
			root->next->previous = newNode;
		root->next = newNode;
		return;
	}

	DLLNode* newNode = new DLLNode();
	newNode->data = TElem(c, v);
	currentElement->next->previous = newNode;
	newNode->next = currentElement->next;
	newNode->previous = currentElement;
	currentElement->next = newNode;
}

/*
 *	Complexity:
 *	theta(containerSize) - constant.
 */
std::vector<TValue> SortedMultiMap::search(TKey c) const
{
	std::vector<TValue> results;

	DLLNode* currentElement = root;
	while(currentElement != nullptr)
	{
		if(c == currentElement->data.first)
			results.push_back(currentElement->data.second);
		currentElement = currentElement->next;
	}
	
	return results;
}

/*
 *	Complexity:
 *	O(containerSize)
 *	Best: theta(1) - element was first in list.
 *	Worst: theta(containerSize) - element was last in list or not found.
 */
bool SortedMultiMap::remove(TKey c, TValue v)
{
	DLLNode* currentElement = root;
	containerSize--;
	while(currentElement != nullptr)
	{
		// If element was found, remove it.
		if(TElem(c, v) == currentElement->data)
		{
			// If the beginning needs to be deleted.
			if(currentElement == root)
			{
				// Next element exists.
				if(root->next != nullptr)
				{
					root = root->next;
					root->previous = nullptr;
					delete currentElement;
				}
				else
				{
					delete root;
					root = nullptr;
				}

				return true;
			}

			// If the last element needs to be deleted.
			if(currentElement->next == nullptr)
			{
				currentElement->previous->next = nullptr;
				delete currentElement;
				return true;
			}

			// Any other element.
			currentElement->previous->next = currentElement->next;
			currentElement->next->previous = currentElement->previous;
			delete currentElement;

			return true;
		}

		currentElement = currentElement->next;
	}
	
	// Element not found.
	containerSize++;
	return false;
}

/*
 *	Complexity:
 *	theta(1) - constant.
 */
int SortedMultiMap::size() const
{
	return containerSize;
}

/*
 *	Complexity:
 *	theta(1) - constant.
 */
bool SortedMultiMap::isEmpty() const
{
	return size() == 0;
}

/*
 *	Complexity:
 *	theta(1) - constant.
 */
SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

/*
 *	Complexity:
 *	theta(containerSize) - constant.
 */
void SortedMultiMap::print_linked_list(DLLNode* rootNode)
{
	if(rootNode != nullptr)
	{
		if(rootNode->next != nullptr)
			print_linked_list(rootNode->next);
		printf("Current address: %p\n", rootNode);
		printf("Next address: %p\n", rootNode->next);
		printf("Previous address: %p\n", rootNode->previous);
		printf("Data: \(%d, %d)\n\n", rootNode->data.first, rootNode->data.second);
	}
}

/*
 *	Complexity:
 *	theta(containerSize) - constant.
 */
void SortedMultiMap::free_linked_list(DLLNode* rootNode)
{
	if(rootNode->next != nullptr)
		free_linked_list(rootNode->next);
	delete rootNode;
}

/*
 *	Complexity:
 *	theta(containerSize) - constant.
 */
std::vector<TKey> SortedMultiMap::keySet() const
{
	std::vector<TKey> result;

	DLLNode* currentElement = root;
	while(currentElement != nullptr)
	{
		result.push_back(currentElement->data.first);
		currentElement = currentElement->next;

		while(currentElement != nullptr && (currentElement->previous == nullptr || currentElement->data.first == currentElement->previous->data.first))
			currentElement = currentElement->next;
	}

	return result;
}


SortedMultiMap::~SortedMultiMap()
{
	if(root != nullptr)
		free_linked_list(root);
}
