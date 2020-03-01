#include "SuffixTree.h"

SuffixTree::SuffixTree(std::string text) : rootNodePtr() {
    text += "$";
    rootNodePtr = new Node ();
    for(int i = 0; i < text.length(); ++i) {
        // Loop through each substring, and insert it to the suffix tree
        insertSuffixString(text.substr(i), i);
    }
}

SuffixTree::~SuffixTree() {
    rootNodePtr->cleanNode();
    delete rootNodePtr;
}

void SuffixTree::Node::cleanNode() {
    if(!childrenPtrs.empty()) {
        auto it = childrenPtrs.begin();
        while(it != childrenPtrs.end()) {
            if(nullptr != it->second){
                it->second->cleanNode();
                delete it->second;
            }
            ++it;
        }
    }
}

void SuffixTree::insertSuffixString(std::string text, int offset) {
    int i = 0;
    auto* cur = getRoot();

    // follow the path of the tree, that matches with a prefix of the suffix
    // string, and add the suffix of the suffix string as a new node.
    while (i < text.length()) {
        auto* childrenPtrs = cur->getChildrenPtrs();
        auto it = childrenPtrs->find(text.substr(i, 1));

        if(it == childrenPtrs->end()) {
        // if the last node of the path does not have a child that starts with
        // the first character of the suffix, we add the suffix as a new node
            Node* newChildNode = new Node (text.substr(i));
            newChildNode->parentPtr = cur;
            newChildNode->offset = offset;
            childrenPtrs->insert({text.substr(i,1), newChildNode});
        } else {
        // if the last node of the path has a child that stars with the first
        // character of the suffix, we seperat the child node into two.
            Node* childNode = it->second;
            int k = i + 1;
            std::string& label = childNode->label;
            while(k - i < label.length() && text[k] == label[k-i]) ++k;
            if (k-i == label.length()){
                cur = childNode;
                i = k;
            } else {
                Node* leftHalfNode = new Node (label.substr(0, k-i));
                leftHalfNode->childrenPtrs.insert({label.substr(k-i,1), childNode});
                Node* newNode = new Node (text.substr(k));
                newNode->parentPtr = leftHalfNode;
                newNode->offset = offset;
                leftHalfNode->childrenPtrs.insert({text.substr(k,1), newNode});
                childNode->label = label.substr(k-i);
                childNode->parentPtr = leftHalfNode;
                leftHalfNode->parentPtr = cur;
                it->second = leftHalfNode;
            }
        }
    }
}

SuffixTree::Node* SuffixTree::followPath(const std::string& text) const {
    Node* cur = getRoot();
    int i = 0;
    while ( i < text.length()) {
        auto it = cur->childrenPtrs.find(text.substr(i, 1));
        if(it == cur->childrenPtrs.end()){
            std::cout << "Exit here" << std::endl;
            return nullptr;
        };
        Node* childNode = it->second;
        std::string & childNodeLabel = childNode->label;
        int j = i + 1;
        while (j - i < childNodeLabel.length() && j < text.length() && 
            text.substr(j,1) == childNodeLabel.substr(j-i, 1))
            ++j;
        if(j - i == childNodeLabel.length()){
            cur = childNode;
            i = j;
        } else if (j == text.length()) {
            return childNode;
        } else {
            return nullptr;
        }
    }
    return cur;
}

std::vector<int> SuffixTree::query(const std::string& text) const {
    Node* hitNode = followPath(text);
    if(nullptr == hitNode) {
        std::cout << "Here" << std::endl;
        std::vector<int> res;
        return res;
    }
    return hitNode->getAllOccurrence_();
}

std::vector<int> SuffixTree::Node::getAllOccurrence_() const {
    std::vector<int> offsets;
    if(offset != -1){
        offsets.push_back(offset);
    }
    if(childrenPtrs.empty()) return offsets; 
    for(auto it = childrenPtrs.begin(); it != childrenPtrs.end(); ++it) {
        std::vector<int> childOffsets = it->second->getAllOccurrence_();
        offsets.insert(offsets.begin(), childOffsets.begin(), childOffsets.end());
    }
    return offsets;
}

void SuffixTree::printTree() const {
    std::cout << "SuffixTree: " << std::endl;
    rootNodePtr->printLabel(0);
}

void SuffixTree::Node::printLabel(int ind) const {
    std::string ph (ind, '-');
    std::cout << ph << label << " this=" << this;
    if (offset != -1) std::cout << " offset=" << offset;
    std::cout << std::endl;

    for(auto it = childrenPtrs.begin(); it != childrenPtrs.end(); ++it) {
        it->second->printLabel(ind + label.length());
    }
}