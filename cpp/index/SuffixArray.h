/**
 *  An implementation of suffix array using AVL tree.
 * 
 * @author Chenghao Zhu <chhzhu@ucdavis.edu>
 */

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class SuffixArray {
private:
    // AVLtree node
    class Node {
    public:
        const int offset;
        Node* left;
        Node* right;
        int height_;
        Node(const int& offsetValue) : offset(offsetValue), left(nullptr), right(nullptr), height_(0){};
    };
    Node *head_;
    std::string text_;

    void _insertSuffix(int i);
    void _findAndInsert(int i, Node*& cur);

    bool _firstOccIsLarger(int first, int second) const;
    void _ensureBalance(Node *& node);
    int _getBalanceFactor(Node *& node);
    void _rotateLeft(Node *& node);
    void _rotateRight(Node *& node);
    void _rotateLeftRight(Node *& node);
    void _rotateRightLeft(Node *& node);
    void _updateHeight(Node *& node);
    Node* _find(std::string x, Node *& cur);
    std::vector<int> _findAll(std::string x, Node *& cur);
    int _getHeight(Node *& node);
    void _printSubTree(Node *& cur);
    void _cleanNode(Node *& node);

public:
    SuffixArray() : text_() {};
    SuffixArray(std::string text);
    ~SuffixArray();
    
    std::vector<int> query(std::string x) ;
    bool has(std::string x) ;

    void printSuffixArray();
};