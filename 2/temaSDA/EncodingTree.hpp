#ifndef TEMASDA_ENCODINGTREE_HPP
#define TEMASDA_ENCODINGTREE_HPP

#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "Tree.hpp"
#include "BST.hpp"

using namespace std;

class EncodingTree {
private:

    Tree::Node *root = nullptr;

    int maxCardinal = 0;
    unordered_map<char, string> encoding;
    unordered_map<string, char> decoding;

    void buildPairs();

public:

    explicit EncodingTree(BST *bst);

    void printHuffmanTree();

    void printEncodings();

    string encode(const string& sequence);

    string decode(string sequence);

};


#endif
