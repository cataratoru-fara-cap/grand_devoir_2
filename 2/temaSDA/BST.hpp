#ifndef TEMASDA_BST_HPP
#define TEMASDA_BST_HPP

#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "Tree.hpp"

using namespace std;

class BST {
private:

    Tree::Node *root = nullptr;

    void buildTree(Tree::Node** tree, vector<std::pair<int, char>> arr, int start, int end);

public:

    explicit BST(const string& sequence);

    ~BST();

    void print();

    void insertBST(char data, int frequency, int customId = -1);

    Tree::Node *removeMin();

};


#endif
