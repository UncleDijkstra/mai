#include <iostream>
#include <vector>

void CreateSequence(std::vector<int> &sequence, int sizeOfArray, int *array);
int Swap(std::vector<int> &sequence, int i, int j, int shift, int sizeOfArray);

const int SET[3] = {1, 2 ,3};

int main() {
    int sizeOfArray;
    int swaps = 0;
    int j = 0;
    int shift = 0;
    int countOfElements[2] = {0};
    std::vector<int> sequence;

    std::cin >> sizeOfArray;
    CreateSequence(sequence, sizeOfArray, countOfElements);

    for(int i = 0; i < sizeOfArray && j < 2; ++i) {
        shift += countOfElements[j];
        for(; i < shift; ++i) {
            if(sequence[i] != SET[j]) {
                swaps += Swap(sequence, i, j, shift, sizeOfArray);
            }
        }
        --i;
        ++j;
    }

    std::cout << swaps << std::endl;
    return 0;
}

void CreateSequence(std::vector<int> &sequence, int sizeOfArray, int *array) {
    int tmp;
    for(int i = 0; i < sizeOfArray; ++i) {
        std::cin >> tmp;
        if(tmp == SET[0]) {
            ++array[0];
        } else if(tmp == SET[1]) {
            ++array[1];
        }
        sequence.push_back(tmp);
    }
}

int Swap(std::vector<int> &sequence, int i, int j, int shift, int sizeOfArray) {
    if(sequence[i] != SET[2]) {
        for(; shift < sizeOfArray; ++shift) {
            if(sequence[shift] == SET[j]) {
                int tmp = sequence[i];
                sequence[i] = sequence[shift];
                sequence[shift] = tmp;
                return 1;
            }
        }
    } else {
        --sizeOfArray;
        for(; sizeOfArray >= shift; --sizeOfArray) {
                if(sequence[sizeOfArray] == SET[j]) {
                    int tmp = sequence[i];
                    sequence[i] = sequence[sizeOfArray];
                    sequence[sizeOfArray] = tmp;
                    return 1;
            }
        }
    }
    return 0;
} 