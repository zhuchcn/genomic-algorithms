#include "EditDistance.h"
#include <algorithm>
#include <iostream>


EditDistance::EditDistance(const std::string &x, const std::string &y, double shift, double match, double mismatch) :  
    x_(" " + x), y_(" " + y), shift_(shift), match_(match), mismatch_(mismatch)
{
    matrix_ = new std::vector<std::vector<double> >;
    computeMatrix();
}

void EditDistance::computeMatrix() {
    std::vector<double> row;

    for (int i = 0; i < int(x_.length()); ++i) {
        std::vector<double> row;
        for (int j = 0; j < int(y_.length()); ++j) {
            if(i == 0) {
                row.push_back(j == 0 ? 0 : shift_ * j);
            } else {
                if(j == 0) {
                    row.push_back(shift_ * i);
                    continue;
                }
                double sij = x_[i] == y_[j] ? match_ : mismatch_;
                double new_sij = std::min((*matrix_)[i-1][j-1] + sij, (*matrix_)[i-1][j] + shift_);
                new_sij = std::min(new_sij, row[j-1] + shift_);
                row.push_back(new_sij);
            }
        }
        matrix_->push_back(row);
    }
    score_ = (*matrix_)[x_.length()-1][y_.length()-1];
}

void EditDistance::printMatrix() {
    using namespace std;
    for (int i = 0; i < matrix_->size(); ++i) {
        for (int j = 0; j < (*matrix_)[i].size(); ++j) {
            if(j == 0) cout << (i == 0 ? "[[" : " [");
            cout << (*matrix_)[i][j];
            if(j < (*matrix_)[i].size()-1) cout << ", "; 
            else if(i < matrix_->size()-1) cout << "],\n";
            else cout << "]]\n";
        }
    }
}
