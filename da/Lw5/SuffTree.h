#ifndef TST_H
#define TST_H
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <iostream>

const int INF = 1e9;

class TNode {
public:
    TNode(const int& fpos, const int& tmpEdgeLength, TNode* tmpParent);
    friend class TST;
private:
    int firstPos;
    int edgeLength;
    TNode *parent;
    std::map<int, TNode *> chil;
    TNode *suffLink;
};

class TST {
private:
    int n;
    int pos;
    std::vector<int> symPos;
    TNode *setFirst(int&, const std::string&);
  
public:
    TNode *root;
    TST();
    void ExtendSuffTree(const int& sym);
    void MS(std::vector<int>&, const std::string&);
};


#endif
