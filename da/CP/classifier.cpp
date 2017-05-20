#include "classifier.hpp"

void classParsing(int argc, char const *argv[], std::string &inFilename,
                                                std::string &statFilename,
                                                std::string &outFilename) {
    for(int i = 2; i < argc; ++i) {
        if(!strcmp(argv[i], "--input")) {
            inFilename = argv[++i];
        } else if (!strcmp(argv[i], "--output")) {
            outFilename = argv[++i];
        } else if(!strcmp(argv[i], "--stats")) {
            statFilename = argv[++i];
        } else {
            std::cout << "Error\n";
            exit(0);
        }
    }
}

void addWordsInMap(std::map<std::string, size_t>& mapOfWords,
                        const std::string& line) {
    std::string tmp = "";
    for(size_t i = 0; i < line.size(); ++i) {
        if(!isDelimiter(line[i])) {
            tmp += tolower(line[i]);
        } else {
            bool flag = false;
            if(tmp != "") {
                flag = true;
            }
            if(isGoodDelimiter(line[i])) {
                tmp = line[i];
                flag = true;
            }
            if(flag) {
                auto i = mapOfWords.find(tmp);
                if(i == mapOfWords.end()) {
                    mapOfWords.emplace(tmp, 1);
                } else {
                    ++i->second;
                }
            }
            tmp = "";
        }
    }
}

void classification(std::ifstream &fin, std::ifstream &stat,
                            std::ofstream &fout,
                            std::map<std::string, TTag> &cloudOfTags,
                            size_t &countOfAllArt,
                            size_t &countOfAllUniqWords) {
    size_t nOfLines;
    std::string line;

    readOfStatistics(stat, cloudOfTags, countOfAllArt, countOfAllUniqWords);
    while(fin.peek() != EOF) {
        std::map<std::string, size_t> mapOfWords;
        std::vector<std::pair<long double, std::string> > finishHim;

        fin >> nOfLines;
        fin.get();

        for(; nOfLines > 0; --nOfLines) {
            getline(fin, line);
            addWordsInMap(mapOfWords, line);
        }
        for(auto& tag : cloudOfTags) {
            long double result = std::log(static_cast<long double>(tag.second.countOfArt) / countOfAllArt);
            size_t tmp = countOfAllUniqWords + tag.second.countOfWords;
            long double tmp2 = std::log(1.0 / tmp);
            for(auto& word : mapOfWords) {
                auto check = tag.second.uniqWords.find(word.first);
                if(check == tag.second.uniqWords.end()) {
                    result += tmp2 * word.second;
                } else {
                    result += std::log(static_cast<long double>(check->second + 1) / tmp) * word.second;
                }
            }
            finishHim.emplace_back(result, tag.first);
        }
        long double tmp3 = 0;
        for(auto& i : finishHim) {
                tmp3 += std::exp(i.first);
        }
        for(auto& i : finishHim) {
            i.first = std::exp(i.first) / tmp3;
        }
        std::sort(finishHim.begin(), finishHim.end());

        /* check array begin*/
        // std::cout << "===========\n";
        // for(auto& i : finishHim) {
        //     std::cout << "probability = " << i.first << " % // tag = " << i.second << "\n";
        // }
        // long double kek = 0;
        // for(auto &i : finishHim) {
        //     kek += i.first;
        // }
        // std::cout << "TOTAL = " << kek << "\n";
        /* check array end*/

        /* out of res */
        auto tmp4 = (--finishHim.end());
        fout << tmp4->second;
        while(tmp4->first / (finishHim.end() - 2)->first < MAYBE) {
            tmp4 = (finishHim.end() - 2);
            fout << "," << tmp4->second;
            finishHim.pop_back();
        }
        fout << "\n";
    }
}

void readOfStatistics(std::ifstream &stat,
                            std::map<std::string, TTag> &cloudOfTags,
                            size_t &countOfAllArt,
                            size_t &countOfAllUniqWords) {
    stat >> countOfAllArt >> countOfAllUniqWords;

    while(stat.peek() != EOF) {
        createTag(stat, cloudOfTags);
    }
}

void createTag(std::ifstream &stat,
                    std::map<std::string, TTag> &cloudOfTags) {
    std::string line;
    std::string uniqWord;
    size_t amountOfMeetings = 0;

    stat >> line;
    TTag tagTmp = line;
    size_t amountOfUniqWords = 0;
    stat >> tagTmp.countOfArt >> tagTmp.countOfWords 
    >> amountOfUniqWords;
    for(; amountOfUniqWords > 0; --amountOfUniqWords) {
        stat >> uniqWord >> amountOfMeetings;
        tagTmp.uniqWords.emplace(uniqWord, amountOfMeetings);
    }
    cloudOfTags.emplace(line, tagTmp);
    stat.get();
}