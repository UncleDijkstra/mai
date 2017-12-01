#include "bm.h"

void
BadCharacter(std::vector<std::string>& pattern,
                  std::unordered_map<std::string, size_t>& badChar) {
    size_t patternSize = pattern.size();
    for(auto& i : pattern) {
        badChar[i] = patternSize;
    }

    for(int i = 0; i < patternSize; ++i) {
        badChar[pattern[i]] = i;
    }
}

void
NFunc(std::vector<std::string>& pattern, int* array, int patternSize) {
    for(int i = 0; i < patternSize; ++i) {
        array[i] = 0;
    }
    for (int i  = patternSize - 2, l = patternSize - 1, 
        r = patternSize - 1; i >= 0; --i) {
        if (i >= l) {
            array[i] = std::min(i - l + 1, array[patternSize - 1 - r + i]);
        }

        while (i - array[i] >= 0 && 
            pattern[patternSize - 1 - array[i]] == pattern[i - array[i]]) {
            ++array[i];
        }

        if (i - array[i] + 1 < l) {
            l = i - array[i] + 1;
            r = i;
        }
    }
}

void
GoodSuf(std::vector<std::string>& pattern, int* bigLArray, int* nArray,
                int* littelLArray, int patternSize) {
    int k = 0;
    for(int i = 0; i < patternSize; ++i) {
        bigLArray[i] = 0;
    }
    int max = 0;
    int i = 0;
    for(i = 0; i < patternSize - 1; ++i) {
        if(nArray[i] != 0) {
            k = patternSize - nArray[i];
            bigLArray[k] = i;
        }
        if (nArray[i] > max && nArray[i] == i + 1) {
            max = nArray[i];
        }
        littelLArray[patternSize - 1 - i] = max;
    }
    if (nArray[i] > max && nArray[i] == i + 1) {
        max = nArray[i];
    }
    littelLArray[patternSize - 1 - i] = max;
}
