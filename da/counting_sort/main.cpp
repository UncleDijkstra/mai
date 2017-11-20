#include "vector.h"

int main(int argc, char const *argv[]) {
    TVector vec;
    int key = 0;
    ulli value = 0;
    while(std::cin >> key >> value) {
        TElem tmp(key, value);
        vec.AddItem(tmp);
    }
    vec.CountingSort();
    std::cout << vec;
    return 0;
}