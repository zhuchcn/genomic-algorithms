#include <array>
#include "Alignment.h"

class SmithWaterman : public Alignment {
public:
    explicit SmithWaterman(): Alignment() {};
    explicit SmithWaterman(std::string seq1, std::string seq2) : Alignment(seq1, seq2) {
        align();
        trace_back();
    };
    ~ SmithWaterman() {};

    void align();
    void trace_back();

    void printAlignment() const {
        std::cout << "Smith Waterman alignment:" << std::endl << std::endl;
        Alignment::printAlignment();
    }

private:
    std::array<int, 2> getBestScorePosition();
};