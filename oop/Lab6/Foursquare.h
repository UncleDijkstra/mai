#ifndef FOURSQUARE_H
#define FOURSQUARE_H

#include <iostream>
#include <cstdlib>
#include "Figure.h"

class Foursquare : public Figure {
public:
    Foursquare();
    Foursquare(std::istream &is);
    Foursquare(size_t i);
    Foursquare(const Foursquare& orig);
    friend std::ostream& operator<<(std::ostream& os, const Foursquare& obj);
    Foursquare& operator=(const Foursquare& right);
    Foursquare *Get();
    void Print() override;
    ~Foursquare();
    friend class TVector;
private:
    size_t side_a;
};

#endif