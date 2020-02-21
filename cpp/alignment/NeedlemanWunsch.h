#pragma once
#include "Alignment.h"
#include <string>

class NeedlemanWunsch: public Alignment {
public:
    explicit NeedlemanWunsch(): Alignment() {};
    explicit NeedlemanWunsch(std::string seq1, std::string seq2) : Alignment(seq1, seq2) {
        align();
        trace_back();
    };
    ~ NeedlemanWunsch() {};

    void align();
    void trace_back();

    void printAlignment() const {
        std::cout << "Needleman Wunsch alignment:" << std::endl << std::endl;
        Alignment::printAlignment();
    }
};