#ifndef VECTOR_H
#define VECTOR_H

#include "Figure.h"
#include "Triangle.h"
#include "Foursquare.h"
#include "Rectangle.h"
#include <memory>

class TVector {
public:
    TVector(int vCap); // конструктор класса
    void Push(std::shared_ptr<Figure> &temp); // добавление элемента в класс
    void Get(int index); // получение элемента класса
    void Delete();// удаление последнего элемента класса
    // void Delete(int index); // удаление по индексу 
    friend std::ostream& operator<<(std::ostream& os,const TVector& vector);// вывод в стандартный поток
    ~TVector(); // деструктор класса
    int GetSize(); // получение размера класса
private:
    void ResizeVector(std::shared_ptr<Figure> *&array); // изменение размера вектора
    int size; // текущее количетсво элементов
    int capacity; // выделенное место 
    std::shared_ptr<Figure> *array; // массив
};

#endif