#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <cctype>
#include <algorithm>
#include <map>
#include <iterator>
// #include <time.h>

#include "bm.h"

const int OUTWORD = 0;
const int INWORD = 1;

struct TAnswer{
    int nString;
    int nPosition;
};

void PatterParsing(std::vector<std::pair<std::string, int> > &patter, int &max, std::map <std::string, int> &dict);
bool TextParsing(std::deque<std::pair<std::string, TAnswer> > &text, int pSize, int shift);

int main() {
    int max = 0;
    std::vector<std::pair<std::string, int> > patter;
    std::map <std::string, int> dict;
    PatterParsing(patter, max, dict);
    int pSize = patter.size();
    std::map<std::string, int>::iterator It;
    // double start_time =  clock();
    std::deque<std::pair<std::string, TAnswer> > text;
    TextParsing(text, pSize, 0);

    int *bcArray = new int[max];
    int *nFuncArray = new int[pSize];
    int *lArray = new int[pSize];
    int *llArray = new int[pSize];

    PreBmBc(patter, bcArray, max, pSize);
    Nfunc(patter, nFuncArray, pSize);
    Lfunc(patter, lArray, nFuncArray, llArray, pSize);

    if(pSize > 1) {
        bool flag = true;
        while(flag) {
            int i;
            int shift;
            for(i = pSize - 1; i >= 0 && patter[i].first == text[i].first; --i) {
            }
            if(i == -1) {
                printf("%d, %d\n", text[0].second.nString, text[0].second.nPosition);
                shift = pSize - llArray[1];
            } else {
                int bc = -1;
                It = dict.find(text[i].first);
                if(It != dict.end()) {
                    bc = It->second;
                }

                if(bc == -1) {
                    bc = pSize;
                } else {
                    bc = bcArray[bc] - (pSize - 1 - i);
                }
                int lShift;
                if(i == pSize - 1) {
                    lShift = 1;
                } else {
                    lShift = lArray[i + 1] > 0 ? pSize - 1 - lArray[i + 1] : pSize - 1 - llArray[i + 1];
                }
                if(lShift == 0) {
                    lShift = 1;
                }
                shift = std::max(bc, lShift);
            }
            flag = TextParsing(text, pSize, shift);
        }
    } else if(pSize == 1) {
        bool flag = true;
        int i;
        int shift = 1;
        while(flag) {
            for(i = pSize - 1; i >= 0 && patter[i].first == text[i].first; --i) {
            }
            if(i == -1) {
                printf("%d, %d\n", text[0].second.nString, text[0].second.nPosition);
            }
            flag = TextParsing(text, pSize, shift);
        }
    }
    // double end_time = clock();
    // double search_time = end_time - start_time;
    // printf("Time: %f sec\n", (double)search_time/CLOCKS_PER_SEC);
    delete [] nFuncArray;
    delete [] llArray;
    delete [] lArray;
    delete [] bcArray;
    return 0;
}

bool TextParsing(std::deque<std::pair<std::string, TAnswer> > &text, int pSize, int shift) {
    char ch;
    int i;
    if(!text.empty()) { 
        i = pSize - shift;
    } else {
        i = 0;
    }
    static int nOfString = 1;
    static int nOfWord = 1;
    for(int m = shift; m > 0; --m) {
        text.pop_front();
    }
    text.resize(pSize);
    while(i < pSize) {
        while(!isalpha(ch = getchar())) {
            if(ch == EOF) {
                return false;
            }
            if(ch == '\n') {
                ++nOfString;
                nOfWord = 1;
            } 
        }
        text[i].first += tolower(ch);
        while(isalpha(ch = getchar())) {
            text[i].first += tolower(ch);
        }

        text[i].second.nString = nOfString;
        text[i].second.nPosition = nOfWord;
        
        if(ch == '\n') {
            ++nOfString;
            nOfWord = 1;
        } else {
            ++nOfWord;
        }
        ++i;
    }
    return true;
}

void PatterParsing(std::vector<std::pair<std::string, int> > &patter, int &max, std::map <std::string, int> &dict) {
    char ch;
    int i = 0;
    int condition = OUTWORD;
    int j = 0;
    std::map<std::string, int>::iterator It;
    while((ch = getchar()) != '\n') {
        switch(condition) {
            case 0:
                if(ch == EOF) {
                    return;
                }
                if(isalpha(ch)) {
                    patter.resize(i + 1);
                    condition = INWORD;
                    patter[i].first += tolower(ch);
                }
                break;
            case 1:
                if(isalpha(ch)) {
                    patter[i].first += tolower(ch);
                } else {
                    condition = OUTWORD;
                    It = dict.find(patter[i].first);
                    if(It != dict.end()) {
                        patter[i].second = It->second;
                    } else {
                        patter[i].second = j;
                        dict.insert(std::pair<std::string,int>(patter[i].first, patter[i].second));
                        ++j;
                    }
                    ++i;
                }
                break;
        }
    }
    if(!patter.empty()) {
        It = dict.find(patter[i].first);
        if(It != dict.end()) {
            patter[i].second = It->second;
        } else {
            patter[i].second = j;
            dict.insert(std::pair<std::string,int>(patter[i].first, patter[i].second));
            ++j;
        }
        max = j;
    }
}
