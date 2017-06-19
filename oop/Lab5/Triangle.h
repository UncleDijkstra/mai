#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Triangle : public Figure {
public:
    Triangle();
    Triangle(std::istream &is);
    Triangle(size_t i,size_t j,size_t k);
    Triangle(const Triangle& orig);
    friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
    Triangle& operator=(const Triangle& right);
    Triangle *Get();
    void Print() override;
    ~Triangle();
    friend class TVector;
private:
    size_t side_a;
    size_t side_b;
    size_t side_c;
};
#endif