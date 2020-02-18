#pragma once
#include "EditDistance.h"
#include <vector>

class LevenshteinDistance : public EditDistance {
    public:
    explicit LevenshteinDistance(const std::string& x, const std::string& y) :
        EditDistance(x, y, 1, 0, 1) {};
    virtual ~LevenshteinDistance() {};
};