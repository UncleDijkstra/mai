#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include <cstdlib>
#include "Figure.h"

class Rectangle : public Figure {
public:
    Rectangle();
    Rectangle(std::istream &is);
    Rectangle(size_t i,size_t j); 
    Rectangle(const Rectangle& orig);
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& obj);
    Rectangle& operator=(const Rectangle& right);
    Rectangle *Get();
    void Print() override;
    int What() override;
    double Square() override;
    ~Rectangle();
    friend class TVector;
private:
    size_t side_a;
    size_t side_b;
};

#endif