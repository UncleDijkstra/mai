#include "tags.hpp"
#include "training.hpp"
#include "classifier.hpp"

int main(int argc, char const *argv[]) {
    size_t countOfAllArt = 0;
    size_t countOfAllUniqWords = 0;
    std::string inFilename;
    std::string outFilename;
    std::string statFilename;
    std::map<std::string, TTag> cloudOfTags;

    if(!strcmp(argv[1], "learn")) {
        learnParsing(argc, argv, inFilename, outFilename);
        std::ifstream fin(inFilename);
        std::ofstream fout(outFilename);
        collectOfStatistics(fin, cloudOfTags, countOfAllArt, countOfAllUniqWords);
        writeOfStatistics(fout, cloudOfTags, countOfAllArt, countOfAllUniqWords);
    } else if(!strcmp(argv[1], "classify")) {
        classParsing(argc, argv, inFilename, statFilename, outFilename);
        std::ifstream fin(inFilename);
        std::ifstream stat(statFilename);
        std::ofstream fout(outFilename);
        classification(fin, stat, fout, cloudOfTags, 
            countOfAllArt, countOfAllUniqWords);
    } else {
        std::cout << "Error\n";
        exit(0);
    }

    return 0;
}