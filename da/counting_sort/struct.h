#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>

using ulli = unsigned long long int;

struct TElem {
    int key;
    ulli val;
    TElem() : key(0), val(0) {};
    TElem(int newKey, ulli newVal) : key(newKey), val(newVal) {};
};

#endif