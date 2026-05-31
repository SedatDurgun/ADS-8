// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <vector>

template <typename T>
class BST {
private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& val)
            : value(val), count(1), left(nullptr), right(nullptr) {
        }
    };

    Node* root;

    Node* insert(Node* node, const T& val) {
        if (!node) return new Node(val);
        if (val < node->value)
            node->left = insert(node->left, val);
        else if (val > node->value)
            node->right = insert(node->right, val);
        else
            node->count++;
        return node;
    }

    Node* searchNode(Node* node, const T& val) const {
        if (!node || node->value == val) return node;
        if (val < node->value)
            return searchNode(node->left, val);
        return searchNode(node->right, val);
    }

    int depth(Node* node) const {
        if (!node) return -1;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inorder(Node* node, std::vector<Node*>& nodes) const {
        if (!node) return;
        inorder(node->left, nodes);
        nodes.push_back(node);
        inorder(node->right, nodes);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const T& val) {
        root = insert(root, val);
    }

    int search(const T& val) const {
        return searchNode(root, val) != nullptr;
    }

    int getCount(const T& val) const {
        Node* nod = searchNode(root, val);
        return nod ? nod->count : 0;
    }

    int depth() const {
        return depth(root);
    }

    std::vector<std::pair<T, int>> getAllNodes() const {
        std::vector<Node*> nodes;
        inorder(root, nodes);
        std::vector<std::pair<T, int>> res;
        res.reserve(nodes.size());
        for (Node* n : nodes)
            res.emplace_back(n->value, n->count);
        return res;
    }

    bool empty() const { return root == nullptr; }
};

#endif  // INCLUDE_BST_H_
