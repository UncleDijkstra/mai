#include "Vector.h"
#include <stdlib.h>

const int INCREASE = 2;
// конструктор класса
template <class T> TMyVector<T>::TMyVector(int vCap) {
    array = new std::shared_ptr<T> [vCap];
    size = 0;
    capacity = vCap;
}

template <class T> TAllocationBlock TMyVector<T>::vector_allocator(sizeof(TMyVector<T>), 100);

template <class T> void TMyVector<T>::MySort(int l, int r) {
    int x = l + (r - l) / 2;
    int i = l;
    int j = r;

    while(i <= j) {
        while(array[i]->Square() < array[x]->Square()) {
            i++;
        }
        while(array[j]->Square() > array[x]->Square()) {
            j--;
        }
        if(i <= j) {
            std::shared_ptr<Figure> tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    }
    if (i < r) {
        MySort(i, r);
    }
    
    if (l < j) {
        MySort(l, j);
    }
}

// изменение размера вектора
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
// добавление элемента в класс
template <class T> void TMyVector<T>::Push(std::shared_ptr<T> &temp) {
    if(size == capacity) {
        ResizeVector(array);
    }
    array[size] = temp;
    ++size;
}
// получение элемента класса
template <class T> void TMyVector<T>::Get(int index) {
    array[index]->Print();
}
// удаление последнего элемента класса
template <class T> void TMyVector<T>::Delete() {
    array[--size]->~T();
}
// new для своего аллокатора
template <class T> void * TMyVector<T>::operator new (size_t size) {
    return vector_allocator.allocate();
}
// delete для своего аллокатора
template <class T> void TMyVector<T>::operator delete(void *p) {
    vector_allocator.deallocate(p);
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

// Установка итератора на начало
template <class T> TIterator<T> TMyVector<T>::begin() {
    return TIterator<T>(array);
}
// Установка итератора на конец
template <class T> TIterator<T> TMyVector<T>::end() {
    return TIterator<T>(array + size);
}
// деструктор класса
template <class T> TMyVector<T>::~TMyVector() {
    for(int i = 0; i < size; ++i) {
        array[i] = nullptr;
    }
    delete [] array;
    array = nullptr;
    capacity = size = 0;
}
// вывод в стандартный поток
template <class T> std::ostream& operator<<(std::ostream& os, const TMyVector<T>& vector) {
    for(int i = 0; i < vector.size; ++i) {
        vector.array[i]->Print();
    }
    return os;
}
// получение размера класса
template <class T> int TMyVector<T>::GetSize() {
    return size;
}

#include "Figure.h"
template class TMyVector<Figure>;
template std::ostream& operator<<(std::ostream& os, const TMyVector<Figure> &vector);