#ifndef TEMASDA_TREE_HPP
#define TEMASDA_TREE_HPP

#include <iostream>
#include <vector>

#define COUNT 5

using namespace std;

class Tree {

public:
    struct Node {
        int id;
        char data;
        int frequency;
        Node *left;
        Node *right;
    };

private:

    static void print2DUtil(Node *rootUtil, int space) {
        if (rootUtil == nullptr)
            return;

        space += COUNT;

        print2DUtil(rootUtil->right, space);

        cout << endl;
        for (int i = COUNT; i < space; i++)
            cout << " ";
        cout << rootUtil->data << "[" << rootUtil->frequency << "]\n";

        print2DUtil(rootUtil->left, space);
    }

public:

    static Node *createTreeNode(char data, int frequency, int customId = -1) {
        static int globalId = 0;
        auto *node = new Node;
        node->id = customId == -1 ? globalId++ : customId;
        node->data = data;
        node->frequency = frequency;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    static void print2D(Node* rootUtil) {
        print2DUtil(rootUtil, 0);
    }

    static void deleteBinaryTree(Node* root) {
        if (root == nullptr) {
            return;
        }

        deleteBinaryTree(root->left);
        deleteBinaryTree(root->right);

        delete root;
    }

    static Node *findInVector(vector<Node *>& vec, int find) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i]->id == find) {
                Node *curr = vec[i];
                vec.erase(vec.begin() + i);
                return curr;
            }
        }
        return nullptr;
    }

};


#endif
