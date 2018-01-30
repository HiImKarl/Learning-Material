/*
* @Author: karl
* @Date:   2018-01-22 20:44:10
* @Last Modified by:   karl
* @Last Modified time: 2018-01-29 22:20:08
*/

#include "part1/AVL.hh"
#include "part2/AVL.hh"
#include <queue>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

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
    std::cout << string(terminal_cols, '-') << '\n';
    if (!root) {
    	cout << string(terminal_cols / 2, ' ') << "No tree\n";
    	std::cout << string(terminal_cols, '-') << '\n';
    	return;
    }

	size_t tree_height = root->height + 1;
	size_t max_height = min((size_t)log2(terminal_cols), tree_height);
	queue<decltype(root)> tree_row {};
	tree_row.push(root);

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
    std::cout << string(terminal_cols, '-') << '\n';
}


vector<string> split_string(const string &str, char delim = ' ')
{
	size_t prev = 0;
	vector<string> arr {};
	for (size_t i = 1; i < str.size(); ++i) {
		if (str[i] == delim && prev != i) {
			arr.push_back(str.substr(prev, i - prev));
			prev = i + 1;
		}
	}
	if (prev != str.size()) arr.push_back(str.substr(prev));
	return arr;
}

int main()
{
	part1::Node<int> *root = nullptr;
	string u_input = {};
	vector<string> arr {};
	for (;;) {
		getline(cin, u_input);
		arr = split_string(u_input);
		if (!arr.size()) continue;
		if (arr.front() == "i" || arr.front() == "I") {
			for (size_t i = 1; i < arr.size(); ++i) {
				root = part1::Insert(root, stoi(arr[i]));
			}
		} else if (arr.front() == "e" || arr.front() == "E") {
			for (size_t i = 1; i < arr.size(); ++i) {
				auto valid = part1::Find(root, stoi(arr[i]));
				if (!valid) cout << "Value " << stoi(arr[i]) << " was not found\n";
				else root = part1::Erase(root, stoi(arr[i]));
			}
		} else if (arr.front() == "q" || arr.front() == "Q") {
			part1::Destroy(root);
			return 0;
		} else if (arr.front() == "d" || arr.front() == "D") {
			display_tree(root);
		} else {
			cout << "Unkown option " << arr.front() << '\n';
		}
	}
	return 0;
}
