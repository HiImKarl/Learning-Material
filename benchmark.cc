#include <iostream>
#include <chrono>
#include "part2/AVL.hh"

using namespace std;
using namespace part2;

double TimeAVLInsertion(unsigned long N)
{
	Node<unsigned long> *root = nullptr;
	unsigned long i = 0;
	auto start = chrono::high_resolution_clock::now();
	for (; i < N; ++i) root = Insert(root, i);
	auto end = chrono::high_resolution_clock::now();
	Destroy(root);
	return chrono::duration<double>(end - start).count();
}

int main()
{
	std::cout << TimeAVLInsertion(10000000) << "s\n";
}