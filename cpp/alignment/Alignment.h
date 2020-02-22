#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>

const std::unordered_map<std::string, std::unordered_map<std::string, double> > 
__DEFAULT_SUBSTITUTE_MATRIX ({
    {"A", {{"A", 1}, {"C", -1}, {"G", -1}, {"T", -1}}},
    {"C", {{"A", -1}, {"C", 1}, {"G", -1}, {"T", -1}}},
    {"G", {{"A", -1}, {"C", -1}, {"G", 1}, {"T", -1}}},
    {"T", {{"A", -1}, {"C", -1}, {"G", -1}, {"T", 1}}}
});

class Alignment {
private:
    std::string seq1_;
    std::string seq2_;
    double delta_;
    std::vector<std::vector<double> > matrix_;
    std::unordered_map<std::string, std::unordered_map<std::string, double> > subMat_;
    std::string aligned_seq1_;
    std::string aligned_seq2_;
    std::string aligned_matches_;

public:
    static constexpr double _INFINITY = std::numeric_limits<double>::infinity();
    explicit Alignment(std::string seq1, std::string seq2):
        seq1_(" " + seq1), seq2_(" " + seq2), delta_(1), matrix_(),
        subMat_(__DEFAULT_SUBSTITUTE_MATRIX), aligned_seq1_(), 
        aligned_seq2_(), aligned_matches_()
    {};
    explicit Alignment() : 
        seq1_(), seq2_(), delta_(1), matrix_(), 
        subMat_(__DEFAULT_SUBSTITUTE_MATRIX),
        aligned_seq1_(), aligned_seq2_(), aligned_matches_()
    {};
    virtual ~Alignment() {};

    std::string const * getSeq1() const { return &seq1_; };
    std::string const * getSeq2() const { return &seq2_; };
    double getDelta() const { return delta_; };
    std::string const * getAlignedSeq1() const { return &aligned_seq1_; };
    std::string const * getAlignedSeq2() const { return &aligned_seq2_; };
    std::string const * getAlignedMatches() const { return &aligned_matches_; };
    std::unordered_map<std::string, std::unordered_map<std::string, double> > 
        & getSubMat() { return subMat_; };
    
    std::vector<std::vector<double> >& matrix() { return matrix_; };

    void setAlignedSeqs (std::string seq1, std::string seq2, std::string matches) { 
        aligned_seq1_ = seq1;
        aligned_seq2_ = seq2;
        aligned_matches_ = matches;
    }

    virtual void printAlignment () const {
        int w = log10(aligned_matches_.length());
        w++;
        for (int i = 0; i < aligned_matches_.length(); i+=60) {
            std::cout << "seq1: " << std::setfill (' ') << std::setw(w) << i << " ";
            std::cout << aligned_seq1_.substr(i, 60) << std::endl;
            std::cout << "      " << std::string(w+1, ' ') << aligned_matches_.substr(i, 60) << std::endl;
            std::cout << "seq2: " << std::string(w+1, ' ') << aligned_seq2_.substr(i, 60) << std::endl;
            std::cout << std::endl;
        }
    }
};