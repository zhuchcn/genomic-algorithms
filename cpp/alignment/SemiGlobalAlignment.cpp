#include "SemiGlobalAlignment.h"
#include <algorithm>
#include <iterator>

// constructor
SemiGlobalAlignment::SemiGlobalAlignment(std::string seq1, std::string seq2) :
Alignment(seq1, seq2) {
    if(seq1.length() > seq2.length()) {
        throw std::invalid_argument("seq1 must not be longer than seq2.");
    }
    align();
    trace_back();
}

void SemiGlobalAlignment::align() {
    std::string const * seq1 = getSeq1();
    std::string const * seq2 = getSeq2();
    double delta = getDelta();
    auto & matrix = this->matrix();
    auto & subMat = getSubMat();

    for(int i = 0; i < seq1->length(); ++i) {
        std::vector<double> row;
        for(int j = 0; j < seq2->length(); ++j) {
            if(i == 0) {
                row.push_back(0);
            } else if(j == 0) {
                row.push_back(-delta * i);
            } else {
                double Sa = matrix[i-1][j-1] + 
                    subMat.at(seq1->substr(i, 1)).at(seq2->substr(j,1));
                double Sb = matrix[i-1][j] - delta;
                double Sc = row[j-1] - delta;

                double Sij = std::max(Sa, Sb);
                Sij = std::max(Sij, Sc);
                row.push_back(Sij);
            }
        }
        matrix.push_back(row);
    }
}

void SemiGlobalAlignment::trace_back() {
    std::string const * seq1 = getSeq1();
    std::string const * seq2 = getSeq2();
    auto & matrix = this->matrix();

    int i = seq1->length() - 1;
    std::vector<double> & lastRow = matrix.back();
    int j = std::distance(lastRow.begin(), std::max_element(lastRow.begin(), lastRow.end()));
    
    std::string alseq2 = seq2->substr(j);
    std::reverse(alseq2.begin(), alseq2.end());
    std::string alseq1(alseq2.length(), ' ');
    std::string matches(alseq2.length(), ' ');
    
    while (i > 0 || j > 0) {
        if(i <= 0) {
            alseq1.push_back(' ');
            alseq2.push_back((*seq2)[j]);
            matches.push_back(' ');
            --j;
        } else {
            double diag = i > 0 && j > 0 ? matrix[i - 1][j - 1] : -_INFINITY;
            double up = i > 0 ? matrix[i - 1][j] : -_INFINITY;
            double left = j > 0 ? matrix[i][j - 1] : -_INFINITY;
            double best = std::max(diag, up);
            best = std::max(best, left);

            if (best == diag){
                alseq1.push_back((*seq1)[i]);
                alseq2.push_back((*seq2)[j]);
                matches.push_back(seq1->substr(i, 1) == seq2->substr(j, 1) ? '|' : ' ');
                --i;
                --j;
            } else if (best == up){
                alseq1.push_back((*seq1)[i]);
                alseq2.push_back('-');
                matches.push_back(' ');
                --i;
            } else {
                alseq1.push_back('-');
                alseq2.push_back((*seq2)[j]);
                matches.push_back(' ');
                --j;
            }
        }
    }
    std::reverse(alseq1.begin(), alseq1.end());
    std::reverse(alseq2.begin(), alseq2.end());
    std::reverse(matches.begin(), matches.end());
    setAlignedSeqs(alseq1, alseq2, matches);
}