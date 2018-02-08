#include <iostream>
#include <chrono>
#include <set>
#include "part2/AVL.hh"

using namespace std;
using namespace part2;
typedef unsigned long ulong;

string TimeAVLInsertion(ulong N)
{
  Node<ulong> *root = nullptr;
  ulong i = 0;
  auto start = chrono::high_resolution_clock::now();
  for (; i < N; ++i) root = Insert(root, i);
  auto end = chrono::high_resolution_clock::now();
  Destroy(root);
  return to_string(chrono::duration<double>(end - start).count()).substr(0, 6) + "s";
}

string TimeAVLDeletion(ulong N)
{
  Node<ulong> *root = nullptr;
  for (ulong i = 0; i < N; ++i) root = Insert(root, i);
  ulong i = 0;
  auto start = chrono::high_resolution_clock::now();
  for (i = 0; i < N; ++i) root = Erase(Find(root, i));
  auto end = chrono::high_resolution_clock::now();
  return to_string(chrono::duration<double>(end - start).count()).substr(0, 6) + "s";
}

string TimeAVLIteration(ulong N)
{
  Node<ulong> *root = nullptr;
  for (ulong i = 0; i < N; ++i) root = Insert(root, i);
  auto it = Begin(root);
  auto start = chrono::high_resolution_clock::now();
  for (; it != End(root); ++it);
  auto end = chrono::high_resolution_clock::now();
  return to_string(chrono::duration<double>(end - start).count()).substr(0, 6) + "s";
}

string TimeSTLInsertion(ulong N)
{
  set<ulong> stl_set {};
  ulong i = 0;
  auto start = chrono::high_resolution_clock::now();
  for (; i < N; ++i) stl_set.insert(i);
  auto end = chrono::high_resolution_clock::now();
  return to_string(chrono::duration<double>(end - start).count()).substr(0, 6) + "s";
}

string TimeSTLDeletion(ulong N)
{
  set<ulong> stl_set {};
  for (ulong i; i < N; ++i) stl_set.insert(i);
  ulong i = 0;
  auto start = chrono::high_resolution_clock::now();
  for (; i < N; ++i) stl_set.insert(i);
  auto end = chrono::high_resolution_clock::now();
  return to_string(chrono::duration<double>(end - start).count()).substr(0, 6) + "s";
}

double TimeSTLIteration(ulong N)
{
  set<ulong> stl_set {};
  for (ulong i; i < N; ++i) stl_set.insert(i);
  auto start = chrono::high_resolution_clock::now();
  for (auto it = stl_set.begin(); it != stl_set.end(); ++it);
  auto end = chrono::high_resolution_clock::now();
  return chrono::duration<double>(end - start).count();
}


int main()
{
  string col = string(2, '-');
  string AVL = "          AVL           ";
  string STL = "          STL           ";
  auto blank = [](size_t n) -> string { return string(n, ' '); };
  auto dash = [](size_t n) -> string { return string(n, '-'); };
  cout << dash(29) << " Insertion " << dash(27) << '\n';
  cout << "  Number of Nodes   " << col << AVL << col << STL << " \n";
  cout << blank(7) << to_string((ulong)1e5) << blank(7) << col << blank(8) << TimeAVLInsertion(1e5) << blank(9) << col << blank(8) << TimeSTLInsertion(1e5) << " \n";
  cout << blank(6) << to_string((ulong)1e6) << blank(7) << col << blank(8) << TimeAVLInsertion(1e6) << blank(9) << col << blank(8) << TimeSTLInsertion(1e6) << " \n";
  cout << blank(5) << to_string((ulong)1e7) << blank(7) << col << blank(8) << TimeAVLInsertion(1e7) << blank(9) << col << blank(8) << TimeSTLInsertion(1e7) << " \n";
  cout << dash(29) << " Deletion " << dash(28) << '\n';
  cout << "  Number of Nodes   " << col << AVL << col << STL << " \n";
  cout << blank(7) << to_string((ulong)1e5) << blank(7) << col << blank(8) << TimeAVLDeletion(1e5) << blank(9) << col << blank(8) << TimeSTLDeletion(1e5) << " \n";
  cout << blank(6) << to_string((ulong)1e6) << blank(7) << col << blank(8) << TimeAVLDeletion(1e6) << blank(9) << col << blank(8) << TimeSTLDeletion(1e6) << " \n";
  cout << blank(5) << to_string((ulong)1e7) << blank(7) << col << blank(8) << TimeAVLDeletion(1e7) << blank(9) << col << blank(8) << TimeSTLDeletion(1e7) << " \n";
  cout << dash(29) << " Iteration " << dash(27) << '\n';
  cout << "  Number of Nodes   " << col << AVL << col << STL << " \n";
  cout << blank(7) << to_string((ulong)1e5) << blank(7) << col << blank(8) << TimeAVLIteration(1e5) << blank(9) << col << blank(8) << TimeSTLIteration(1e5) << "s\n";
  cout << blank(6) << to_string((ulong)1e6) << blank(7) << col << blank(8) << TimeAVLIteration(1e6) << blank(9) << col << blank(8) << TimeSTLIteration(1e6) << "s\n";
  cout << blank(5) << to_string((ulong)1e7) << blank(7) << col << blank(8) << TimeAVLIteration(1e7) << blank(9) << col << blank(8) << TimeSTLIteration(1e7) << "s\n";
  cout << dash(67) << '\n';
  return 0;
}
