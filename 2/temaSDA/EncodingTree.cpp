#include "EncodingTree.hpp"

void EncodingTree::buildPairs() {
    struct tempNode {
        Tree::Node *curr;
        Tree::Node *prev;
        bool left;
    };

    stack<tempNode *> trace;
    tempNode *utilAddress;
    unordered_map<int, string> visited;

    utilAddress = new tempNode;
    utilAddress->curr = root;
    utilAddress->prev = nullptr;
    trace.push(utilAddress);
    while (!trace.empty()) {
        tempNode *curr = trace.top();
        trace.pop();

        string base;
        if (curr->prev != nullptr) {
            if (visited.find(curr->prev->id) != visited.end()) {
                base += visited[curr->prev->id];
            }
            if (curr->left) {
                visited[curr->curr->id] = base + "0";
            } else {
                visited[curr->curr->id] = base + "1";
            }

            if (curr->curr->data != '\0') {
                if (visited[curr->curr->id].length() > maxCardinal) {
                    maxCardinal = static_cast<int>(visited[curr->curr->id].length());
                }
                encoding[curr->curr->data] = visited[curr->curr->id];
                decoding[visited[curr->curr->id]] = curr->curr->data;
            }
        }

        if (curr->curr->right != nullptr && visited.find(curr->curr->right->id) == visited.end()) {
            utilAddress = new tempNode;
            utilAddress->curr = curr->curr->right;
            utilAddress->prev = curr->curr;
            utilAddress->left = false;
            trace.push(utilAddress);
        }
        if (curr->curr->left != nullptr && visited.find(curr->curr->left->id) == visited.end()) {
            utilAddress = new tempNode;
            utilAddress->curr = curr->curr->left;
            utilAddress->prev = curr->curr;
            utilAddress->left = true;
            trace.push(utilAddress);
        }
        delete curr;
    }
}

EncodingTree::EncodingTree(BST *bst) {
    vector<Tree::Node *> util;
    while (true) {
        Tree::Node *node1 = bst->removeMin();
        Tree::Node *node2 = bst->removeMin();
        if (!node2) {
            break;
        }
        Tree::Node *curr = Tree::createTreeNode('\0', node1->frequency + node2->frequency);
        bst->insertBST('\0', node1->frequency + node2->frequency, curr->id);
        if (node1->data == '\0' && node2->data == '\0') {
            Tree::Node *val1 = Tree::findInVector(util, node1->id);
            Tree::Node *val2 = Tree::findInVector(util, node2->id);

            curr->left = val1;
            curr->right = val2;
        } else if (node1->data == '\0') {
            Tree::Node *val = Tree::findInVector(util, node1->id);

            curr->left = val;
            curr->right = node2;
        } else if (node2->data == '\0') {
            Tree::Node *val = Tree::findInVector(util, node2->id);

            curr->left = node1;
            curr->right = val;
        } else {
            curr->left = node1;
            curr->right = node2;
        }
        util.emplace_back(curr);
    }
    root = util[0];
    buildPairs();
}

void EncodingTree::printHuffmanTree() {
    Tree::print2D(root);
}

void EncodingTree::printEncodings() {
    cout << endl;
    for (auto& pair : encoding) {
        cout << pair.first << "[" << pair.second << "] ";
    }
}

string EncodingTree::encode(const string& sequence) {
    string ret;
    for (char c : sequence) {
        ret += encoding[c];
    }
    return ret;
}

string EncodingTree::decode(string sequence) {
    string ret;
    while (!sequence.empty()) {
        for (int i = maxCardinal; i >= 0; --i) {
            string substr = sequence.substr(0, i);
            if (decoding.find(substr) == decoding.end())
                continue;

            ret += decoding[substr];
            sequence.erase(0, i);
        }
    }
    return ret;
}