#include "Vector.h"
#include <stdlib.h>

const int INCREASE = 2;

template <class T> TMyVector<T>::TMyVector(int vCap) {
    array = new std::shared_ptr<T> [vCap];
    size = 0;
    capacity = vCap;
}

template <class T> void TMyVector<T>::ResizeVector(std::shared_ptr<T> *&array) {
    capacity *= INCREASE;
    std::shared_ptr<T> *tmp = new std::shared_ptr<T> [capacity];
    for(int i = 0; i < size; ++i) {
        tmp[i] = array[i];
        array[i] = nullptr;
    }
    delete [] array;
    array = nullptr;
    array = tmp;
    tmp = nullptr;
}

template <class T> void TMyVector<T>::Push(std::shared_ptr<T> &temp) {
    if(size == capacity) {
        ResizeVector(array);
    }
    array[size] = temp;
    ++size;
}

template <class T> void TMyVector<T>::Get(int index) {
    array[index]->Print();
}

template <class T> void TMyVector<T>::Delete() {
    array[--size]->~T();
}

// void TMyVector::Delete(int index) {
//     int i;
//     int j;
//     T *temp = (T *)malloc(sizeof(T) * (size - 1));
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

template <class T> TMyVector<T>::~TMyVector() {
    for(int i = 0; i < size; ++i) {
        array[i] = nullptr;
    }
    delete [] array;
    array = nullptr;
    capacity = size = 0;
}

template <class T> std::ostream& operator<<(std::ostream& os, const TMyVector<T>& vector) {
    for(int i = 0; i < vector.size; ++i) {
        vector.array[i]->Print();
    }
    return os;
}

template <class T> int TMyVector<T>::GetSize() {
    return size;
}

#include "Figure.h"
template class TMyVector<Figure>;
template std::ostream& operator<<(std::ostream& os, const TMyVector<Figure> &vector);