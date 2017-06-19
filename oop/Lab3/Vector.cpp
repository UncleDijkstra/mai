#include "Vector.h"
#include <stdlib.h>

const int INCREASE = 2;

TVector::TVector(int vCap) {
    array = new std::shared_ptr<Figure> [vCap];
    size = 0;
    capacity = vCap;
}

void TVector::ResizeVector(std::shared_ptr<Figure> *&array) {
    capacity *= INCREASE;
    std::shared_ptr<Figure> *tmp = new std::shared_ptr<Figure> [capacity];
    for(int i = 0; i < size; ++i) {
        tmp[i] = array[i];
        array[i] = nullptr;
    }
    delete [] array;
    array = nullptr;
    array = tmp;
    tmp = nullptr;
}

void TVector::Push(std::shared_ptr<Figure> &temp) {
    if(size == capacity) {
        ResizeVector(array);
    }
    array[size] = temp;
    ++size;
}

void TVector::Get(int index) {
    array[index]->Print();
}

void TVector::Delete() {
    array[--size]->~Figure();
}

// void TVector::Delete(int index) {
//     int i;
//     int j;
//     Figure *temp = (Figure *)malloc(sizeof(Figure) * (size - 1));
//     for(j = 0, i = 0; i < size; ++i) {
//         if(i != index) {
//             temp[j] = array[i];
//             ++j;
//         }
//     }
//     free(array);
//     array = temp;
//     --size;
// }

TVector::~TVector() {
    for(int i = 0; i < size; ++i) {
        array[i] = nullptr;
    }
    delete [] array;
    array = nullptr;
    capacity = size = 0;
}

std::ostream& operator<<(std::ostream& os, const TVector& vector) {
    for(int i = 0; i < vector.size; ++i) {
        // vector.array[i]->Print();
        os << *vector.array[i];
    }
    return os;
}

int TVector::GetSize() {
    return size;
}