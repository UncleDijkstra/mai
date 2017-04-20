#include <stdio.h>
#include "vector.h"
#include "struct.h"
#include "mystring.h"
#include "sort.h"
#include "string.h"

int main(int argc, char const *argv[]) {
    TVector pVtr;
    CreateVector(&pVtr); // создаем вектор
    TElem tmp; // здесь храним элемент с помощью которого заносим данные в вектор
    while(scanf("%s\t%s", tmp.key, tmp.string) == 2) {
        int length = MyStrlen(tmp.string);
        if (length != MY_STRING_SIZE) { // если длина строки меньше 64, то дозаполняем \0
            int i;
            for(i = length; i < MY_STRING_SIZE; i++) {
                tmp.string[i] = '\0';
            }
        }
        AddItem(&pVtr, &tmp); // добавляем элемент в вектор
    }
    RadixSort(pVtr.array, pVtr.size);
    PrintVector(&pVtr);
    DeleteVector(&pVtr);
    return 0;
}