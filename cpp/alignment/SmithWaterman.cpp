#include "SmithWaterman.h"
#include <array>
#include <algorithm>
#include <limits>

const double _INFINITY = std::numeric_limits<double>::infinity();

void SmithWaterman::align() {
    auto & matrix = this->matrix();
    auto & subMat = getSubMat();
    std::string const* seq1 = getSeq1();
    std::string const* seq2 = getSeq2();
    double delta = getDelta();

    for(int i = 0; i < seq1->length(); ++i) {
        std::vector<double> row;
        for(int j = 0; j < seq2->length(); ++j) {
            if(i == 0) {
                row.push_back(0);
            } else if (j == 0) {
                row.push_back(0);
            } else {
                double Sa = matrix[i-1][j-1] + 
                    subMat.at(seq1->substr(i, 1)).at(seq2->substr(j,1));
                double Sb = matrix[i-1][j] - delta;
                double Sc = row[j-1] - delta;

                double Sij = std::max(Sa, Sb);
                Sij = std::max(Sij, Sc);
                if(Sij < 0) Sij = 0;
                row.push_back(Sij);
            }
        }
        matrix.push_back(row);
    }
}

void SmithWaterman::trace_back() {
    auto & matrix = this->matrix();
    std::string const* seq1 = getSeq1();
    std::string const* seq2 = getSeq2();

    auto best_score_pos = getBestScorePosition();

    std::string alseq1, alseq2, matches;
    bool stopFound = false;

    int i = seq1->length(), j = seq2->length();
    while (i > 0 || j > 0) {
        if(i > best_score_pos[0] || j > best_score_pos[1]){
            if(i - best_score_pos[0] > j - best_score_pos[1]) {
                alseq1.push_back((*seq1)[i]);
                alseq2.push_back(' ');
                --i;
            } else if (i - best_score_pos[0] < j-best_score_pos[1]) {
                alseq1.push_back(' ');
                alseq2.push_back((*seq2)[j]);
                --j;
            } else {
                alseq1.push_back((*seq1)[i]);
                alseq2.push_back((*seq2)[j]);
                --i;
                --j;
            }
            matches.push_back(' ');
        } else if(stopFound){
            if(i < 0) {
                alseq1.push_back(' ');
                alseq2.push_back((*seq2)[j]);
                --j;
            } else if (j < 0) {
                alseq1.push_back((*seq1)[i]);
                alseq2.push_back(' ');
                --i;
            } else {
                alseq1.push_back((*seq1)[i]);
                alseq2.push_back((*seq2)[j]);
                --i;
                --j;
            }
            matches.push_back(' ');
        } else {
            double diag = i > 0 && j > 0 ? matrix[i - 1][j - 1] : -_INFINITY;
            double up = i > 0 ? matrix[i - 1][j - 1] : -_INFINITY;
            double left = j > 0 ? matrix[i - 1][j - 1] : -_INFINITY;
            double best = std::max(diag, up);
            best = std::max(best, left);

            if(best == 0) {
                stopFound = true;
            }
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

std::array<int, 2> SmithWaterman::getBestScorePosition() {
    auto & matrix = this->matrix();
    std::array<int, 2> pos ({0,0});
    for(int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            if (matrix[i][j] > matrix[pos[0]][pos[1]]){
                pos[0] = i;
                pos[1] = j;
            }
        }
    }
    return pos;
}