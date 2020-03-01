#include "SuffixArray.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
    //std::string text = "TCCTGCAGCCTTGCTCCCTAACCTGCCCCACAGCCTTGCCTGGATTTCTATCTCCCTGGCTTGGTGCCAGTTCCTCCAAGTCGATGGCACCTCCCTCCCTCTCAACCACTTGAGCAAACTCCAAGACATCTTCTACCCCAACACCAGCAATTGTGCCAAGGGCCATTAGGCTCTCAGCATGACTATTTTTAGAGACCCCGTGTCTGTCACTGAAACCTTTTTTGTGGGAGACTATTCCTCCCATCTGCAACAGCTGCCCCTGCTGACTGCCCTTCTCTCCTCCCTCTCATCCCAGAG";
    std::string text = "TCCTGCAGCCTTGCTCCCT";
    SuffixArray sa (text);

    //sa.printSuffixArray();

    if(sa.has("CTTGC")) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    vector<int> res1 = sa.query("CCT");
    cout << "[ ";
    for(auto & it : res1) {
        cout << it << ", ";
    }
    cout << "]" << endl;
    cout << "size of res1 = " << res1.size() << endl;

    if(sa.has("CTTGCB")) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    // std::vector<int> occs = st.query("CCT");
    // for(auto i : occs) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;

    return 0;
}