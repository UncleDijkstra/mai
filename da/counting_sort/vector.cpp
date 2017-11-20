#include "vector.h"

const int INCREASE = 2;

TVector::TVector() {
    size = 0;
    freespace = INCREASE;
    max_key = 0;
    array = new TElem[INCREASE];
}

void TVector::ResizeVector() {
    TElem* tmp = new TElem[INCREASE * size];
    for(size_t i = 0; i < size; ++i) {
        tmp[i] = array[i];
    }
    freespace = size;
    delete [] array;
    array = tmp;
}

void TVector::CountingSort() {
    int* tmp = new int[max_key + 1];
    TElem* result = new TElem[size];

    for(size_t i = 0; i < max_key + 1; ++i) {
        tmp[i] = 0;
    }
    for(size_t i = 0; i < size; ++i) {
        ++tmp[array[i].key];
    }
    for(size_t i = 1; i < max_key + 1; ++i) {
        tmp[i] += tmp[i - 1];
    }
    for(int i = size - 1; i >= 0; --i) {
        result[--tmp[array[i].key]] = array[i];
    }
    delete [] array;
    delete [] tmp;
    array = result;
}


void TVector::AddItem(TElem& value) {
    if(!freespace) {
        ResizeVector();
    }
    if(max_key < value.key) {
        max_key = value.key;
    }
    array[size] = value;
    ++size;
    --freespace;
}

std::ostream& operator<<(std::ostream& stream, const TVector& vec) {
    for(size_t i = 0; i < vec.size; ++i) {
        stream << std::setfill ('0') << std::setw (FILL) << vec.array[i].key << \
			"\t" << vec.array[i].val << "\n";
    }
    return stream;
}
