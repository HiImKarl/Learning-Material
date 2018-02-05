#include "part1/AVL.hh"
#include "part2/AVL.hh"
#include <vector>
#include <iostream>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Part1 Tree methods", "[AVL]") {
	using namespace part1;

	SECTION("Empty Insertion") {
		Node<int> *single = Insert<int>(nullptr, 0);
		REQUIRE(single->value == 0);
		REQUIRE(single->height == 0);
		REQUIRE(single->left == nullptr);
		REQUIRE(single->right == nullptr);
	}

	Node<int> *root = nullptr;
	for (size_t i = 0; i < 50; ++i) 
		for (int j = -90; j <= 90; ++j) 
			root = Insert(root, j);

	SECTION("Tree size") {
		REQUIRE(CountNodes(root) == 9050);
	}

	SECTION("Insertion") {
		vector<int> vec {};
		vec.reserve(9050);
		for (size_t i = 0; i < 50; ++i) 
			for (int j = -90; j <= 90; ++j) 
				vec.push_back(j);
		std::sort(vec.begin(), vec.end());
		vector<int> inorder_traversal {};
		InOrderTraversal(root, inorder_traversal);
		REQUIRE(vec == inorder_traversal);
	}

	SECTION("Tree is balanced after insertions") {
		REQUIRE(AreHeightsCorrect(root));
		REQUIRE(IsTreeBalanced(root));
	}

	for (size_t i = 0; i < 25; ++i) 
		for (int j = -90; j <= 90; ++j)
			root = Erase(root, j);

	SECTION("Deletion") {
		vector<int> vec {};
		vec.reserve(4525);
		for (size_t i = 0; i < 25; ++i) 
			for (int j = -90; j <= 90; ++j) 
				vec.push_back(j);
		std::sort(vec.begin(), vec.end());
		vector<int> inorder_traversal {};
		InOrderTraversal(root, inorder_traversal);
		REQUIRE(vec == inorder_traversal);
	}

	SECTION("Tree is balanced after deletions") {
		REQUIRE(AreHeightsCorrect(root));
		REQUIRE(IsTreeBalanced(root));
	}

	for (size_t i = 0; i < 25; ++i) {
		for (int j = -90; j <= 90; ++j) {
			root = Erase(root, j);
		}
	}

	SECTION("Delete the rest") {
		REQUIRE(root == nullptr);
	}
}

TEST_CASE("Part2 Tree methods", "[AVL]") {
	using namespace part2;

	SECTION("Empty Insertion") {
		Node<int> *single = Insert<int>(nullptr, 0);
		REQUIRE(single->value == 0);
		REQUIRE(single->height == 0);
		REQUIRE(single->left == nullptr);
		REQUIRE(single->right == nullptr);
		REQUIRE(single->parent == nullptr);
		Destroy(single);
	}

	Node<int> *root = nullptr;
	for (size_t i = 0; i < 50; ++i) 
		for (int j = -90; j <= 90; ++j) 
			root = Insert(root, j);

	SECTION("Tree size") {
		REQUIRE(CountNodes(root) == 9050);
	}

	SECTION("Insertion") {
		vector<int> vec {};
		vec.reserve(9050);
		for (size_t i = 0; i < 50; ++i) 
			for (int j = -90; j <= 90; ++j) 
				vec.push_back(j);
		std::sort(vec.begin(), vec.end());
		vector<int> inorder_traversal {};
		InOrderTraversal(root, inorder_traversal);
		REQUIRE(vec == inorder_traversal);
	}

	SECTION("Tree is balanced after insertions") {
		REQUIRE(AreHeightsCorrect(root));
		REQUIRE(IsTreeBalanced(root));
	}

	for (size_t i = 0; i < 25; ++i) {
		for (int j = -90; j <= 90; ++j) {
			auto node = Find(root, j);
			root = Erase(node);
		}
	}

	SECTION("Deletion") {
		vector<int> vec {};
		vec.reserve(4525);
		for (size_t i = 0; i < 25; ++i) 
			for (int j = -90; j <= 90; ++j) 
				vec.push_back(j);
		std::sort(vec.begin(), vec.end());
		vector<int> inorder_traversal {};
		InOrderTraversal(root, inorder_traversal);
		REQUIRE(vec == inorder_traversal);
	}
	
	SECTION("Tree is balanced after deletions") {
		REQUIRE(AreHeightsCorrect(root));
		REQUIRE(IsTreeBalanced(root));
	}

	for (size_t i = 0; i < 25; ++i) {
		for (int j = -90; j <= 90; ++j) {
			auto node = Find(root, j);
			root = Erase(node);
		}
	}

	SECTION("Delete the rest") {
		REQUIRE(root == nullptr);
	}
}