#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

class SuffixTree {
public:
    class Node {
    public:
        Node* parentPtr;
        std::unordered_map< std::string, Node* > childrenPtrs;
        std::string label;
        int offset;

        Node() : parentPtr(nullptr) , offset(-1) {};
        Node(std::string text) : parentPtr(nullptr), label(text), offset(-1) {
            if(label.back() == '$') offset = label.length();
        };
        ~Node() {};
        void cleanNode();

        // Node& operator=(const Node& other) {};

        void addChild(std::string labelArg, int offsetArg);
        std::unordered_map<std::string, Node*>* getChildrenPtrs() { return &childrenPtrs; };
    
        std::vector<int> getAllOccurrence_() const;
        void printLabel (int ind) const;
    };

    Node* rootNodePtr;
    
    SuffixTree() : rootNodePtr() {};
    SuffixTree(std::string text);
    ~SuffixTree();

    Node* getRoot() const { return rootNodePtr; };
    void insertSuffixString(std::string, int offset);
    Node* followPath(const std::string& text) const;
    bool hasSubstring(const std::string& text) const { return nullptr != followPath(text); };
    std::vector<int> query(const std::string& text) const;
    void printTree() const ;
};