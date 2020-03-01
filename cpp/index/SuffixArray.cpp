#include "SuffixArray.h"
#include <iomanip>

SuffixArray::SuffixArray(std::string text) : head_(nullptr), text_(text + "$") {
    for(int i = text_.length() - 1; i >= 0; --i) {
        _insertSuffix(i);
    }
}

void SuffixArray::_insertSuffix(int i) {
    _findAndInsert(i, head_);
}

void SuffixArray::_findAndInsert(int i, SuffixArray::Node*& cur) {
    if (cur == nullptr) {
        cur = new Node (i);
        return;
    } else if (_firstOccIsLarger(cur->offset, i)) {
        _findAndInsert(i, cur->left);
        _ensureBalance(cur);
    } else {
        _findAndInsert(i, cur->right);
        _ensureBalance(cur);
    }
}

bool SuffixArray::_firstOccIsLarger(int first, int second) const {
    return text_.substr(first).compare(text_.substr(second)) > 0;
}

void SuffixArray::_ensureBalance(SuffixArray::Node *& node) {
    if (node == nullptr) return;
    const int initial_balance = _getBalanceFactor(node);
    if (initial_balance < -2 || initial_balance > 2) {
        std::string msg("ERROR: Detected invalid initial balance factor: ");
        msg += std::to_string(initial_balance);
        throw std::runtime_error(msg);
    }
    if (initial_balance == -2) {
        const int l_balance = _getBalanceFactor(node->left);
        if (l_balance == -1 || l_balance == 0) {
            _rotateRight(node);
        } else if (l_balance == 1) {
            _rotateLeftRight(node);
        } else {
            std::string msg("ERROR: l_balance has unexpected value: ");
            msg += std::to_string(l_balance);
            throw std::runtime_error(msg);
        }
    } else if (initial_balance == 2) {
        const int r_balance = _getBalanceFactor(node->right);
        if (r_balance == -1 || r_balance == 0) {
            _rotateLeft(node);
        } else if (r_balance == 1) {
            _rotateRightLeft(node);
        } else {
            std::string msg("ERROR: r_balance has unexpected value: ");
            msg += std::to_string(r_balance);
            throw std::runtime_error(msg);
        }
    }
    _updateHeight(node);
    const int final_balance = _getBalanceFactor(node);
    if (final_balance < -1 || final_balance > 1) {
        std::string msg("ERROR: Invalid balance factor after _ensureBalance: ");
        msg += std::to_string(final_balance);
        msg += " ; Something went wrong.";
        throw std::runtime_error(msg);
    }
}

int SuffixArray::_getHeight(SuffixArray::Node *& node) {
    return node == nullptr ? 0 : node->height_;
}

int SuffixArray::_getBalanceFactor(SuffixArray::Node *& node) {
    if (node == nullptr) return 0;
    return _getHeight(node->right) - _getHeight(node->left);
}

void SuffixArray::_updateHeight(SuffixArray::Node *& node) {
    node->height_ = std::max(_getHeight(node->left), _getHeight(node->right));
}

void SuffixArray::_rotateLeft(SuffixArray::Node *& node){
    if(node == nullptr) {
        throw std::runtime_error("ERROR: _rotateRight called on nullptr");
    }
    if(node->right == nullptr) {
        throw std::runtime_error("ERROR: _rotateRight: right child is nullptr");
    }
    Node* x = node;
    Node* y = node->right;
    Node* z = node->right->left;

    x->right = z;
    y->left = x;
    node = y;

    _updateHeight(x);
    _updateHeight(y);
}

void SuffixArray::_rotateRight(SuffixArray::Node *& node){
    if(node == nullptr) {
        throw std::runtime_error("ERROR: _rotateRight called on nullptr");
    }
    if(node->left == nullptr) {
        throw std::runtime_error("ERROR: _rotateRight: left child is nullptr");
    }
    Node* x = node;
    Node* y = node->left;
    Node* z = node->left->right;

    x->left = z;
    y->right = x;
    node = y;

    _updateHeight(x);
    _updateHeight(y);
}

void SuffixArray::_rotateLeftRight(SuffixArray::Node *& node){
    if(node == nullptr) {
        throw std::runtime_error("ERROR: _rotateRight called on nullptr");
    }
    _rotateLeft(node->left);
    _rotateRight(node);
}

void SuffixArray::_rotateRightLeft(SuffixArray::Node *& node){
    if(node == nullptr) {
        throw std::runtime_error("ERROR: _rotateRight called on nullptr");
    }
    _rotateRight(node->right);
    _rotateLeft(node);
}

std::vector<int> SuffixArray::query(std::string x) {
    std::vector<int> occurs = _findAll(x, head_);
    return occurs;
}

bool SuffixArray::has(std::string x)  {
    return _find(x, head_) != nullptr;
}

SuffixArray::Node* SuffixArray::_find(std::string x, SuffixArray::Node *& cur)  {
    if(cur == nullptr) return cur;
    if(x.compare(text_.substr(cur->offset, x.length())) == 0){
        return cur;
    }
    int compareRes = x.compare(text_.substr(cur->offset));
    if (compareRes > 0) {
        return _find(x, cur->right);
    } else if (compareRes < 0) {
        return _find(x, cur->left);
    } else {
        return cur;
    }
}

std::vector<int> SuffixArray::_findAll(std::string x, SuffixArray::Node *& cur)  {
    std::vector<int> occurs;
    if(cur == nullptr) return occurs;
    if(x.compare(text_.substr(cur->offset, x.length())) == 0){
        occurs.push_back(cur->offset);
        std::vector<int> r_occurs = _findAll(x, cur->right);
        std::vector<int> l_occurs = _findAll(x, cur->left);
        occurs.insert(occurs.end(), r_occurs.begin(), r_occurs.end());
        occurs.insert(occurs.end(), l_occurs.begin(), l_occurs.end());
        return occurs;
    }
    int compareRes = x.compare(text_.substr(cur->offset));
    if (compareRes > 0) {
        return _findAll(x, cur->right);
    } else {
        return _findAll(x, cur->left);
    }
}

void SuffixArray::printSuffixArray() {
    _printSubTree(head_);
}

void SuffixArray::_printSubTree(SuffixArray::Node *& cur) {
    if(cur->right != nullptr) _printSubTree(cur->right);
    std::cout << text_.substr(cur->offset) << " offset = " << cur->offset << std::endl;
    if(cur->left != nullptr) _printSubTree(cur->left);
}

SuffixArray::~SuffixArray() {
    if (head_ != nullptr) _cleanNode(head_);
}

void SuffixArray::_cleanNode(SuffixArray::Node *& node) {
    if (node == nullptr) return;
    Node *& rightChild = node->right;
    Node *& leftChild = node->left;
    if(rightChild != nullptr) {
        if(rightChild->right != nullptr) _cleanNode(rightChild->right);
        if(rightChild->left != nullptr) _cleanNode(rightChild->left);
        delete node->right;
        node->right = nullptr;
    }
    if(leftChild != nullptr) {
        if(leftChild->right != nullptr) _cleanNode(leftChild->right);
        if(leftChild->left != nullptr) _cleanNode(leftChild->left);
        delete node->left;
        node->left = nullptr;
    }
}