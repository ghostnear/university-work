#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

SortedMap::SortedMap(Relation r)
{
	containerSize = count = 0;
	containerCapacity = 1;
	data = new DLLNode[1];
	start = -1;
	comp = r;
}

/*
 * Complexity:
 * 	Constant: Theta(n)
 */
void SortedMap::resize(int newCapacity)
{
	// Create new data and copy old data.
	DLLNode* newData = new DLLNode[newCapacity];
	for(auto index = 0; index < containerSize; index++)
		newData[index] = data[index];

	delete[] data;
	data = newData;
	containerCapacity = newCapacity;
}

/*
 * Complexity:
 * 	Best: Theta(1) when the element should be the first element, and no resize is required as the first slot in the array is empty.
 * 	Worst: Theta(n) when the element should be the last element and resizing is required.
 * 	Total: Theta(n)
 */
TValue SortedMap::add(TKey k, TValue v)
{
	// Find if the key already exists. If so, replace the value.
	auto index = start;
	while(index != -1)
	{
		if(data[index].data.first == k)
		{
			auto oldValue = data[index].data.second;
			data[index].data.second = v;
			return oldValue;
		}
		index = data[index].next;
	}

	count++;
	
	// If the container is empty, add the element as the first element.
	if(start == -1)
	{
		start = 0;
		data[0].data = TElem(k, v);
		containerSize = 1;
		if (containerSize == containerCapacity)
			resize(containerCapacity * 2);
		return NULL_TVALUE;
	}

	// If the container is not empty, find the position where the element should be added.
	index = start;
	while(index != -1 && comp(data[index].data.first, k))
		index = data[index].next;

	// Find first empty space.
	auto firstEmpty = 0;
	for(firstEmpty = 0; firstEmpty < containerSize; firstEmpty++)
		if(data[firstEmpty].data == NULL_TPAIR)
			break;

	// No empty space, resize.
	if(firstEmpty == containerSize)
	{
		containerSize++;
		if(containerSize == containerCapacity)
			resize(containerCapacity * 2);
	}

	// If the element should be added at the beginning, update the start.
	if(index == start)
	{
		data[firstEmpty].data = TElem(k, v);
		data[firstEmpty].next = start;
		data[start].previous = firstEmpty;
		start = firstEmpty;
		return NULL_TVALUE;
	}

	// If the element should be added at the end, update the last element.
	if(index == -1)
	{
		// Find the last element.
		index = start;
		while(data[index].next != -1)
			index = data[index].next;

		data[firstEmpty].data = TElem(k, v);
		data[firstEmpty].previous = index;
		data[index].next = firstEmpty;
		return NULL_TVALUE;
	}

	// If the element should be added in the middle, update the previous and next elements.
	data[firstEmpty].data = TElem(k, v);
	data[firstEmpty].previous = data[index].previous;
	data[firstEmpty].next = index;
	data[data[index].previous].next = firstEmpty;
	data[index].previous = firstEmpty;

	return NULL_TVALUE;
}

/*
 * Complexity:
 * 	Best: Theta(1) when the element is the first element.
 * 	Worst: Theta(n) when the element is the last element.
 * 	Total: Theta(n)
 */
TValue SortedMap::search(TKey k) const
{
	// Find the element with the given key.
	auto index = start;
	while(index != -1)
	{
		if(data[index].data.first == k)
			return data[index].data.second;
		index = data[index].next;
	}

	return NULL_TVALUE;
}

/*
 * Complexity:
 * 	Best: Theta(1) when the element is the first element.
 * 	Worst: Theta(n) when the element is the last element.
 * 	Total: Theta(n)
 */ 
TValue SortedMap::remove(TKey k)
{
	// Look for the element.
	auto index = start;
	while(index != -1)
	{
		if(data[index].data.first == k)
		{
			// If the element is the first element, update only the start.
			if(index == start)
			{
				start = data[index].next;
				if(start != -1)
					data[start].previous = -1;
			}
			else
			{
				// Update the next and previous elements.
				data[data[index].previous].next = data[index].next;
				if(data[index].next != -1)
					data[data[index].next].previous = data[index].previous;
			}

			// Mark the space as empty.
			auto oldValue = data[index].data.second;
			data[index].data = NULL_TPAIR;
			data[index].previous = -1;
			data[index].next = -1;
			count--;
			return oldValue;
		}
		index = data[index].next;
	}

	return NULL_TVALUE;
}

int SortedMap::size() const
{
	return count;
}

bool SortedMap::isEmpty() const
{
	return size() == 0;
}

SMIterator SortedMap::iterator() const
{
	return SMIterator(*this);
}

SortedMap::~SortedMap()
{
	if(data)
		delete[] data;
}
