#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "EditDistance.h"
#include "HammingDistance.h"
#include "LevenshteinDistance.h"

using namespace std;

// const double INF = std::numeric_limits<double>::infinity();

int main() {

    string x = "AAATAATGCGAG";
    string y = "AAATAATCCGAG";
    HammingDistance d (x, y);

    cout << d.getScore() << endl;
    //auto m = e.getMatrix();
    //cout << m->size() << endl;
    d.printMatrix();
    // cout << INF << endl;

    return 0;
}