#include <cctype>
#include <deque>
#include <iostream>

#include "bm.h"

const int UNDEFINE = -1;

struct TAnswer {
    TAnswer() : position(0), line(0), m(UNDEFINE) {};
    TAnswer(size_t newPos, size_t newLine) : 
                position(newPos), line(newLine), m(UNDEFINE) {};
    size_t position;
    size_t line;
    int m;
};

void PatternParser(std::vector<std::string>& pattern);
bool TextParser(std::deque<std::pair<std::string, TAnswer> >& text,
                     int patternSize, size_t shift);
void PrintAnswer(size_t position, size_t line);
size_t BMShift(int* nArray, int* littelLArray, int* bigLArray, 
                     int patternSize, int bad, int i, TAnswer& answer);

int main(int argc, char const* argv[]) {
    std::vector<std::string> pattern;
    std::deque<std::pair<std::string, TAnswer> > text;
    std::unordered_map<std::string, size_t> badChar;

    PatternParser(pattern);

    bool flag = true;
    int patternSize = pattern.size();
    int* nArray = new int[patternSize];
    int* littelLArray = new int[patternSize];
    int* bigLArray = new int[patternSize];


    BadCharacter(pattern, badChar);
    NFunc(pattern, nArray, patternSize);
    GoodSuf(pattern, bigLArray, nArray, littelLArray, patternSize);
    flag = TextParser(text, patternSize, 0);
    while(flag) {
        for(int i = patternSize - 1; i >= 0 && flag; --i) {
            if(text[i].second.m == -1 || (text[i].second.m == 0 
                && nArray[i] == 0)) {
                if(text[i].first == pattern[i] && i == 0) {
                    PrintAnswer(text[0].second.position, text[0].second.line);
                    text.back().second.m = patternSize;
                    auto tmp = badChar.find(text[i].first);
                    int bad = tmp == badChar.end() ? patternSize : 
                        i - tmp->second;
                    flag = TextParser(text, patternSize, 
                        BMShift(nArray, littelLArray, bigLArray, patternSize, 
                        std::max(1, bad), i, text[0].second));
                    break;
                } else if(text[i].first == pattern[i] && i > 0) {
                    // pass
                } else if(text[i].first != pattern[i]) {
                    text.back().second.m = patternSize - 1 - i;
                    auto tmp = badChar.find(text[i].first);
                    int bad = tmp == badChar.end() ? patternSize : 
                        i - tmp->second;
                    flag = TextParser(text, patternSize, 
                        BMShift(nArray, littelLArray, bigLArray, patternSize, 
                        std::max(1, bad), i, text[0].second));
                    break;
                }
            } else if(text[i].second.m < nArray[i]) {
                i = i - text[i].second.m + 1;
            } else if(text[i].second.m >= nArray[i] 
                    && nArray[i] == i + 1) {
                PrintAnswer(text[0].second.position, text[0].second.line);
                text.back().second.m = patternSize - 1 - i;
                auto tmp = badChar.find(text[i].first);
                int bad = tmp == badChar.end() ? patternSize : 
                    i - tmp->second;
                flag = TextParser(text, patternSize, std::max(
                    std::max(patternSize - 1 - littelLArray[1], 1), bad));
                break;
            } else if(text[i].second.m > nArray[i] && nArray[i] < i) {
                text.back().second.m = patternSize - 1 - i;
                auto tmp = badChar.find(text[i].first);
                int bad = tmp == badChar.end() ? patternSize : 
                    i - tmp->second;
                flag = TextParser(text, patternSize, 
                    BMShift(nArray, littelLArray, bigLArray, patternSize, 
                    std::max(1, bad), i - nArray[i], text[0].second));
                break;
            } else if(text[i].second.m == nArray[i] 
                    && (0 < nArray[i] && nArray[i] < i)) {
                i = i - text[i].second.m + 1;
            }
        }
    }
    delete [] nArray;
    delete [] littelLArray;
    delete [] bigLArray;
    return 0;
}

void
PatternParser(std::vector<std::string>& pattern) {
    std::string line;
    std::string tmp;
    getline(std::cin, line);
    line += " ";
    for(int i = 0; i < line.size(); ++i) {
        if(line[i] != ' ') {
            tmp += tolower(line[i]);
        } else {
            if(!tmp.empty()) {
                pattern.push_back(tmp);
                tmp.clear();
            }
        }
    }
}

bool
TextParser(std::deque<std::pair<std::string, TAnswer> >& text,
                int patternSize,
                size_t shift) {
    char ch;
    size_t capacity = text.empty() ? 0 : patternSize - shift;
    static size_t line = 1;
    static size_t word = 1;
    for(size_t i = shift; i > 0; --i) {
        text.pop_front();
    }
    while(capacity < patternSize) {
        std::string tmp;
        while(!isalpha(ch = std::cin.get())) {
            if(ch == '\n') {
                ++line;
                word = 1;
            } else if(ch == EOF) {
                return false;
            }
        }
        tmp += tolower(ch);
        while(isalpha(ch = std::cin.get())) {
            tmp += tolower(ch);
        }
        text.push_back(std::make_pair(tmp, TAnswer(word, line)));
        if(ch == '\n') {
            ++line;
            word = 1;
        } else {
            ++word;
        }
        ++capacity;
    }
    return true;
}

void
PrintAnswer(size_t position, size_t line) {
    std::cout << line << ", " << position << "\n";
}

size_t BMShift(int* nArray, int* littelLArray, int* bigLArray, 
    int patternSize, int bad, int i, TAnswer& answer) {
    if(i == 0) {
        return std::max(patternSize - 1 - littelLArray[1], bad);
    }
    int good;
    if(i == patternSize - 1) {
        good = 1;
    } else {
        good = bigLArray[i + 1] > 0 ? patternSize - 1 - bigLArray[i + 1] : 
        patternSize - 1 - littelLArray[i + 1];
    }
    if(good == 0) {
        good = 1;
    }
    return std::max(bad, good);
}

/* Naive
        int i = 0;
        for(i = 0; i < pattern.size(); ++i) {
            if(pattern[i] != text[i].first) {
                break;
            }
        }
        if(i == pattern.size()) {
            std::cout << text[0].second.line << ", " << text[0].second.position
            << "\n";
        }
        flag = TextParser(text, pattern.size(), 1);
*/
