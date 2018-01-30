#pragma once
#include <cstddef>
#include <iostream>

namespace part2 {

template <typename T>
struct Node {
	typedef T value_type;
	Node(value_type value)
		: value(value), left(nullptr), right(nullptr), parent(nullptr), height(0) 
		{}
	value_type value;
	size_t height;
	Node *left;
	Node *right;
	Node *parent;
};

namespace util {

template <typename T>
int get_balance_factor(Node<T> *node)
{
	long left_height = (node->left ? node->left->height + 1 : 0);
	long right_height = (node->right ? node->right->height + 1 : 0);
	return right_height - left_height;
}

template <typename T>
void update_height(Node<T> *node)
{
	size_t left_height = (node->left ? node->left->height + 1: 0);
	size_t right_height = (node->right ? node->right->height + 1: 0);
	node->height = (left_height > right_height ? left_height : right_height);
}

template <typename T>
void left_rotation(Node<T> **head)
{
	Node<T> *rotated = *head;
	*head = (*head)->right;
	(*head)->parent = rotated->parent; 
	rotated->right = (*head)->left;
	if (rotated->right) rotated->right->parent = rotated;
	(*head)->left = rotated;
	rotated->parent = (*head);
	update_height(rotated);
	update_height(*head);
}

template <typename T>
void right_rotation(Node<T> **head)
{
	Node<T> *rotated = *head;
	*head = (*head)->left;
	(*head)->parent = rotated->parent;
	rotated->left = (*head)->right;
	if (rotated->left) rotated->left->parent = rotated;
	(*head)->right = rotated;
	rotated->parent = (*head);
	update_height(rotated);
	update_height(*head);
}

template <typename T>
void right_left_rotation(Node<T> **head)
{
	right_rotation(&(*head)->right);
	left_rotation(head);
}

template <typename T>
void left_right_rotation(Node<T> **head)
{
	left_rotation(&(*head)->left);
	right_rotation(head);
}

template <typename T>
void check_for_rotations(Node<T> **node_ptr)
{
	int bf = get_balance_factor(*node_ptr);
	if (bf > 1) {
		int left_bf = get_balance_factor((*node_ptr)->right);
		if (left_bf > 0) left_rotation(node_ptr);
		else right_left_rotation(node_ptr);
	} else if (bf < -1) {
		int right_bf = get_balance_factor((*node_ptr)); 
		if (right_bf <= 0) right_rotation(node_ptr);
		else left_right_rotation(node_ptr);
	} else {
		update_height(*node_ptr);
	}
}

// assuming node is not null
template <typename T>
Node<T> **pointer_to_node(Node<T> *node)
{
	Node<T> *parent = node->parent;
	if (parent->left == node) return &(parent->left);
	else return &(parent->right);
} 

template <typename T>
void delete_replacement(Node<T> **replacement, Node<T> *dangling_branch)
{
	Node<T> **node_ptr = util::pointer_to_node(*replacement);
	Node<T> *parent = (*replacement)->parent;
	(*node_ptr) = dangling_branch;
	if (dangling_branch) dangling_branch->parent = parent;
	delete (*replacement);
	*replacement = parent;
}

} // namespace util

template <typename T, typename Container>
void PostOrderTraversal(Node<T> *root, Container &container)
{
	if (!root) return;
	if (root->left) PostOrderTraversal(root->left, container);
	if (root->right) PostOrderTraversal(root->right, container);
}

template <typename T, typename Container>
void InOrderTraversal(Node<T> *root, Container &container)
{
	if (!root) return;
	if (root->left) InOrderTraversal(root->left, container);
	container.push_back(root->value);
	if (root->right) InOrderTraversal(root->right, container);
}	


template <typename T, typename Container>
void PreOrderTraversal(Node<T> *root, Container &container)
{
	if (!root) return;
	container.push_back(root->value);
	if (root->left) PreOrderTraversal(root->left, container);
	if (root->right) PreOrderTraversal(root->right, container);
}

template <typename T>
Node<T> *Insert(Node<T> *root, typename Node<T>::value_type val) 
{
	// create a new node to insert into the tree
	Node<T> *new_node = new Node<T>(val);

	// if root is null the new node becomes the root node
	if (!root) return new_node;

	// find out where to put the new node
	// keep track of the route moved into the tree
	Node<T> **indirect = &root;
	while (*indirect) {
		// update the parent of the new_node
		new_node->parent = *indirect;
		if ((*indirect)->value < val) indirect = &(*indirect)->right;
		else indirect = &(*indirect)->left;
	}

	// place the new node into tree
	*indirect = new_node;
	// update the height of the tree, applying rotations if necessary
	while (new_node->parent) {
		util::check_for_rotations(util::pointer_to_node(new_node));
		new_node = new_node->parent;
	}

	indirect = &root;
	util::check_for_rotations(indirect);
	return root;
}

template <typename T>
size_t Height(Node<T> *root) noexcept { return root->height; }

template <typename T>
size_t CountNodes(Node<T> *root) noexcept
{
	if (!root) return 0;
	size_t count = CountNodes(root->left);
	count += CountNodes(root->right);
	return count + 1;
}

template <typename T>
Node<T> *Find(Node<T> *root, typename Node<T>::value_type val) noexcept
{
	while (root) {
		if (val == root->value) return root;
		if (val > root->value) root = root->right;
		else root = root->left;
	}
	return nullptr;
}

template <typename T>
static void replace_node(Node<T> *target, Node<T> *walk, Node<T> *tail)
{
	target->value = walk->value;
	Node<T> **node_ptr = util::pointer_to_node(walk);
	Node<T> *parent = walk->parent;
	(*node_ptr) = tail;
	if (*node_ptr) (*node_ptr)->parent = parent;
	delete walk;
	walk = parent;
}



template <typename T>
Node<T> *Erase(Node<T> *target) noexcept
{
	Node<T> *walk;
	// find a replacement 
	if (target->left) {
		walk = target->left;
		while (walk->right) {
			walk = walk->right;
		}
		// replace the value and then delete replacement node
		target->value = walk->value;
		delete_replacement(&walk, walk->left);
	} else if (target->right) {
		walk = target->right;
		while (walk->left) 
			walk = walk->left;
		target->value = walk->value;
		delete_replacement(&walk, walk->right);
	} else if (!target->parent) {
		// if the tree is just the single node, return null
		delete target;
		return nullptr;
	} else {
		walk = target;
		delete_replacement(&walk, (Node<T> *)nullptr);
	}

	// update the new heights, applying rotations if necessary
	// traverse until the root node is met
	while (walk->parent) {
		util::check_for_rotations(util::pointer_to_node(walk));
		walk = walk->parent;
	}

	// check if the root node requires a rotation
	Node<T> **root_indirect = &walk;
	util::check_for_rotations(root_indirect);
	return walk;
}

template <typename T>
void Destroy(Node<T> *root)
{
	if (root->left) Destroy(root->left);
	if (root->right) Destroy(root->right);
	delete root;
}

// methods to test the correctness of the tree
// updates heights as it moves along
// returns true if heights are correct
template <typename T>
bool AreHeightsCorrect(Node<T> *root)
{
	bool correct = true;
	if (root->left) correct = correct && IsTreeBalanced(root->left);
	if (root->right) correct = correct && IsTreeBalanced(root->right);
	size_t height = root->height;
	util::update_height(root);
	return (height == root->height && correct);
}

// returns true if balanced false o.w.
template <typename T>
bool IsTreeBalanced(Node<T> *root)
{
	bool balanced = true;
	if (root->left) balanced = balanced && IsTreeBalanced(root->left);
	if (root->right) balanced = balanced && IsTreeBalanced(root->right);
	int bf = util::get_balance_factor(root);
	return (bf <= 1 && bf >= -1 && balanced);
}

} // namespace part2
