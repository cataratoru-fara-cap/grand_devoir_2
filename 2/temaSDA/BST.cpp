#include "BST.hpp"

void BST::buildTree(Tree::Node** tree, vector<std::pair<int, char>> arr, int start, int end) {
    if (*tree != nullptr) {
        return;
    }
    if (start == end) {
        return;
    }
    int nodeIndex = (start + end) / 2;
    *tree = Tree::createTreeNode(arr[nodeIndex].second, arr[nodeIndex].first);
    this->buildTree(&(*tree)->left, arr, start, nodeIndex);
    this->buildTree(&(*tree)->right, arr, nodeIndex + 1, end);
}

BST::BST(const string& sequence) {
    unordered_map<char, int> frequency;
    for (char c : sequence) {
        if (frequency.find(c) == frequency.end()) {
            frequency[c] = 1;
        } else {
            frequency[c]++;
        }
    }

    std::vector<std::pair<int, char>> valueKeyPairs;

    for (const auto& pair : frequency) {
        valueKeyPairs.emplace_back(pair.second, pair.first);
    }
    std::sort(valueKeyPairs.begin(), valueKeyPairs.end());

    this->buildTree(&root, valueKeyPairs, 0, static_cast<int>(valueKeyPairs.size()));
}

BST::~BST() {
    Tree::deleteBinaryTree(root);
}

void BST::print() {
    Tree::print2D(root);
}

void BST::insertBST(char data, int frequency, int customId) {
    Tree::Node *node = Tree::createTreeNode(data, frequency, customId);

    if (root == nullptr) {
        root = node;
        return;
    }
    bool placeLeft;
    Tree::Node *curr = root;
    Tree::Node *currNext;

    if (frequency < curr->frequency) {
        currNext = curr->left;
        placeLeft = true;
    } else {
        currNext = curr->right;
        placeLeft = false;
    }
    while (currNext != nullptr) {
        curr = currNext;
        if (frequency < currNext->frequency) {
            currNext = currNext->left;
            placeLeft = true;
        } else {
            currNext = currNext->right;
            placeLeft = false;
        }
    }
    if (placeLeft) {
        curr->left = node;
    } else {
        curr->right = node;
    }
}

Tree::Node *BST::removeMin() {
    if (root == nullptr)
        return nullptr;

    Tree::Node *parent = nullptr;
    Tree::Node *minNode = root;
    while (minNode->left != nullptr) {
        parent = minNode;
        minNode = minNode->left;
    }

    if (parent == nullptr) {
        root = minNode->right;
    } else {
        parent->left = minNode->right;
    }
    minNode->left = nullptr;
    minNode->right = nullptr;
    return minNode;
}