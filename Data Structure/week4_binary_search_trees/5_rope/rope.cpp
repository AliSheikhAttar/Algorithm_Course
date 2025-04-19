#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

// Vertex of a splay tree
struct Vertex {
    // key field stores an index pointing to a character via the initial string.
    int key;
    // Include size to be able to compute order statistics of the key values.
    int size;
    Vertex *left;
    Vertex *right;
    Vertex *parent;

    Vertex(int key) : key(key), size(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

void update(Vertex *v) {
    if (v == nullptr)
        return;
    v->size =
        1 + (v->left != nullptr ? v->left->size : 0) + (v->right != nullptr ? v->right->size : 0);
    if (v->left != nullptr) 
        v->left->parent = v;
    if (v->right != nullptr)
        v->right->parent = v;
}

void small_rotation(Vertex *v) {
    Vertex *parent = v->parent;
    if (parent == nullptr)
        return;
    Vertex *grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex *m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex *m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != nullptr) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex *v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex *&root, Vertex *v) {
    if (v == nullptr)
        return;
    while (v->parent != nullptr) {
        if (v->parent->parent == nullptr) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches the tree for the node in position k (1-based) ~ k-th order statistic
// Assume k in [1, size]
Vertex *find(Vertex *&root, int k) {
    if (k == 0) 
        return nullptr;
    int s{0};
    if (root->left != nullptr) 
        s = root->left->size;
    if (k == s + 1) 
        return root;
    else if (k < s + 1 and root->left != nullptr) 
        return find(root->left, k);
    else if (root->right != nullptr)
        return find(root->right, k - s - 1);
    else
        return nullptr;
}

void split(Vertex *root, int pos, Vertex *&left, Vertex *&right) {
    right = find(root, pos);
    splay(root, right);
    if (right == nullptr) {	
        left = root;
        return;
    }
    left = right->left;
    right->left = nullptr;
    if (left != nullptr) 
        left->parent = nullptr;
    update(left);
    update(right);
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns nullptr.
Vertex *old_find(Vertex *&root, int key) {
    Vertex *v = root;
    Vertex *last = root;
    Vertex *next = nullptr;
    while (v != nullptr) {
        if (v->key >= key && (next == nullptr || v->key < next->key)) 
            next = v;
        last = v;
        if (v->key == key) 
            break;
        if (v->key < key) 
            v = v->right;
        else
            v = v->left;
    }
    splay(root, last);
    return next;
}

// Version of split using the old_find function, used for rope initalization.
void old_split(Vertex *root, size_t key, Vertex *&left, Vertex *&right) {
    right = old_find(root, key);
    splay(root, right);
    if (right == nullptr) {
        left = root;
        return;
    }
    left = right->left;
    right->left = nullptr;
    if (left != nullptr) 
        left->parent = nullptr;
    update(left);
    update(right);
}

Vertex *merge(Vertex *left, Vertex *right) {
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;
    Vertex *min_right = right;
    while (min_right->left != nullptr) 
        min_right = min_right->left;
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

class Rope {
    std::string s;
    Vertex *root = nullptr;

    void insert(int idx) {
        Vertex *left = nullptr;
        Vertex *right = nullptr;
        Vertex *new_vertex = nullptr;
        old_split(root, idx, left, right);
        if (right == nullptr || right->key != idx) 
            new_vertex = new Vertex(idx);
        root = merge(merge(left, new_vertex), right);
    }

    void traverse(Vertex *node, std::stringstream &ss) {
        // In order search of the spaly tree
        if (node == nullptr) 
            return;
        traverse(node->left, ss);
        // output original character
        ss << s[node->key];
        traverse(node->right, ss);
    }

  public:
    Rope(const std::string &s) : s(s){
        for (size_t idx = 0; idx < s.size(); ++idx) 
            insert(idx);
    }

    void process(int i, int j, int k) {
        Vertex *left = nullptr;
        Vertex *middle = nullptr;
        Vertex *right = nullptr;

        split(root, j + 2, middle, right);
        split(middle, i + 1, left, middle);

        root = merge(left, right);

        if (root != nullptr) 
            split(root, k + 1, left, right);
        else
            root = middle;

        root = merge(merge(left, middle), right);

    }

    std::string result() {
        std::stringstream ss;
        traverse(root, ss);
        return ss.str();
    }
};

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
	for (int action_index = 0; action_index < actions; ++action_index)
	{
		int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	std::cout << rope.result() << std::endl;
}
