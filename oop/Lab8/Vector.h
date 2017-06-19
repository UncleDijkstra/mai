#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <future>
#include <mutex>
#include <thread>


#include "Figure.h"
#include "Triangle.h"
#include "Foursquare.h"
#include "Rectangle.h"
#include "Iterator.h"
#include "TAllocationBlock.h"

template <class T> class TMyVector {
public:
    TMyVector(int vCap); // конструктор класса
    void Push(std::shared_ptr<T> &temp); // добавление элемента в класс
    void Get(int index); // получение элемента класса
    void Delete(); // удаление последнего элемента класса
    // void Delete(int index); // удаление по индексу 
    template <class A> friend std::ostream& operator<<(std::ostream& os,const TMyVector<A>& vector); // вывод в стандартный поток
    ~TMyVector(); // деструктор класса
    TIterator<T> begin(); // Установка итератора на начало
    TIterator<T> end(); // Установка итератора на конец
    int GetSize(); // получение размера класса
    void * operator new (size_t size); // переопределенный оператор выделения памяти из кучи
    void operator delete(void *p); // возвращение памяти в кучу
    int MySort(int l, int r);
    void Quicksort_parallel(int l, int r);

private:
    void ResizeVector(std::shared_ptr<T> *&array); // изменение размера вектора
    int size; // текущее количетсво элементов
    int capacity; // выделенное место 
    std::shared_ptr<T> *array; // массив

    static TAllocationBlock vector_allocator;
};

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

template <class T> void TMyVector<T>::Quicksort_parallel(int l, int r) { 
    int i = l, j = r; 
    int x = l + (r - l) / 2;
    while (i <= j) { 
        while (array[i]->Square() < array[x]->Square()) {
            i++; 
        }
        while (array[j]->Square() > array[x]->Square()) {
            j--; 
        }
        if (i <= j) { 
            std::shared_ptr<Figure> tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        } 
    } 
    if (i < r) { 
        std::packaged_task<void(void)> task(bind(std::mem_fn(&TMyVector<T>::Quicksort_parallel), this, i, r)); 
        std::thread tht(move(task)); 
        tht.detach(); 
    } 
    if (l < j) { 
        std::packaged_task<void(void)> task(bind(std::mem_fn(&TMyVector<T>::Quicksort_parallel), this, l, j));
        std::thread thtw(move(task)); 
        thtw.detach(); 
    } 
}

template <class T> int TMyVector<T>::MySort(int l, int r) {
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
    return 0;
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

#endif