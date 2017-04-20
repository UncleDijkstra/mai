#include "SuffTree.h"

int main() {
    std::string pattern;
    std::string text;
    TST tree;
    std::cin >> pattern;
  
    for (const auto& i: pattern) {
        tree.ExtendSuffTree(i);
    }
    while (std::cin >> text) {
        std::vector<int> ms (text.size(), 0);
        tree.MS(ms, text);
    }
    return 0;
}
