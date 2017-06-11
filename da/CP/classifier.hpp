#ifndef CLASS_H
#define CLASS_H

#include "tags.hpp"
#include <algorithm>

const double MAYBE = 1 - std::exp(-4);

void readOfStatistics(std::ifstream& stat,
                            std::unordered_map<std::string, TTag>& cloudOfTags,
                            size_t& countOfAllArt,
                            size_t& countOfAllUniqWords);
void classification(std::ifstream& fin, std::ifstream& stat,
                            std::ofstream& fout,
                            std::unordered_map<std::string, TTag>& cloudOfTags,
                            size_t& countOfAllArt,
                            size_t& countOfAllUniqWords);
void createTag(std::ifstream& stat,
                    std::unordered_map<std::string, TTag>& cloudOfTags);

void addWordsInMap(std::unordered_map<std::string, size_t>& mapOfWords,
                        const std::string& line);

#endif