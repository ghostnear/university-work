#pragma once

#include "SortedMultiMap.h"

class SMMIterator
{
	friend class SortedMultiMap;

private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	int index = 0;
	TElem* _elements = nullptr;

	void tree_inorder_traversal(SortedMultiMap::TreeNode* node);

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
	~SMMIterator();
};

