#ifndef BM_H
#define BM_H

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

void BadCharacter(std::vector<std::string>& pattern,
                  std::unordered_map<std::string, size_t>& badChar);
void NFunc(std::vector<std::string>& pattern, int* array, int patternSize);
void GoodSuf(std::vector<std::string>& pattern, int* bigLArray, int* nArray,
                int* littelLArray, int patternSize);

#endif
