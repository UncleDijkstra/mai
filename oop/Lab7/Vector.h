#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

#include "Figure.h"
#include "Triangle.h"
#include "Foursquare.h"
#include "Rectangle.h"
#include "Iterator.h"
#include "TAllocationBlock.h"
#include <stdlib.h>

template <class T> class TMyVector {
public:
    TMyVector(int vCap); // конструктор класса
    void Push(std::shared_ptr<T> &temp); // добавление элемента в класс
    void SubPush(std::shared_ptr<Figure> &temp); // добавление элемента в класс
    void Get(int index1, int index2); // получение элемента класса
    void Delete(); // удаление последнего элемента класса
    void DDelete(int index); // удаление последнего элемента класса
    void TDelete(int index); // удаление по индексу 
    void SDelete(double index); // удаление по индексу 
    template <class A> friend std::ostream& operator<<(std::ostream& os,const TMyVector<A>& vector); // вывод в стандартный поток
    ~TMyVector(); // деструктор класса
    TIterator<T> begin(); // Установка итератора на начало
    TIterator<T> end(); // Установка итератора на конец
    int GetSize(); // получение размера класса
    int GetCapacity(); // получить капасити
    std::shared_ptr<T> *GetArray(); // получить массив
    void MySort(int l, int r, std::shared_ptr<Figure> *array);
    void * operator new (size_t size); // переопределенный оператор выделения памяти из кучи
    void operator delete(void *p); // возвращение памяти в кучу

private:
    void ResizeVector(std::shared_ptr<T> *&array); // изменение размера вектора
    int size; // текущее количетсво элементов
    int capacity; // выделенное место 
    std::shared_ptr<T> *array; // массив

    static TAllocationBlock vector_allocator;
};

const int INCREASE = 2;
// конструктор класса
template <class T> TMyVector<T>::TMyVector(int vCap) {
    array = new std::shared_ptr<T> [vCap];
    size = 0;
    capacity = vCap;
}

template <class T> std::shared_ptr<T> *TMyVector<T>::GetArray() {
    return array;
}

template <class T> TAllocationBlock TMyVector<T>::vector_allocator(sizeof(TMyVector<T>), 100);
// быстрая сортировка
template <class T> void TMyVector<T>::MySort(int l, int r, std::shared_ptr<Figure> *array) {
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
        MySort(i, r, array);
    }
    
    if (l < j) {
        MySort(l, j, array);
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

template <class T> void TMyVector<T>::SubPush(std::shared_ptr<Figure> &temp) {
    int i = 0;
    int end = size;
    while (i == 0 || i < end) {
            if (size == 0 || (array[i]->GetSize() == 5 && i + 1 == end)) {
                TMyVector<Figure> *slon = new TMyVector <Figure> (5);
                std::shared_ptr<TMyVector<Figure> > pp = std::shared_ptr<TMyVector<Figure> > (slon);
                Push(pp);
                ++i;
                break;
            } else if (array[i]->GetSize() != 5) {
                break;
            }
        ++i;
    }
    if(size == i) {
        --i;
    }
    printf("i = %d\n", i);
    (*(array + i))->Push(temp);
    if (array[i]->GetSize() > 1) { 
        MySort(0, array[i]->GetSize() - 1, (*(array + i))->GetArray());
    }
}
// получение элемента класса
template <class T> void TMyVector<T>::Get(int index1, int index2) {
    (*(*array[index1]) + index2)->Print();
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
// удаление по типу
template <class T> void TMyVector<T>::TDelete(int index) {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < (*(array + i))->GetSize(); ++j) {
            if ((*((*(array + i))->GetArray() + j))->What() == index ) {
                (*(array + i))->DDelete(j);
            }
        }
    }
    for(int i = 0; i < size; ++i) {
        if((*(array + i))->GetSize() == 0) {
            DDelete(i);
        }
    }
}
// удаление по площади
template <class T> void TMyVector<T>::SDelete(double index) {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < (*(array + i))->GetSize(); ++j) {
            if ((*((*(array + i))->GetArray() + j))->Square() == index ) {
                (*(array + i))->DDelete(j);
            }
        }
    }
    for(int i = 0; i < size; ++i) {
        if((*(array + i))->GetSize() == 0) {
            DDelete(i);
        }
    }
}

template <class T> void TMyVector<T>::DDelete(int index) {
    std::shared_ptr<T> tmp;
    for(int i = index; i < size - 1; ++i) {
        tmp = array[i];
        array[i] = array[i + 1];
    }
    Delete();
}

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
    for(int j = 0; j < vector.size; ++j) {
        printf("Array %d:\n", j);
        printf("Size %d:\n", vector.array[j]->size);
        for(int i = 0; i < vector.array[j]->size; ++i) {
            vector.array[j]->array[i]->Print();
        }
        printf("================\n");
    }
    return os;
}
// получение размера класса
template <class T> int TMyVector<T>::GetSize() {
    return size;
}

template <class T> int TMyVector<T>::GetCapacity() {
    return capacity;
}

// КОСТЫЛЬ для .cpp
// #include "Figure.h"
// template class TMyVector<Figure>;
// template std::ostream& operator<<(std::ostream& os, const TMyVector<Figure> &vector);

#endif