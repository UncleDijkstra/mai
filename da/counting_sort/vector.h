#ifndef VECTOR_H
#define VECTOR_H

#include "struct.h"
#include <iomanip>

static const size_t FILL = 6;

struct TVector {
    size_t size;
    size_t freespace;
    ulli max_key;
    TElem* array;

    TVector();
    void ResizeVector();
    void AddItem(TElem& value);
    void CountingSort();
    friend std::ostream& operator<< (std::ostream& stream, const TVector& elem);
}; 


#endif