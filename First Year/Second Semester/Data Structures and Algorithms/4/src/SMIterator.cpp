#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

/*
 * Complexity:
 * 	Constant: Theta(n^2)
 */
SMIterator::SMIterator(const SortedMap& m) : map(m)
{
	sorted_results = new TElem[map.size()];

	auto current_table = new SortedMap::SLLNode*[map.tableCapacity];
	for(auto index = 0; index < map.tableCapacity; index++)
		current_table[index] = map.hashTable[index];

	for(auto index = 0; index < map.size(); index++)
	{
		int min_position = -1;
		for(auto position = 0; position < map.tableCapacity; position++)
		{
			if(current_table[position] == nullptr)
				continue;

			if(min_position == -1 || map.relation(current_table[position]->data.first, current_table[min_position]->data.first))
				min_position = position;
		}

		if(min_position != -1)
		{
			sorted_results[index] = current_table[min_position]->data;
			current_table[min_position] = current_table[min_position]->next;
		}
	}

	delete[] current_table;

	first();
}

void SMIterator::first()
{
	position = 0;
}

void SMIterator::next()
{
	if(!valid())
		throw std::exception();

	position++;
}

bool SMIterator::valid() const
{
	return position < map.size();
}

TElem SMIterator::getCurrent() const
{
	if(!valid())
		throw std::exception();

	return sorted_results[position];
}

SMIterator::~SMIterator()
{
	delete[] sorted_results;
}

