#include "Kmer.h"
#include "SuffixTree.h"
#include <iostream>
#include <string>

int main() {
    //std::string text = "TCCTGCAGCCTTGCTCCCTAACCTGCCCCACAGCCTTGCCTGGATTTCTATCTCCCTGGCTTGGTGCCAGTTCCTCCAAGTCGATGGCACCTCCCTCCCTCTCAACCACTTGAGCAAACTCCAAGACATCTTCTACCCCAACACCAGCAATTGTGCCAAGGGCCATTAGGCTCTCAGCATGACTATTTTTAGAGACCCCGTGTCTGTCACTGAAACCTTTTTTGTGGGAGACTATTCCTCCCATCTGCAACAGCTGCCCCTGCTGACTGCCCTTCTCTCCTCCCTCTCATCCCAGAG";
    std::string text = "TCCTGCAGCCTTGCTCCCT";
    SuffixTree st (text);

    st.printTree();

    std::vector<int> occs = st.query("CCT");
    for(auto i : occs) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}