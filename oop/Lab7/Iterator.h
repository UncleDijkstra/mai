#ifndef TITERATOR_H
#define TITERATOR_H 

#include <memory>
#include <iostream>
#include "Vector.h"

// Класс итератора на шаблонах
template <class T> class TIterator {
public:
    // Конструктор итератора
    TIterator(std::shared_ptr<T> *n) {
        ptr = n;
    }
    // Разыменование *
    std::shared_ptr<T> operator * () {
        return *ptr;
    }
    // Разыменование через ->
    std::shared_ptr<T> operator -> () {
        return ptr->GetValue();
    }
    // Продвижение по контейнеру
    void operator ++ () {
            ++ptr;
    }
    // Продвижение на n позиций
    TIterator operator ++ (int) {
        TIterator iter(*this);
        ++(*this);
        return iter;
    }
    // Сравнение итераторов
    bool operator == (TIterator const& i) {
        return ptr == i.ptr;
    }
    // Сравнение итераторов
    bool operator != (TIterator const& i) {
        return !(*this == i);
    }
private:
    // Указатель на ячейку контейнера
    std::shared_ptr<T> *ptr;
};

#endif
