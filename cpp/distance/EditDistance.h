#pragma once
#include <string>
#include <vector>

class EditDistance {
    private:
    std::string x_;
    std::string y_;
    double shift_;
    double match_;
    double mismatch_;

    std::vector<std::vector<double> > * matrix_;
    double score_;

    public:
    explicit EditDistance();
    explicit EditDistance(const std::string &x, const std::string &y, double shift, double match, double mismatch);
    virtual ~EditDistance(){ delete matrix_; };

    std::string getX() const { return x_; };
    std::string getY() const { return y_; };
    double getShift() const { return shift_; };
    double getMatch() const { return match_; };
    double getMismatch() const { return mismatch_; };
    const std::vector<std::vector<double> >* const getMatrix() const { return matrix_; };
    int getScore() const { return score_; };

    void setX(std::string x) { x_ = x; };
    void setY(std::string y) { y_ = y; };
    void setShift(double shift) { shift_ = shift; };
    void setMatch(double match) { match_ = match; };
    void setMismatch(double mismatch) { mismatch_ = mismatch; };

    void computeMatrix();

    void printMatrix();
};

