#pragma once
#include "EditDistance.h"
#include <string>
#include <limits>

class HammingDistance : public EditDistance {
    private:
    static constexpr double INF = std::numeric_limits<double>::infinity();
    
    public:
    explicit HammingDistance(const std::string& x, const std::string& y) :
        EditDistance(x, y, INF, 0, 1) {};
    ~HammingDistance() {};
};