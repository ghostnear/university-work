#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m)
{
	first();
}

void SMIterator::first()
{
	position = map.start;
}

void SMIterator::next()
{
	if(!valid())
		throw std::exception();
	position = map.data[position].next;
}

bool SMIterator::valid() const
{
	return position != -1;
}

/*
 * Complexity:
 * 	Total: Theta(k)
 */
void SMIterator::jumpForward(int k)
{
	if(k <= 0 || !valid())
		throw std::exception();

	while(valid() && k > 0)
	{
		next();
		k--;
	}
}

TElem SMIterator::getCurrent() const
{
	if(!valid())
		throw std::exception();
	return map.data[position].data;
}


