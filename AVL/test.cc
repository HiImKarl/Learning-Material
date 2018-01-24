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
	auto root = new Node<int>(0);
	for (size_t i = 0; i < 50; ++i) 
		for (int j = -90; j <= 90; ++j) 
			root = Insert(root, j);

	SECTION("Empty Insertion") {
		Node<int> *root = Insert<int>(nullptr, 0);
		REQUIRE(root->value == 0);
		REQUIRE(root->height == 0);
		REQUIRE(root->left == nullptr);
		REQUIRE(root->right == nullptr);
	}

	SECTION("Tree size") {
		REQUIRE(CountNodes(root) == 9051);
	}

	SECTION("Insertion") {
		vector<int> vec {0};
		vec.reserve(9051);
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
		vector<int> vec {0};
		vec.reserve(4526);
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
}

TEST_CASE("Part2 Tree methods", "[AVL]") {
	using namespace part2;

	SECTION("Empty Insertion") {
		Node<int> *root = Insert<int>(nullptr, 0);
		REQUIRE(root->value == 0);
		REQUIRE(root->height == 0);
		REQUIRE(root->left == nullptr);
		REQUIRE(root->right == nullptr);
		REQUIRE(root->parent == nullptr);
	}

	auto root = new Node<int>(0);
	for (size_t i = 0; i < 50; ++i) 
		for (int j = -90; j <= 90; ++j) 
			root = Insert(root, j);

	SECTION("Tree size") {
		REQUIRE(CountNodes(root) == 9051);
	}

	SECTION("Insertion") {
		vector<int> vec {0};
		vec.reserve(9051);
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
		vector<int> vec {0};
		vec.reserve(4526);
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
}