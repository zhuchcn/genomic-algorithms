#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "NeedlemanWunsch.h"

void NeedlemanWunsch::align() {
    auto & matrix = this->matrix();
    auto & subMat = getSubMat();
    std::string const* seq1 = getSeq1();
    std::string const* seq2 = getSeq2();
    double delta = getDelta();

    for(int i = 0; i < seq1->length(); ++i) {
        std::vector<double> row;
        for(int j = 0; j < seq2->length(); ++j) {
            if(i == 0) {
                double Sij = - delta * j;
                row.push_back(Sij);
            } else if (j == 0) {
                double Sij = - delta * i;
                row.push_back(Sij);
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

void NeedlemanWunsch::trace_back() {
    auto & matrix = this->matrix();
    std::string const* seq1 = getSeq1();
    std::string const* seq2 = getSeq2();

    int i = matrix.size() - 1;
    int j = matrix[0].size() - 1;

    std::string alseq1, alseq2, matches;

    while(i > 0 && j > 0) {
        double diag = matrix[i - 1][j - 1];
        double up = matrix[i - 1][j - 1];
        double left = matrix[i - 1][j - 1];
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
    std::reverse(alseq1.begin(), alseq1.end());
    std::reverse(alseq2.begin(), alseq2.end());
    std::reverse(matches.begin(), matches.end());
    setAlignedSeqs(alseq1, alseq2, matches);
}