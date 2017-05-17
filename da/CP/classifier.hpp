#ifndef CLASS_H
#define CLASS_H

#include "tags.hpp"
#include <algorithm>
#include <iomanip>

void classParsing(int argc, char const *argv[], std::string &inFilename,
                    std::string &statFilename, std::string &outFilename);
void readOfStatistics(std::ifstream &stat,
                            std::map<std::string, TTag> &cloudOfTags,
                            size_t &countOfAllArt,
                            size_t &countOfAllUniqWords);
void classification(std::ifstream &fin, std::ifstream &stat,
                            std::ofstream &fout,
                            std::map<std::string, TTag> &cloudOfTags,
                            size_t &countOfAllArt,
                            size_t &countOfAllUniqWords);
void createTag(std::ifstream &stat,
                    std::map<std::string, TTag> &cloudOfTags);

void addWordsInMap(std::map<std::string, size_t>& mapOfWords,
                        const std::string& line);

#endif