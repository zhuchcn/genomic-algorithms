/**
 * A k-mer implementation.
 * 
 * @author Chenghao Zhu <chhzhu@ucdavis.edu>
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Kmer {
private:
    int k_;
    std::string text_;
    std::unordered_map<std::string, std::vector<int> > index_;

public:
    explicit Kmer();
    explicit Kmer(int k, std::string text);
    virtual ~Kmer();

    void index();
    std::vector<int> query(std::string pattern) const;
};