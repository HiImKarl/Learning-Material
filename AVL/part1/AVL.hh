#pragma once
#include <cstddef> // for size_t

namespace part1 {

template <typename T>
struct Node {
	typedef T value_type;

	Node(value_type value, Node<T> *left = nullptr, Node<T> *right = nullptr)
	: value(value), left(left), right(right), height(0) {}

	value_type value;
	Node<T> *left;
	Node<T> *right;
	size_t height;
};

// wrap all of the functions that won't be visible in the API
// in a seperate namespace

namespace util {

// The balance factor is defined as Height(right child) - Height(left child)
// We can think of the height of a non-existant child as -1
template <typename T>
int get_balance_factor(Node<T> *node) noexcept
{
	long left_height = (node->left ? node->left->height + 1 : 0);
	long right_height = (node->right ? node->right->height + 1 : 0);
	return right_height - left_height;
}

template <typename T>
void update_height(Node<T> *node) noexcept
{
	size_t left_height = (node->left ? node->left->height + 1: 0);
	size_t right_height = (node->right ? node->right->height + 1: 0);
	node->height = (left_height > right_height ? left_height : right_height);
}

template <typename T>
void left_rotation(Node<T> **head) noexcept
{
	Node<T> *rotated = *head;
	*head = (*head)->right;
	rotated->right = (*head)->left;
	(*head)->left = rotated;
	update_height(rotated);
	update_height(*head);
}

template <typename T>
void right_rotation(Node<T> **head) noexcept
{
	Node<T> *rotated = *head;
	*head = (*head)->left;
	rotated->left = (*head)->right;
	(*head)->right = rotated;
	update_height(rotated);
	update_height(*head);
}

// Right rotate the right child and left rotate the parent
template <typename T>
void right_left_rotation(Node<T> **head) noexcept
{
	right_rotation(&(*head)->right);
	left_rotation(head);
}

// Left rotate the left child and right rotate the parent
template <typename T>
void left_right_rotation(Node<T> **head) noexcept
{
	left_rotation(&(*head)->left);
	right_rotation(head);
}

template <typename T>
void check_for_rotations(Node<T> **node_ptr)
{
	int bf = util::get_balance_factor(*node_ptr);
	// check BF and rotate appropriately
	if (bf >= 2) {
		int left_bf = get_balance_factor((*node_ptr)->right);
		if (left_bf > 0) left_rotation(node_ptr);
		else right_left_rotation(node_ptr);
	} else if (bf <= -2) {
		int right_bf = get_balance_factor((*node_ptr)->left); 
		if (right_bf < 0) right_rotation(node_ptr);
		else left_right_rotation(node_ptr);
	} else {
		update_height(*node_ptr);
	}
}

} // util

template <typename T, typename Container>
void PostOrderTraversal(Node<T> *root, Container &container)
{
	if (!root) return;
	if (root->left) PostOrderTraversal(root->left, container);
	if (root->right) PostOrderTraversal(root->right, container);
	container.push_back(root->value);
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
	// create a new node to insert into the tree,
	Node<T> *new_node = new Node<T>(val);
	if (!root) return new_node;

	// find out where to put the new node
	// keep track of the route moved into the tree
	Node<T> **indirect = &root;
	Node<T> **parents[root->height + 1];
	size_t parents_index = 0;
	while (*indirect) {
		parents[parents_index++] = indirect;
		if ((*indirect)->value < val) indirect = &(*indirect)->right;
		else indirect = &(*indirect)->left;
	}

	// place the new node into tree
	*indirect = new_node;

	// update the height of the tree, applying rotations if necessary
	for (size_t i = 0; i < parents_index; ++i) 
		util::check_for_rotations(parents[parents_index - i - 1]);
	return root;
}

template <typename T>
size_t Height(Node<T> *root) 
{
	return root->height;
}

template <typename T>
size_t CountNodes(Node<T> *root) 
{
	if (!root) return 0;
	size_t count = CountNodes(root->left);
	count += CountNodes(root->right);
	return count + 1;
}

template <typename T>
Node<T> *Erase(Node<T> *root, typename Node<T>::value_type val)
{
	if (!root) /* Throw an exception? */ return nullptr;
	Node<T> **parents[root->height + 1];
	size_t parents_index = 0;

	// find the node to delete
	Node<T> **indirect = &root;
	while (*indirect) {
		if (val == (*indirect)->value) break;
		parents[parents_index++] = indirect;
		if (val > (*indirect)->value) indirect = &(*indirect)->right;
		else indirect = &(*indirect)->left;
	}
	if (!(*indirect)) return root; 
	/* Throw an exception? */

	// find a replacement 
	parents[parents_index++] = indirect;
	if ((*indirect)->left) {
		Node<T> **walk = &(*indirect)->left;
		while ((*walk)->right) {
			parents[parents_index++] = walk;
			walk = &(*walk)->right;
		}
		// replace the value and then delete replacement node
		(*indirect)->value = (*walk)->value;
		Node<T> *tmp = *walk;
		*walk = (*walk)->left;
		delete tmp;
	} else if ((*indirect)->right) {
		Node<T> **walk = &(*indirect)->right;
		while ((*walk)->left) {
			parents[parents_index++] = walk;
			walk = &(*walk)->left;
		}
		(*indirect)->value = (*walk)->value;
		Node<T> *tmp = *walk;
		*walk = (*walk)->right;
		delete tmp;
	} else {
		Node<T> *tmp = *indirect;
		delete tmp;
		*indirect = nullptr;
	}

	// update the new heights, applying rotations if necessary
	for (size_t i = 0; i < parents_index; ++i) {
		util::check_for_rotations(parents[parents_index - 1 - i]);
	}
	return root;
}


template <typename T>
void Destroy(Node<T> *root) noexcept
{
	if (root->left) Destroy(root->left);
	if (root->right) Destroy(root->right);
	delete root;
}

} // namespace part1