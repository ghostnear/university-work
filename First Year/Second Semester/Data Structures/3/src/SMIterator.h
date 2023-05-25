#pragma once

#include "SortedMap.h"

class SMIterator
{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	std::size_t position;

public:
	void first();
	void next();
	void jumpForward(int k);
	bool valid() const;
    TElem getCurrent() const;
};

