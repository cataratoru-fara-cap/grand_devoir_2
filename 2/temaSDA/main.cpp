#include <iostream>
#include <fstream>
#include <string>

#include "BST.hpp"
#include "EncodingTree.hpp"

#define COUNT 5

using namespace std;

string readFile(const string& path) {
    string data;
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return "";
    }
    string line;
    while (std::getline(inputFile, line)) {
        data += line + '\n';
    }
    inputFile.close();
    return data.substr(0, data.size() - 1);
}

bool writeFile(const string& path, const string& data) {
    std::ofstream outputFile(path);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file.\n";
        return false;
    }
    outputFile << data;
    outputFile.close();
    return true;
}

int main() {
    string encodingData = readFile("message.in");

    auto bst = new BST(encodingData);
    cout << "Initial BST:\n";
    bst->print();
    cout << endl;

    auto encodingTree = new EncodingTree(bst);
    cout << "Huffman tree:\n";
    encodingTree->printHuffmanTree();
    cout << endl;

    cout << "Encodings:\n";
    encodingTree->printEncodings();
    cout << endl;

    writeFile("encoded.out", encodingTree->encode(encodingData));

    string decodingData = readFile("encoded.in");
    writeFile("message.out", encodingTree->decode(decodingData));

    delete encodingTree;
    delete bst;
    return 0;
}
