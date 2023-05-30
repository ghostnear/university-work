#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <iostream>
#include <exception>
#include <cstring>

using namespace std;

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
SortedMultiMap::SortedMultiMap(Relation r)
{
	this->_relation = r;
}

/*
 * Complexity:
 * 	Best: Theta(1) when the key is in the root.
 * 	Worst: Theta(log2(n)) as log2(n) is the max depth of the tree.
 * 	Total: Theta(log2(n))
 */
void SortedMultiMap::add_tree(TreeNode* &node, TKey c, TValue v)
{
	if(node == nullptr)
	{
		node = new TreeNode();
		node->key = c;
		node->data.push_back(v);
		node->left = nullptr;
		node->right = nullptr;
		return;
	}

	if(node->key == c)
		node->data.push_back(v);
	else if(_relation(node->key, c))
		add_tree(node->right, c, v);
	else
		add_tree(node->left, c, v);
}

/*
 * Complexity:
 * 	Same as add_tree.
 */
void SortedMultiMap::add(TKey c, TValue v)
{
	_size++;
	add_tree(_root, c, v);
}

/*
 * Complexity:
 * 	Best: Theta(1) when the key is in the root.
 * 	Worst: Theta(log2(n)) as log2(n) is the max depth of the tree.
 * 	Total: Theta(log2(n))
 */
SortedMultiMap::TreeNode* SortedMultiMap::search_tree(TreeNode* node, TKey c) const
{
	if(node == nullptr)
		return nullptr;

	if(node->key == c)
		return node;
	else if(_relation(node->key, c))
		return search_tree(node->right, c);
	else
		return search_tree(node->left, c);
}

/*
 * Complexity:
 * 	Same as search_tree.
 */
std::vector<TValue> SortedMultiMap::search(TKey c) const
{
	TreeNode* result = search_tree(_root, c);
	if(result == nullptr)
		return std::vector<TValue>();

	return result->data;
}

/*
 * Complexity:
 *	Same as search_tree.
 */
bool SortedMultiMap::remove(TKey c, TValue v)
{
	TreeNode* node = search_tree(_root, c);
	if(node == nullptr)
		return false;

	for(int i = 0; i < node->data.size(); i++)
		if(node->data[i] == v)
		{
			node->data.erase(node->data.begin() + i);
			_size--;
			return true;
		}

	return false;
}

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
int SortedMultiMap::size() const
{
	return _size;
}

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
bool SortedMultiMap::isEmpty() const
{
	return (size() == 0);
}

/*
 * Complexity:
 * 	Constant: Theta(1)
 */
SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);
}

/*
 * Complexity:
 * 	Constant: Theta(log2(n))
 */
void SortedMultiMap::free_tree(TreeNode* node)
{
	if(node == nullptr)
		return;

	free_tree(node->left);
	free_tree(node->right);

	delete node;
}

/*
 * Complexity:
 *	Same as free_tree.
 */
SortedMultiMap::~SortedMultiMap()
{
	if(_root != nullptr)
		free_tree(_root);
}
