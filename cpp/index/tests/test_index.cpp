#define CATCH_CONFIG_MAIN

#include "../../catch/catch.hpp"
#include "../Kmer.h"
#include "../SuffixTree.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

TEST_CASE("Testing Kmer", "[KmerIndex]") {
    SECTION("Test small text") {
        string text = "TCCTGCAGCCTTGCTCCCTAACCTGCCCCACAGCCTTGCCTGGATTTCTATCTCCCTGG";
        Kmer k (5, text);
        auto occs = k.query("TAACCTGCCC");
        int expect = 18;
        REQUIRE(find(occs.begin(), occs.end(), expect) != occs.end());
    }
}

TEST_CASE("Testing Suffix Tree", "[SuffixTree]") {
    SECTION("Test small text") {
        string text = "TCCTGCAGCCTTGCTCCCTAACCTGCCCCACAGCCTTGCCTGGATTTCTATCTCCCTGG";
        SuffixTree st (text);
        REQUIRE(st.hasSubstring("TAACCTGCCC"));
        auto occs = st.query("TAACCTGCCC");
        int expect = 18;
        REQUIRE(find(occs.begin(), occs.end(), expect) != occs.end());
    }
}