#include "SmithWaterman.h"
#include "NeedlemanWunsch.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    SmithWaterman a1 (
        "CTCTAAGCTCGGTGGCGAAGTCGTCA", 
        "GTCCCCCCCCAGTAAGCTAGGGGCGACAGTG"
    );

    a1.printAlignment();
    cout << a1.matrix().back().back() << endl;

    NeedlemanWunsch a2 (
        "AAGCTCGGTGGCGAAGTC", 
        "AAGCTCGGTGGCGAAGTC"
    );

    a2.printAlignment();
    cout << a2.matrix().back().back() << endl;

    return 0;
};