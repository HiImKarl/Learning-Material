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
		for (int j = -9; j <= 9; ++j) 
			root = Insert(root, j);

	SECTION("Tree size") {
		REQUIRE(CountNodes(root) == 951);
	}

	SECTION("Insertion") {
		vector<int> vec {0};
		vec.reserve(951);
		for (size_t i = 0; i < 50; ++i) 
			for (int j = -9; j <= 9; ++j) 
				vec.push_back(j);
		std::sort(vec.begin(), vec.end());
		vector<int> inorder_traversal {};
		InOrderTraversal(root, inorder_traversal);
		REQUIRE(vec == inorder_traversal);
	}

	for (size_t i = 0; i < 25; ++i) 
		for (int j = -9; j <= 9; ++j)
			root = Erase(root, j);

	SECTION("Deletion") {
		vector<int> vec {0};
		vec.reserve(476);
		for (size_t i = 0; i < 25; ++i) 
			for (int j = -9; j <= 9; ++j) 
				vec.push_back(j);
		std::sort(vec.begin(), vec.end());
		vector<int> inorder_traversal {};
		InOrderTraversal(root, inorder_traversal);
		REQUIRE(vec == inorder_traversal);
	}
}

TEST_CASE("Part2 Tree methods", "[AVL]") {
	using namespace part2;
	auto root = new Node<int>(0);
	for (size_t i = 0; i < 50; ++i) 
		for (int j = -9; j <= 9; ++j) 
			root = Insert(root, j);

	SECTION("Tree size") {
		REQUIRE(CountNodes(root) == 951);
	}

	SECTION("Insertion") {
		vector<int> vec {0};
		vec.reserve(951);
		for (size_t i = 0; i < 50; ++i) 
			for (int j = -9; j <= 9; ++j) 
				vec.push_back(j);
		std::sort(vec.begin(), vec.end());
		vector<int> inorder_traversal {};
		InOrderTraversal(root, inorder_traversal);
		REQUIRE(vec == inorder_traversal);
	}

	for (size_t i = 0; i < 25; ++i) {
		for (int j = -9; j <= 9; ++j) {
			auto node = Find(root, j);
			root = Erase(node);
		}
	}

	SECTION("Deletion") {
		vector<int> vec {0};
		vec.reserve(476);
		for (size_t i = 0; i < 25; ++i) 
			for (int j = -9; j <= 9; ++j) 
				vec.push_back(j);
		std::sort(vec.begin(), vec.end());
		vector<int> inorder_traversal {};
		InOrderTraversal(root, inorder_traversal);
		REQUIRE(vec == inorder_traversal);
	}
}