#define CATCH_CONFIG_MAIN

#include "../../catch/catch.hpp"
#include "../EditDistance.h"
#include "../HammingDistance.h"
#include "../LevenshteinDistance.h"
#include <iostream>
#include <string>
#include <limits>
#include <exception>

TEST_CASE("Testing edit distance", "[EditDistance]") {
    SECTION("Testing two equal strings") {
        const double INF = std::numeric_limits<double>::infinity();
        const std::string x = "AAATAATCCGAG";
        const std::string y = "AAATAATCCGAG";
        EditDistance d (x, y, INF, 0, 1);
        REQUIRE(d.getScore() == 0);
    }
}

TEST_CASE("Testing Hamming distance", "[HammingDistance]") {
    
    SECTION("Testing two equal strings") {
        const std::string x = "AAATAATCCGAG";
        const std::string y = "AAATAATCCGAG";
        HammingDistance d (x, y);
        REQUIRE(d.getScore() == 0);
        auto matrix = d.getMatrix();
        REQUIRE(matrix->size() == 13);
        REQUIRE((*matrix)[0].size() == 13);
    }

    SECTION("Testing two strings unequally long") {
        const std::string x = "AAATAATCCGA";
        const std::string y = "AAATAATCCGAG";
        REQUIRE_THROWS_AS([&](){HammingDistance d (x,y);}(), std::invalid_argument); 
    }
    
    SECTION("Testing different strings") {
        const std::string x = "AAATAATCGAGA";
        const std::string y = "AAATAATCCGAG";
        HammingDistance d (x, y);
        REQUIRE(d.getScore() == 4);
    }
}

TEST_CASE("Testing Levenshtein distance", "[LevenshteinDistance]") {
    
    SECTION("Testing two equal strings") {
        const std::string x = "AAATAATCCGAG";
        const std::string y = "AAATAATCCGAG";
        LevenshteinDistance d (x, y);
        REQUIRE(d.getScore() == 0);
        auto matrix = d.getMatrix();
        REQUIRE(matrix->size() == 13);
        REQUIRE((*matrix)[0].size() == 13);
    }
    
    SECTION("Testing mismatch") {
        const std::string x = "AAATAATGCGAG";
        const std::string y = "AAATAATCCGAG";
        LevenshteinDistance d (x, y);
        REQUIRE(d.getScore() == 1);
    }

    SECTION("Testing indel") {
        const std::string x = "AAATAATCGAG";
        const std::string y = "AAATAATCCGAG";
        LevenshteinDistance d (x, y);
        REQUIRE(d.getScore() == 1);
    }
}