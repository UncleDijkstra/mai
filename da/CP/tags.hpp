#ifndef CLASSES_H
#define CLASSES_H


#include <cctype>
#include <cmath>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>

struct TTag {
    size_t countOfArt;
    size_t countOfWords;
    std::unordered_map<std::string, size_t> uniqWords;
};

#endif