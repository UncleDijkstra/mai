#include "SuffTree.h"

TNode::TNode(const int& fpos, const int& tmpEdgeLength, TNode* tmpParent) {
    firstPos = fpos;
    edgeLength = tmpEdgeLength;
    parent = tmpParent;
}

TST::TST() {
    n = 0;
    pos = 0;
    root = new TNode(0, INF, nullptr);
    root->parent = root;
}

void TST::ExtendSuffTree(const int& sym) {
    symPos.emplace_back(sym);
    n++;
    pos++;
    TNode *node = root;
    TNode *last = root;
    while (pos > 0) {
        while ((node->chil.find(symPos[n - pos]) != node->chil.end()) &&
               (pos > node->chil[symPos[n - pos]]->edgeLength)) {
            node = node->chil[symPos[n - pos]];
            pos -= node->edgeLength;
        }
        int edge = symPos[n - pos];
        std::map<int, TNode *>::iterator child = node->chil.find(edge);
        int t = (child == node->chil.end()) ? -1 : symPos[child->second->firstPos + pos - 1];
        if (child == node->chil.end()) {
            node->chil[edge] = new TNode(n - pos, INF, node);
            last->suffLink = node;
            last = root;
          
        } else if (t == sym) {
            last->suffLink = node;
          return;
        } else {
            TNode *splitNode = new TNode(child->second->firstPos, pos - 1, child->second->parent);
            splitNode->chil[sym] = new TNode(n - 1, INF, splitNode);
            splitNode->chil[t] = child->second;
            child->second->firstPos += pos - 1;
            child->second->edgeLength -= pos - 1;
            child->second->parent = splitNode;
            child->second = splitNode;
            last->suffLink = splitNode;
            last = splitNode;
        }
        if (node == root) {
            --pos;
        } else {
            node = node->suffLink;
        }
  }
}

TNode *TST::setFirst(int& ms, const std::string& pattern) {
    int smth = pattern.find(pattern[0]);
    TNode *tmp = root;

    if (smth != std::string::npos) {
        std::map<int, TNode *>::iterator child = tmp->chil.find(pattern[0]);
        while (smth < pattern.size()) {
            if (child != tmp->chil.end()) {
                for (int l = 0, i = child->second->firstPos;
                    l < child->second->edgeLength && i < n && smth < pattern.size();
                    i++, smth++, l++) {
                    if (pattern[smth] != symPos[i]) {
                        return tmp;
                    }
                    ++ms;
                }

                tmp = child->second;
                child = child->second->chil.find(pattern[smth]);
            } else {
                return tmp;
            }
        }
    }
    return tmp;
}

void TST::MS(std::vector<int>& ms, const std::string& text) {
    root->suffLink = root;
    TNode *node = setFirst(ms[0], text);

    for (int i = 1; i < ms.size(); i++) {
        if (ms[i - 1] == n) {
            std::cout << i << std::endl;
        }
        int nodeegin = node->firstPos;
        int whatsLeft = n - node->firstPos;
        node = (node->edgeLength > n) ? node->parent->suffLink : node->suffLink;
        while (whatsLeft > node->edgeLength) {
            for (const auto& child: node->chil) {
                if (child.second->firstPos == nodeegin) {
                    node = child.second;
                    break;
                }
            }
            whatsLeft -= node->edgeLength;
            nodeegin += n - node->firstPos;
        }
        for (int j = i, l = nodeegin; j < text.size() && l < n; ++j, ++l) {
            if (text[j] != symPos[l]) {
                break;
            }
            ++ms[i];
            if (l == node->edgeLength) {
                std::map<int, TNode *>::iterator child = node->chil.find(text[j + 1]);
                if(child != node->chil.end()) {
                    node = child->second;
                    l = node->firstPos;
                } else {
                    l = n + 1;
                }
            }
        }
    }
}

