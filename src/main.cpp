// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    const char* fName = "src/war_peace.txt";

    std::cout << "Building tree from file: " << fName << "\n";
    makeTree(tree, fName);

    std::cout << "Tree depth: " << tree.depth() << "\n";

    const std::string testWord = "war";     
    if (tree.search(testWord))
        std::cout << "'" << testWord << "' found in tree.\n";
    else
        std::cout << "'" << testWord << "' NOT found in tree.\n";

    std::cout << "\nWord frequencies:\n";
    printFreq(tree);

    return 0;
}
