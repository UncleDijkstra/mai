#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <map>
#include <string>

class TClass {
public:
    TClass();
    ~TClass();
private:
    size_t countOfDocs;
    size_t countOfWords;
    std::map<std::string, size_t> uniqWords; 
};

#endif