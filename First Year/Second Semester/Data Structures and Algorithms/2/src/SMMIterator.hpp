#pragma once

#include "SortedMultiMap.hpp"

class SMMIterator
{
	// Has access to private stuff.
	friend class SortedMultiMap;

private:
	// Stored refference to the OG map.
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	// Internal representation of the SMMIterator.
	SortedMultiMap::DLLNode* index;

public:
	// Start of the container.
	void first();

	// Next element.
	void next();

	// If is still ok.
	bool valid() const;

	// Get value of element.
   	TElem getCurrent() const;
};

