#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
// Superclass Figure
class Figure {
public:
    virtual void Print() = 0; // Change for Trg, Rec, Fout.
    virtual double Square() = 0; // Change for Trg, Rec, Fout.
    virtual int What() = 0;
    virtual ~Figure() {};
};

#endif