#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node
{
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBST(const vector<Node> &tree, int index, int min, int max)
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
  return IsBST(tree, 0, INT_MIN, INT_MAX);
}

int main()
{
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i)
  {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree))
  {
    cout << "CORRECT" << endl;
  }
  else
  {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
