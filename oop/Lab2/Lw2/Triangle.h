#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cstdlib>
#include <iostream>

class Triangle {
public:
    Triangle();
    Triangle(std::istream &is);
    Triangle(size_t i,size_t j,size_t k);
    Triangle(const Triangle& orig);
    Triangle& operator++();
    double Square();
    friend Triangle operator+(const Triangle& left,const Triangle& right);
    friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
    friend std::istream& operator>>(std::istream& is, Triangle& obj);
    Triangle& operator=(const Triangle& right);
    ~Triangle();
    void SetSides(int a, int b, int c);
    void SetZero();
    friend class TVector;
private:
    size_t side_a;
    size_t side_b;
    size_t side_c;
};
#endif