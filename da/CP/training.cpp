#include "training.hpp"

void countOfUniqInCurArt(const std::string& tmp,
                        std::unordered_map<std::string, size_t> &uniqTmp,
                        std::unordered_set<std::string>& uniqAll) {
    uniqAll.insert(tmp);
    uniqTmp[tmp] += 1;
}

void addWord(const std::string& line,
                std::unordered_map<std::string, size_t>& uniqTmp, 
                size_t& countOfWordsInArt,
                std::unordered_set<std::string>& uniqAll) {
    std::string tmp;
    for(size_t i = 0; i < line.size(); ++i) {
        if(isalpha(line[i])) {
            tmp += tolower(line[i]);
        } else {
            if(!tmp.empty()) {
                countOfUniqInCurArt(tmp, uniqTmp, uniqAll);
                ++countOfWordsInArt;
            }
            tmp.clear();
        }
    }
    if(!tmp.empty()) {
        countOfUniqInCurArt(tmp, uniqTmp, uniqAll);
        ++countOfWordsInArt;
    }
}

void parsingTags(std::vector<std::string>& vecOfTags, std::string& line) {
    std::string tmp;
    line += ",";
    for(size_t i = 0; i < line.size(); ++i) {
        if(line[i] == ',') {
            vecOfTags.push_back(tmp);
            tmp.clear();
        } else {
            tmp += line[i];
        }
    }
}

void addTag(const std::unordered_map<std::string, size_t>& uniqTmp, 
            std::unordered_map<std::string, TTag>& cloudOfTags,
            const std::string& curTag,
            const size_t countOfWordsInArt) {
    auto iter = cloudOfTags.find(curTag);
    if(iter != cloudOfTags.end()) {
        ++iter->second.countOfArt;
        iter->second.countOfWords += countOfWordsInArt;
        for(auto& i : uniqTmp) {
            iter->second.uniqWords[i.first] += i.second;
        }
    } else {
        TTag tagTmp;
        tagTmp.countOfArt = 1;
        tagTmp.countOfWords = countOfWordsInArt;
        tagTmp.uniqWords = uniqTmp;
        cloudOfTags.emplace(curTag, std::move(tagTmp));
    }
}

void collectOfStatistics(std::ifstream& fin,
                            std::unordered_map<std::string, TTag>& cloudOfTags,
                            size_t& countOfAllArt,
                            size_t& countOfAllUniqWords) {
    std::unordered_set<std::string> uniqAll;
    std::string tmp;
    std::string line;
    size_t countOfWordsInArt = 0;
    size_t nOfLines = 0;

    while(fin.peek() != EOF) {
        std::unordered_map<std::string, size_t> uniqTmp;
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
        for(size_t i = 0; i < vecOfTags.size(); ++i) {
            addTag(uniqTmp, cloudOfTags, vecOfTags[i], countOfWordsInArt);
        }
    }
    countOfAllUniqWords = uniqAll.size();
}

void writeOfStatistics(std::ofstream& fout, const std::unordered_map<std::string, TTag>& cloudOfTags, 
                            const size_t countOfAllArt, const size_t countOfAllUniqWords) {
    fout << countOfAllArt << "\n" << countOfAllUniqWords << "\n";
    for(auto& i : cloudOfTags) {
        fout << i.first << "\n" << i.second.countOfArt << " " << i.second.countOfWords << "\n";
        fout << i.second.uniqWords.size() << "\n";
        for(auto& iter : i.second.uniqWords) {
            fout << iter.first << " " << iter.second << "\n";
        }
    }
}