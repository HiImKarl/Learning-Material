/*
* @Author: karl
* @Date:   2018-01-22 20:44:10
* @Last Modified by:   karl
* @Last Modified time: 2018-01-22 21:35:42
*/

#include "part1/AVL.hh"
#include "part2/AVL.hh"
#include <queue>
#include <cmath>
#include <algorithm>
#include <iostream>

#ifdef __linux__
#include <unistd.h>
#include <sys/ioctl.h>
#endif 

#ifdef _WIN32
#include <windows.h>
#endif

#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

template <typename Node>
void display_tree(Node *root)
{
	size_t terminal_cols;

	#ifdef __linux__
	struct winsize screen;
	ioctl(STDOUT_FILENO,TIOCGWINSZ, &screen);
	terminal_cols = screen.ws_col;
	#endif

	#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    temrinal_cols = csbi.srWindow.Right - csbi.srWindow.Left + 1
    #endif

    // makes sure terminal_cols is a power of two for better displaying
    terminal_cols = (size_t)pow(2, (size_t)log2(terminal_cols));
	size_t tree_height = root->height + 1;
	size_t max_height = min((size_t)log2(terminal_cols), tree_height);
	queue<decltype(root)> tree_row {};
	tree_row.push(root);

	cout << string(terminal_cols, '-') << '\n';
	for (size_t i = 0; i < max_height; ++i) {
		size_t num_nodes = pow(2, i);
		int block_len = terminal_cols / (num_nodes * 2);
		queue<decltype(root)> tmp {};
		while (tree_row.size()) {
			Node *node = tree_row.front();
			string val = (node ? to_string(node->value) : " ");
			string row = "";
			if (block_len - (int)val.size() > 0) row = string(block_len - val.size(), ' ');
			cout << row << val;
			cout << string(block_len , ' ');
			if (node) {
				tmp.push(node->left);
				tmp.push(node->right);
			}
			tree_row.pop();
		}
		cout << '\n';
		tmp.swap(tree_row);
	}
	if (max_height > tree_height) 
		cout << "(" << max_height - tree_height << " rows not shown...)" << '\n';
	cout << string(terminal_cols, '-') << '\n';
}

#include <vector>

int main()
{
	auto root = new part2::Node<int>(0);
	for (int i = 15; i >= -15; --i) root = part2::Insert(root, i);
	auto node = part2::Find(root, 0);
	root = part2::Erase(node);
	display_tree(root);
	vector<int> vec {};
	part2::PostOrderTraversal(root, vec);
	for (int i : vec) cout << i << ' ';
	cout << '\n';
	part2::Destroy(root);
	return 0;
}
