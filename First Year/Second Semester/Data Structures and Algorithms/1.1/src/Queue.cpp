#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;

Queue::Queue()
{
	// Nothing inside yet.
	size = left = right = 0;

	// 1 element initial capacity.
	capacity = 1;
	data = new TElem[1];
}

void Queue::resize(int newCapacity)
{
	// Create new data, copy the old ones in and then delete the old one.
	TElem* newData = new TElem[newCapacity];

	// Normal case, left[...]right
	if(left < right)
	{
		for(int index = left; index < right; index++)
			newData[index - left] = data[index];
	}
	// Inverted case left[...]capacity - 1 + 0[...]right - 1
	else
	{
		int position = 0;
		for(int index = left; index < capacity; index++)
			newData[position++] = data[index];
			
		for(int index = 0; index < right; index++)
			newData[position++] = data[index];
	}
	left = 0;
	right = size;
	capacity = newCapacity;

	delete[] data;
	data = newData;
}

void Queue::push(TElem elem)
{
	// Save the new element.
	size++;
	data[right++] = elem;

	// If full, double the capacity.
	if(size == capacity)
		resize(capacity * 2);

	// Loop back.
	if(right == capacity)
		right = 0;
}

TElem Queue::top() const
{
	if(size == 0)
		throw exception();

	return data[left];
}

TElem Queue::pop()
{
	// Empty queue, error.
	if(size == 0)
		throw exception();

	// Get old result and advance.
	TElem result = data[left++];
	size--;

	// If not full, halve the capacity.
	if(size < capacity / 4 && size != 0)
		resize(capacity / 2);

	// Loop back.
	if(left == capacity)
		left = 0;

	return result;
}

bool Queue::isEmpty() const
{
	return size == 0;
}


Queue::~Queue()
{
	delete[] data;
}

