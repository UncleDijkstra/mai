#include <stdio.h> 
#include "struct.h"
#include "mystring.h"
#include "vector.h"
#include <stdlib.h>

const static int INCREASE = 2;

void CreateVector(TVector *point) {
	point->size = 0;
	point->array = (TElem *)malloc(INCREASE * sizeof(TElem));
	point->freespace = INCREASE;
}

void ResizeVector(TVector *point) {
	point->array = realloc(point->array, INCREASE * sizeof(TElem) * point->size);
	point->freespace = point->size;
}

void DeleteVector(TVector *point) {
	free(point->array);
	point->array = NULL;
}

void PrintVector(TVector *point) {
    // FILE *file = fopen("result.txt", "wt");
	if(point) {
	    int i;
	    for(i = 0; i < point->size; i++) {
			 // fprintf(file, "%s\t%s\n", point->array[i].key, point->array[i].string);
			printf("%s\t%s\n", point->array[i].key, point->array[i].string);
		}
	}
	 // fclose(file);
}

void AddItem(TVector *point, TElem *value) {
	if (!point->freespace) {
		ResizeVector(point);
	}
	MyStrcpy(point->array[point->size].key, value->key);
	MyStrcpy(point->array[point->size].string, value->string);
    point->size++;
    point->freespace--;
}