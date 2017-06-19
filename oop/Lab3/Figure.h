#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
// Superclass Figure
class Figure {
public:
    virtual void Print() = 0; // Change for Trg, Rec, Fout.
    virtual ~Figure() {};
    friend std::ostream& operator <<(std::ostream &os, Figure& obj) {
        obj.Print();
        return os;
    };
};

#endif