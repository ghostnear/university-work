#include "SMMIterator.h"
#include "SortedMultiMap.h"

/*
 * Complexity:
 * 	Constant: Theta(n)
 */
void SMMIterator::tree_inorder_traversal(SortedMultiMap::TreeNode* node)
{
	if(node == nullptr)
		return;

	tree_inorder_traversal(node->left);
	for(int i = 0; i < node->data.size(); i++)
		_elements[index++] = TElem(node->key, node->data[i]);
	tree_inorder_traversal(node->right);
}

/*
 * Complexity:
 * 	Constant: Theta(n)
 */
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d)
{
	this->_elements = new TElem[d.size()];
	tree_inorder_traversal(d._root);
	first();
}

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
void SMMIterator::first()
{
	index = 0;
}

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
void SMMIterator::next()
{
	if(!valid())
		throw std::exception();

	index++;
}

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
bool SMMIterator::valid() const
{
	return index >= 0 && index < map.size();
}

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
TElem SMMIterator::getCurrent() const
{
	if(!valid())
		throw std::exception();

	return this->_elements[index];
}

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
SMMIterator::~SMMIterator()
{
	delete[] _elements;
}


