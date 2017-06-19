#include "classifier.hpp"

void addWordsInMap(std::unordered_map<std::string, size_t>& mapOfWords,
                        const std::string& line) {
    std::string tmp;
    for(size_t i = 0; i < line.size(); ++i) {
        if(isalpha(line[i])) {
            tmp += tolower(line[i]);
        } else {
            if(!tmp.empty()) {
                mapOfWords[tmp] += 1;
            }
            tmp.clear();
        }
    }
    if(!tmp.empty()) {
        mapOfWords[tmp] += 1;
    }
}

void classification(std::ifstream& fin, std::ifstream& stat,
                            std::ofstream& fout,
                            std::unordered_map<std::string, TTag>& cloudOfTags,
                            size_t& countOfAllArt,
                            size_t& countOfAllUniqWords) {
    size_t nOfLines = 0;
    std::string line;

    readOfStatistics(stat, cloudOfTags, countOfAllArt, countOfAllUniqWords);

    while(fin.peek() != EOF) {
        std::unordered_map<std::string, size_t> mapOfWords;
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

        std::sort(finishHim.begin(), finishHim.end());

        /* check array begin*/
        std::cout << "===========\n";
        for(auto& i : finishHim) {
            std::cout << "probability = " << i.first << " % // tag = " << i.second << "\n";
        }
        /* check array end*/

        /* out of res */
        fout << (--finishHim.end())->second;
        while(std::abs((finishHim.end() - 2)->first) - std::abs((finishHim.end() - 1)->first) < MAYBE) {
            fout << "," << (finishHim.end() - 2)->second;
            finishHim.pop_back();
        }
        fout << "\n";
    }
}

void readOfStatistics(std::ifstream& stat,
                            std::unordered_map<std::string, TTag>& cloudOfTags,
                            size_t& countOfAllArt,
                            size_t& countOfAllUniqWords) {
    stat >> countOfAllArt >> countOfAllUniqWords;

    while(stat.peek() != EOF) {
        createTag(stat, cloudOfTags);
    }
}

void createTag(std::ifstream& stat,
                    std::unordered_map<std::string, TTag>& cloudOfTags) {
    std::string line;
    std::string uniqWord;
    size_t amountOfMeetings = 0;
    size_t amountOfUniqWords = 0;

    stat >> line;
    TTag tagTmp;
    stat >> tagTmp.countOfArt >> tagTmp.countOfWords 
    >> amountOfUniqWords;
    for(; amountOfUniqWords > 0; --amountOfUniqWords) {
        stat >> uniqWord >> amountOfMeetings;
        tagTmp.uniqWords.emplace(uniqWord, amountOfMeetings);
    }
    cloudOfTags.emplace(line, std::move(tagTmp));
}