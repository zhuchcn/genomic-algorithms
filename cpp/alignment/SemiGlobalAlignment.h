#pragma once
#include "Alignment.h"
#include <string>
#include <exception>

class SemiGlobalAlignment : public Alignment {
public:
    explicit SemiGlobalAlignment(): Alignment() {};
    explicit SemiGlobalAlignment(std::string seq1, std::string seq2);
    ~SemiGlobalAlignment() {};

    void align();
    void trace_back();    
};