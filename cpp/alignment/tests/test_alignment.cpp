#define CATCH_CONFIG_MAIN

#include "../../catch/catch.hpp"
#include "../NeedlemanWunsch.h"
#include "../SmithWaterman.h"
#include <iostream>
#include <string>
#include <limits>
#include <exception>


TEST_CASE("Testing Needleman Wunsch alignment", "[NeedlemanWunsch]") {
    SECTION("Testing two equal strings") {
        NeedlemanWunsch a ("AAGCTCGGTGGCGAAGTC", "AAGCTCGGTGGCGAAGTC");
        a.printAlignment();
        auto matrix = a.matrix();
        REQUIRE(matrix.back().back() == 18);
    }
}

TEST_CASE("Testing Smith Watterman alignment", "[SmithWatterman]") {
    SECTION("Testing two equal strings") {
        SmithWaterman a (
            "CTCTAAGCTCGGTGGCGAAGTCGTCA", 
            "GTCCCCCCCCAGTAAGCTAGGGGCGACAGTG"
        );
        a.printAlignment();
        auto matrix = a.matrix();
        REQUIRE(matrix.back().back() == 10);
    }
}
