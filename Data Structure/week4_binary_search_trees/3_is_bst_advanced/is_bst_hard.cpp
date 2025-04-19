#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <cstdint>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node
{
  long key;
  long left;
  long right;

  Node() : key(0), left(-1), right(-1) {}
  Node(long key_, long left_, long right_) : key(key_), left(left_), right(right_) {}
};

bool IsBST(const vector<Node> &tree, long index, long min, long max)
{
  if (index == -1)
    return true;
  if (tree[index].key < min || tree[index].key > max)
    return false;
  return IsBST(tree, tree[index].left, min, tree[index].key - 1) &&
         IsBST(tree, tree[index].right, tree[index].key, max);
}

bool IsBinarySearchTree(const vector<Node> &tree)
{
  // Implement correct algorithm here
  if (tree.empty())
    return true;
  return IsBST(tree, 0, LONG_MIN, LONG_MAX);
}

int main()
{
  long nodes;
  cin >> nodes;
  vector<Node> tree;
  for (long i = 0; i < nodes; ++i)
  {
    long key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree))
    cout << "CORRECT" << endl;
  else
    cout << "INCORRECT" << endl;
  return 0;
}
