// Copyright 2021 NNTU-CS
#include "bst.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: cannot open file '" << filename << "'\n";
        return;
    }

    std::string word;
    int chr;
    while ((chr = file.get()) != EOF) {
        if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z')) {
            word += static_cast<char>(
                        std::tolower(static_cast<unsigned char>(chr)));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
   
    if (!word.empty())
        tree.insert(word);

   
}


static void writeFreq(std::ostream& out,
                      const std::vector<std::pair<std::string, int>>& nodes) {
    out << "Word               | Frequency\n";
    out << "-------------------+----------\n";
    for (const auto& node : nodes) {
        out << node.first;
        
        int padding = 19 - static_cast<int>(node.first.size());
        if (padding > 0)                       
            out << std::string(padding, ' ');
        out << " | " << node.second << "\n";
    }
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

 
    writeFreq(std::cout, nodes);

    
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Error: cannot create 'result/freq.txt'\n";
        return;
    }
  
    writeFreq(outFile, nodes);
    std::cout << "freq.txt created successfully.\n";
}
