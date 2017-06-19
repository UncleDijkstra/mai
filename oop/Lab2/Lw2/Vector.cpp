#include "Vector.h"
#include <stdlib.h>

const int INCREASE = 2;

TVector::TVector(int vCap) {
    array = (Triangle *)malloc(sizeof(Triangle) * vCap);
    size = 0;
    capacity = vCap;
}

Triangle *TVector::ResizeVector(Triangle *array) {
    return (Triangle *)realloc(array, sizeof(Triangle) * INCREASE * capacity);
}

void TVector::Push(Triangle &temp) { // change &temp -> *temp
    if(size == capacity) {
        array = ResizeVector(array);
    }
    array[size] = temp;
    // array[size].side_a = temp->side_a;
    // array[size].side_b = temp->side_b;
    // array[size].side_c = temp->side_c;
    ++size;
    capacity *= INCREASE;
}

Triangle& TVector::Get(int index) {
    return array[index];
}

void TVector::Delete() {
    // array[--size].SetZero(); 1 version
    array[--size].~Triangle();
}

void TVector::Delete(int index) {
    int i;
    int j;
    Triangle *temp = (Triangle *)malloc(sizeof(Triangle) * (size - 1));
    for(j = 0, i = 0; i < size; ++i) {
        if(i != index) {
            temp[j] = array[i];
            ++j;
        }
    }
    free(array);
    array = temp;
    --size;
}

TVector::~TVector() {
    free(array);
    array = NULL;
    capacity = size = 0;
}

std::ostream& operator<<(std::ostream& os, const TVector& vector) {
    for(int i = 0; i < vector.size; ++i) {
        os << vector.array[i];
    }
    return os;
}

int TVector::GetSize() {
    return size;
}