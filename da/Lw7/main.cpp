#include <iostream>
#include <string>

const size_t MAX = 100;

int main() {
    std::string pattern;
    std::cin >> pattern;
    size_t pSize = 0;
    pSize = pattern.size();
    long long int array[MAX][MAX];
    for(int i = 0, j = 0; i < pSize; ++i, ++j) {
        array[i][j] = 1;
        if(i != pSize - 1 && pattern[i] == pattern[i + 1]) {
            array[i][j + 1] = 3;
        } else if(i != pSize - 1) {
            array[i][j + 1] = 2;
        }
    }
    for(int shift = 2; shift < pSize; ++shift) {
        for (int i = 0, j = shift; i < pSize && j < pSize; ++i, ++j) {
            if(pattern[i] == pattern[j]) {
                array[i][j] = array[i][j - 1] + array[i + 1][j] + 1;
            } else if(pattern[i] != pattern[j]) {
                array[i][j] = array[i][j - 1] + array[i + 1][j] - array[i + 1][j - 1];
            }
        }
    }
    if(pSize) {
        std::cout << array[0][pSize - 1] << std::endl;
    }
    return 0;
}