#pragma once

#include "SortedMap.h"

class SMIterator
{
	friend class SortedMap;

private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	int position;
	TElem* sorted_results;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;

	~SMIterator();
};

