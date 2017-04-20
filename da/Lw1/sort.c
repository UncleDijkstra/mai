#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "mystring.h"
#include <string.h>

int IsDigit(char symbol) {
	return '0' <= symbol && symbol <= '9';
}

void RadixSort(TElem *array, register int size) {
	int i;
	register int j;
	int tmp[MY_NUMERAL_SYSTEM];
    TElem *out = (TElem *)malloc(size * sizeof(TElem));
	for(i = MY_KEY_SIZE - 1; i >= 0; i--) {
		bzero(tmp, sizeof(int) * MY_NUMERAL_SYSTEM); // инициализируем массив нулями
		for(j = 0; j < size; j++) {
		 	if(IsDigit(array[j].key[i])) { 
		 		tmp[array[j].key[i] - '0']++;
		 	} else {
		 		tmp[array[j].key[i] - 'a' + CHAR_TO_INT]++;
		 	}
		}
		for(int j = 1; j < MY_NUMERAL_SYSTEM; j++) {
			tmp[j] += tmp[j - 1];
		}
		for(j = size-1; j >= 0; j--) {
			if(IsDigit(array[j].key[i])) {
		 		out[--tmp[array[j].key[i] - '0']] = array[j];
            } else {
		 		out[--tmp[array[j].key[i] - 'a' + CHAR_TO_INT]] = array[j];
		 	}
		}
		TElem *tmp = array; // Перебрсаываем указатели
		array = out;
		out = tmp;
	}
	free(out);
}