#ifndef CLASSES_H
#define CLASSES_H


#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <string.h>
#include <vector>

struct TTag {
    TTag(const std::string name) : tag(name){};
    std::string tag;
    size_t countOfArt;
    size_t countOfWords;
    std::map<std::string, size_t> uniqWords;
};

inline bool isDelimiter(const char tmp) {
    return tmp == '.' || tmp == ',' || tmp == '(' || tmp == ')' || tmp == ' ' 
    || tmp == '\n' || tmp == '\t' || tmp == '*' || tmp == '"' || tmp == '}'
    || tmp == '{' || tmp == '[' || tmp == ']' || tmp == ':' || tmp == ';'
    || tmp == '<' || tmp == '>' || tmp == '|' || tmp == '!' || tmp == '?'
    || tmp == '=' || tmp == '\'' || tmp == '/' || tmp == '`' || tmp == '_';
}

inline bool isGoodDelimiter(const char tmp) {
    return tmp == ';' || tmp == '{' || tmp == '}' 
    || tmp == '<' || tmp == '>';
}

#endif