#pragma once
#include "EditDistance.h"
#include <string>
#include <limits>
#include <exception>

class HammingDistance : public EditDistance {
    private:
    static constexpr double INF = std::numeric_limits<double>::infinity();
    
    public:
    explicit HammingDistance(const std::string& x, const std::string& y) :
        EditDistance(x, y, INF, 0, 1) {
            if(x.length() != y.length()) {
                std::string msg = "Undefined for sequences of unequal length.";
                throw std::invalid_argument(msg);
            }
        };
    ~HammingDistance() {};
};