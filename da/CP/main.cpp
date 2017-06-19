#include "tags.hpp"
#include "training.hpp"
#include "classifier.hpp"

void Parsing(int argc, char const *argv[], std::string& inFilename,
                                                std::string& statFilename,
                                                std::string& outFilename);

int main(int argc, char const *argv[]) {
    size_t countOfAllArt = 0;
    size_t countOfAllUniqWords = 0;
    std::string inFilename;
    std::string outFilename;
    std::string statFilename;
    std::unordered_map<std::string, TTag> cloudOfTags;

    Parsing(argc, argv, inFilename, statFilename, outFilename);
    
    if(!strcmp(argv[1], "learn")) {
        std::ifstream fin(inFilename);
        std::ofstream fout(outFilename);
        collectOfStatistics(fin, cloudOfTags, countOfAllArt, countOfAllUniqWords);
        writeOfStatistics(fout, cloudOfTags, countOfAllArt, countOfAllUniqWords);
    } else if(!strcmp(argv[1], "classify")) {
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

void Parsing(int argc, char const *argv[], std::string& inFilename,
                                                std::string& statFilename,
                                                std::string& outFilename) {
    for(size_t i = 2; i < argc; ++i) {
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