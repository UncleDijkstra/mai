#ifndef TRAINING_HPP
#define TRAINING_HPP

#include "tags.hpp"

void learnParsing(int argc, char const *argv[], std::string &inFilename,
                    std::string &outFilename);
void parsingTags(std::vector<std::string> &vecOfTags, std::string &line);
void collectOfStatistics(std::ifstream &fin,
                            std::map<std::string, TTag> &cloudOfTags,
                            size_t &countOfAllArt,
                            size_t &countOfAllUniqWords);
void countOfUniqInCurArt(const std::string tmp,
                        std::map<std::string, size_t> &uniqTmp,
                        std::set<std::string> &uniqAll);
void addTag(const std::map<std::string, size_t> &uniqTmp, 
            std::map<std::string, TTag> &cloudOfTags,
            const std::vector<std::string> &vecOfTags,
            const size_t countOfWordsInArt);
void addWord(const std::string &line,
                std::map<std::string, size_t> &uniqTmp, 
                size_t &countOfWordsInArt,
                std::set<std::string> &uniq);
void writeOfStatistics(std::ofstream &fout,
                        const std::map<std::string, TTag> &cloudOfTags,
                        const size_t countOfAllArt,
                        const size_t countOfAllUniqWords);

#endif