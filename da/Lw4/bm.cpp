#include <iostream> 
#include <vector>
#include "bm.h"

void PreBmBc(std::vector<std::pair<std::string, int> > &pattern, int *array, int max, int pSize) {
    int i;
    for (i = 0; i < max; ++i) {
        array[i] = pSize;
    }
    for (i = 0; i < pSize - 1; ++i) {
        array[pattern[i].second] = pSize - 1 - i;
    }
}

void Nfunc(std::vector<std::pair<std::string, int> > &pattern, int *array, int pSize) {
    for(int i = 0; i < pSize; ++i) {
        array[i] = 0;
    }
    for (int i  = pSize - 2, l = pSize - 1, r = pSize - 1; i >= 0; --i) {
        if (i >= l) {
            array[i] = std::min(i - l + 1, array[pSize - 1 - r + i]);
        }

        while (i - array[i] >= 0 && pattern[pSize - 1 - array[i]].first == pattern[i - array[i]].first) {
            ++array[i];
        }

        if (i - array[i] + 1 < l) {
            l = i - array[i] + 1;
            r = i;
        }
    }
}

void Lfunc(std::vector<std::pair<std::string, int> > &pattern, int *array, int *nArray, int *llArray, int pSize) {
    int k = 0;
    for(int i = 0; i < pSize; ++i) {
        array[i] = 0;
    }
    int max = 0;
    int i = 0;
    for(i = 0; i < pSize - 1; ++i) {
        if(nArray[i] != 0) {
            k = pSize - nArray[i];
            array[k] = i;
        }
        if (nArray[i] > max && nArray[i] == i + 1) {
            max = nArray[i];
        }
        llArray[pSize - 1 - i] = max;
    }
    if (nArray[i] > max && nArray[i] == i + 1) {
        max = nArray[i];
    }
    llArray[pSize - 1 - i] = max;
}
