#include "Foursquare.h"
#include <iostream>

Foursquare::Foursquare() : Foursquare(0)  { }

Foursquare::Foursquare(size_t i) : side_a(i) {
    std::cout << "Foursquare created: " << side_a << std::endl;
}

Foursquare::Foursquare(std::istream &is) {
    is >> side_a;
}

Foursquare::Foursquare(const Foursquare& orig) {
    std::cout << "Foursquare copy created" << std::endl;
    side_a = orig.side_a;
}

std::ostream& operator<<(std::ostream& os, const Foursquare& obj) {
    os << "a=" << obj.side_a << ", b=" << obj.side_a << ", c=" << obj.side_a << ", d=" << obj.side_a << std::endl;
    return os;
}

Foursquare *Foursquare::Get() {
    return this;
}

void Foursquare::Print() {
    std::cout << "a=" << side_a << ", b=" << side_a << ", c=" << side_a << ", d=" << side_a << std::endl;
}
    
Foursquare& Foursquare::operator=(const Foursquare& right) {
    if(this == &right) {
        return *this;
    }
    side_a = right.side_a;
    return *this;
}

Foursquare::~Foursquare() {
    std::cout << "Foursquare deleted" << std::endl;
}