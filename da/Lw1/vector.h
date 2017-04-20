#ifndef VECTOR_H
#define VECTOR_H
#include "struct.h"

typedef struct TVector {
	unsigned int size; // количество элементов векторе
	unsigned int freespace; // свободное место в векторе
	TElem *array; // массив элементов
}TVector;

void CreateVector(TVector *point);
void ResizeVector(TVector *point);
void DeleteVector(TVector *point);
void AddItem(TVector *point, TElem *value);
void PrintVector(TVector *point);

#endif