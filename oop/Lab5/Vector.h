#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

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

private:
    void ResizeVector(std::shared_ptr<T> *&array); // изменение размера вектора
    int size; // текущее количетсво элементов
    int capacity; // выделенное место 
    std::shared_ptr<T> *array; // массив

    static TAllocationBlock vector_allocator;
};

#endif