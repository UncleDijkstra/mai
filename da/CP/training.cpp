#include "training.hpp"

void learnParsing(int argc, char const *argv[], 
                    std::string &inFilename,
                    std::string &outFilename) {
    for(int32_t i = 2; i < argc; ++i) {
        if(!strcmp(argv[i], "--input")) {
            inFilename = argv[++i];
        } else if (!strcmp(argv[i], "--output")) {
            outFilename = argv[++i];
        } else {
            std::cout << "Error\n";
            exit(0);
        }
    }
}

void countOfUniqInCurArt(const std::string tmp,
                        std::map<std::string, size_t> &uniqTmp,
                        std::set<std::string> &uniqAll) {
    uniqAll.insert(tmp);
    auto iter = uniqTmp.find(tmp);
    if(iter == uniqTmp.end()) {
        uniqTmp.emplace(tmp, 1);
    } else {
        ++iter->second;
    }
}

void addWord(const std::string &line,
                std::map<std::string, size_t> &uniqTmp, 
                size_t &countOfWordsInArt,
                std::set<std::string> &uniqAll) {
    std::string tmp = "";
    for(size_t i = 0; i < line.size(); ++i) {
        if(!isDelimiter(line[i])) {
            tmp += tolower(line[i]);
        } else {
            if(tmp != "") {
                countOfUniqInCurArt(tmp, uniqTmp, uniqAll);
                ++countOfWordsInArt;
            }
            if(isGoodDelimiter(line[i])) {
                tmp = line[i];
                countOfUniqInCurArt(tmp, uniqTmp, uniqAll);
                ++countOfWordsInArt;
            }
                tmp = "";
        }
    }
}

void parsingTags(std::vector<std::string> &vecOfTags, std::string &line) {
    std::string tmp = "";
    line += ",";
    for(int32_t i = 0; i < line.size(); ++i) {
        if(line[i] == ',') {
            vecOfTags.push_back(tmp);
            tmp = "";
        } else {
            tmp += tolower(line[i]);
        }
    }
}

void addTag(const std::map<std::string, size_t> &uniqTmp, 
            std::map<std::string, TTag> &cloudOfTags,
            const std::string &curTag,
            const size_t countOfWordsInArt) {
    auto iter = cloudOfTags.find(curTag);
    if(iter != cloudOfTags.end()) {
        ++(iter->second).countOfArt;
        (iter->second).countOfWords += countOfWordsInArt;
        for(auto &i : uniqTmp) {
            auto flag = (iter->second).uniqWords.find(i.first);
            if(flag != (iter->second).uniqWords.end()) {
                flag->second += i.second;
            } else {
                (iter->second).uniqWords.emplace(i.first, i.second);
            }
        }
    } else {
        TTag tagTmp = curTag;
        tagTmp.countOfArt = 1;
        tagTmp.countOfWords = countOfWordsInArt;
        for(auto &i : uniqTmp) {
            tagTmp.uniqWords.emplace(i.first, i.second);
        }
        cloudOfTags.emplace(curTag, tagTmp);
    }
}

void collectOfStatistics(std::ifstream &fin,
                            std::map<std::string, TTag> &cloudOfTags,
                            size_t &countOfAllArt,
                            size_t &countOfAllUniqWords) {
    std::set<std::string> uniqAll;
    std::string tmp;
    std::string line;
    size_t countOfWordsInArt = 0;
    size_t nOfLines;

    while(fin.peek() != EOF) {
        std::map<std::string, size_t> uniqTmp;
        countOfWordsInArt = 0;

        fin >> nOfLines;
        fin.get();
        ++countOfAllArt;
        for(; nOfLines > 0; --nOfLines) {
            getline(fin, line);
            addWord(line, uniqTmp, countOfWordsInArt, uniqAll);
        }
        getline(fin, line);
        std::vector<std::string> vecOfTags;
        parsingTags(vecOfTags, line);
        for(int32_t i = 0; i < vecOfTags.size(); ++i) {
            addTag(uniqTmp, cloudOfTags, vecOfTags[i], countOfWordsInArt);
        }
    }
    countOfAllUniqWords = uniqAll.size();
}

void writeOfStatistics(std::ofstream &fout, const std::map<std::string, TTag> &cloudOfTags, 
                            const size_t countOfAllArt, const size_t countOfAllUniqWords) {
    fout << countOfAllArt << "\n" << countOfAllUniqWords << "\n";
    for(auto &i : cloudOfTags) {
        fout << i.second.tag << "\n" << i.second.countOfArt << " " << i.second.countOfWords << "\n";
        fout << i.second.uniqWords.size() << "\n";
        for(auto &iter : i.second.uniqWords) {
            fout << iter.first << " " << iter.second << "\n";
        }
    }
}