#ifndef VECTOR_H
#define VECTOR_H

#include "Triangle.h"

class TVector {
public:
    TVector(int vCap); // конструктор класса
    void Push(Triangle &temp); // добавление элемента в класс
    Triangle& Get(int index); // получение элемента класса
    void Delete();// удаление последнего элемента класса
    void Delete(int index); // удаление по индексу 
    friend std::ostream& operator<<(std::ostream& os,const TVector& vector);// вывод в стандартный поток
    ~TVector(); // деструктор класса
    int GetSize(); // получение размера класса 
private:
    Triangle *ResizeVector(Triangle *array); // изменение размера вектора
    int size; // текущее количетсво элементов
    int capacity; // выделенное место 
    Triangle *array; // массив
};

#endif