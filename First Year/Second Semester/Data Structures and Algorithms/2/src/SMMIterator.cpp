#include "SMMIterator.hpp"
#include "SortedMultiMap.hpp"
#include <exception>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d)
{
	first();
}

void SMMIterator::first()
{
	index = map.root;
}

void SMMIterator::next()
{
	if(valid())
		index = index->next;
	else
		throw std::exception();
}

bool SMMIterator::valid() const
{
	return index != nullptr;
}

TElem SMMIterator::getCurrent() const
{
	if(valid())
		return index->data;
	throw std::exception();
}
