// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "bst.h"
void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string word;
    int chr;
    while ((chr = file.get()) != EOF) {
        if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z')) {
            if (chr >= 'A' && chr <= 'Z')
                chr = chr + ('a' - 'A');
            word += static_cast<char>(chr);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty())
        tree.insert(word);
    file.close();
}
void printFreq(BST<std::string>& tree) {
    auto nodes = tree.getAllNodes();
    std::sort(nodes.begin(), nodes.end(),
        [](const std::pair<std::string, int>& x,
           const std::pair<std::string, int>& y) {
            if (x.second != y.second)
                return x.second > y.second;
            return x.first < y.first;
        });
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cout << "Error creating result/freq.txt!" << std::endl;
        return;
    }
    for (const auto& node : nodes) {
        std::cout << node.first << " " << node.second << "\n";
        outFile   << node.first << " " << node.second << "\n";
    }
    outFile.close();
}
