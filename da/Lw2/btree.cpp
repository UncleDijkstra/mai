#include <cstdio>
#include <stdlib.h>
#include "btree.h"
#include <string.h>
#include <time.h>

// ################ NODE #####################

void Swap(char *&x, char *&y) {
    char *temp = x;
    x = y;
    y = temp;
}

TNode::TNode(size_t temp) {
    nKeys = 0;
    leaf = true;
    tCopy = temp;
    keys = (TItem *)malloc(sizeof(TItem) * (2 * temp - 1));
    ptrs = (TNode **)malloc(sizeof(TNode *) * 2 * temp);
    for(int i = 0; i < 2 * temp; ++i) {
        ptrs[i] = NULL;
        if(i < 2 * temp - 1) {
            keys[i].key = NULL;
        }
    }
}

TItem *TNode::Search(char *tmp) {
    int i = 0;
    while(i < nKeys && 0 < strcmp(tmp, keys[i].key)) {
        ++i;
    }
    if(i < nKeys && !strcmp(tmp, keys[i].key)){
        return &keys[i];
    } else if(leaf) {
        return NULL;
    } else {
        return ptrs[i]->Search(tmp);
    }
}

void TNode::Split(int i) {
    int j;
    TNode *z = new TNode(tCopy);
    TNode *y = ptrs[i];
    z->leaf = y->leaf;
    z->nKeys = tCopy - 1;
    for(j = 0; j < tCopy - 1; ++j) {
        Swap(z->keys[j].key, y->keys[j + tCopy].key);
        z->keys[j].keyValue = y->keys[j + tCopy].keyValue;
    }
    if(!y->leaf) {
        for(j = 0; j < tCopy; ++j) {
            z->ptrs[j] = y->ptrs[j + tCopy];
        }
    }
    y->nKeys = tCopy - 1;
    for(j = nKeys; j >= i + 1; --j) {
        ptrs[j + 1] = ptrs[j];
    }
    ptrs[i + 1] = z;
    for(j = nKeys - 1; j >= i; --j) {
        Swap(keys[j + 1].key, keys[j].key);
        keys[j + 1].keyValue = keys[j].keyValue;
    }
    Swap(keys[i].key, y->keys[tCopy - 1].key);
    keys[i].keyValue = y->keys[tCopy - 1].keyValue;
    ++nKeys;
}

void TNode::Merge(int index) {
    int i;
    TNode *child = ptrs[index];
    TNode *bro = ptrs[index + 1];
    // копируем ключ в сына
    char *temp = child->keys[tCopy - 1].key;
    child->keys[tCopy - 1].key = keys[index].key;
    keys[index].key = temp;
    child->keys[tCopy - 1].keyValue = keys[index].keyValue;
    // Копируем ключи из правого сына в левого
    for(i = 0; i < bro->nKeys; ++i) {
        Swap(child->keys[i + tCopy].key, bro->keys[i].key);
        child->keys[i + tCopy].keyValue = bro->keys[i].keyValue;
    }
    // копируем указатели, если не лист
    if(!child->leaf) {
        for(i = 0; i <= bro->nKeys; ++i) {
            child->ptrs[i + tCopy] = bro->ptrs[i];
        }
    }
    // сдвигаем в текущем узле после index ключи влево
    for(i = index + 1; i < nKeys; ++i) {
        // keys[i - 1] = keys[i];
        Swap(keys[i - 1].key, keys[i].key);
        keys[i - 1].keyValue = keys[i].keyValue;
    }
    // сдвигаем в текущем узле после index укахатели влево
    for(i = index + 2; i <= nKeys; ++i) {
        ptrs[i - 1] = ptrs[i];
    }
    ptrs[nKeys] = NULL;
    child->nKeys += bro->nKeys + 1; 
    --nKeys;
    delete bro;
}

void TNode::Insert(TNode **root ,TItem& temp) {
    if(nKeys == 2 * tCopy - 1) {
        TNode *s = new TNode(tCopy);
        *root = s;
        s->leaf = false;
        s->nKeys = 0;
        s->ptrs[0] = this;
        s->Split(0);
        s->InsertNonFull(temp);
    } else {
        (*root)->InsertNonFull(temp);
    }
}

void TNode::InsertNonFull(TItem& tmp) {
    int i = nKeys - 1;
    if(leaf) {
        while(i >= 0 && 0 > strcmp(tmp.key, keys[i].key)) {
            Swap(keys[i + 1].key, keys[i].key);
            keys[i + 1].keyValue = keys[i].keyValue;
            --i;
        }
        keys[i + 1].key = (char *)malloc(sizeof(char) * strlen(tmp.key) + 1);
        strcpy(keys[i + 1].key, tmp.key);
        keys[i + 1].keyValue = tmp.keyValue;
        ++nKeys;
         printf("OK\n");
    } else {
        while(i >= 0 && 0 > strcmp(tmp.key, keys[i].key)) {
            --i;   
        }
        ++i;
        if(ptrs[i]->nKeys == 2 * tCopy - 1) {
            Split(i);
            if(0 < strcmp(tmp.key, keys[i].key)) {
                ++i;
            }
        }
        ptrs[i]->InsertNonFull(tmp);
    }
}

// int TNode::FindKey(char *temp) {
//    int i = 0;
//    while(i < nKeys && 0 < strcmp(temp, keys[i].key)) {
//        ++i;
//    }
//    return i;
// }

int TNode::FindKey(char *temp) {
    size_t first = 0;
    size_t last = nKeys;
    while(first < last) {
        size_t mid = first + (last - first) / 2;
        if(0 >= strcmp(temp, keys[mid].key)) {
            last = mid;
        } else {
            first = mid + 1;
        }
    }
    return last;
}

void TNode::DeleteFromLeaf(int index) {
    for (int i = index + 1; i < nKeys; ++i) {
        Swap(keys[i-1].key, keys[i].key);
        keys[i-1].keyValue = keys[i].keyValue;
    }
    --nKeys;
    free(keys[nKeys].key);
    keys[nKeys].key = NULL;
     printf("OK\n");
}

TItem &TNode::FindMax() {
    TNode *temp = this;
    while(!temp->leaf) {
        temp = temp->ptrs[temp->nKeys];
    }
    return temp->keys[temp->nKeys - 1];
}

TItem &TNode::FindMin() {
    TNode *temp = this;
    while(!temp->leaf) {
        temp = temp->ptrs[0];
    }
    return temp->keys[0];
}

void TNode::Fill(int index) {
    if(index && ptrs[index - 1]->nKeys >= tCopy) {
        BorrowFromPrev(index);
    } else if (index!= nKeys && ptrs[index + 1 ]->nKeys >= tCopy) {
        BorrowFromNext(index);
    } else {
        if (index != nKeys) {
            Merge(index);
        }
        else
            Merge(index - 1);
    }
}

void TNode::BorrowFromPrev(int index) {
    TNode *child = ptrs[index];
    TNode *sibling = ptrs[index - 1];

    for (int i = child->nKeys - 1; i >= 0; --i) {
        Swap(child->keys[i + 1].key, child->keys[i].key);
        child->keys[i + 1].keyValue = child->keys[i].keyValue;
    }

    if (!child->leaf) {
        for(int i = child->nKeys; i>=0; --i)
            child->ptrs[i + 1] = child->ptrs[i];
    }

    Swap(child->keys[0].key, keys[index - 1].key);
    child->keys[0].keyValue = keys[index - 1].keyValue;

    if (!leaf) {
        child->ptrs[0] = sibling->ptrs[sibling->nKeys];
    }

    Swap(keys[index - 1].key, sibling->keys[sibling->nKeys - 1].key);
    keys[index - 1].keyValue = sibling->keys[sibling->nKeys - 1].keyValue;

    ++child->nKeys;
    --sibling->nKeys;

    return;
}

void TNode::BorrowFromNext(int index) {
    TNode *child=ptrs[index];
    TNode *sibling=ptrs[index+ 1];

    Swap(child->keys[(child->nKeys)].key, keys[index].key);
    child->keys[(child->nKeys)].keyValue = keys[index].keyValue;

    if (!(child->leaf)) {
        child->ptrs[(child->nKeys)+1] = sibling->ptrs[0];
    }

    Swap(keys[index].key, sibling->keys[0].key);
    keys[index].keyValue = sibling->keys[0].keyValue;
 
    for (int i = 1; i<sibling->nKeys; ++i) {
        Swap(sibling->keys[i-1].key, sibling->keys[i].key);
        sibling->keys[i-1].keyValue = sibling->keys[i].keyValue;
    }

    if (!sibling->leaf) {
        for(int i = 1; i <= sibling->nKeys; ++i)
            sibling->ptrs[i - 1] = sibling->ptrs[i];
    }

    ++child->nKeys;
    --sibling->nKeys;

    return;
}

void TNode::DeleteFromNonLeaf(int index) {
    char array[257];
    strcpy(array, keys[index].key);
    if(ptrs[index]->nKeys >= tCopy) {
        TItem &temp = ptrs[index]->FindMax();
        free(keys[index].key);
        keys[index].key = (char *)malloc(sizeof(char) * strlen(temp.key) + 1);
        strcpy(keys[index].key, temp.key);
        keys[index].keyValue = temp.keyValue;
        ptrs[index]->Delete(temp.key);
    } else if(ptrs[index + 1]->nKeys >= tCopy) {
        TItem &temp = ptrs[index + 1]->FindMin();
        free(keys[index].key);
        keys[index].key = (char *)malloc(sizeof(char) * strlen(temp.key) + 1);
        strcpy(keys[index].key, temp.key);
        keys[index].keyValue = temp.keyValue;
        ptrs[index + 1]->Delete(temp.key);
    } else {
        Merge(index);
        ptrs[index]->Delete(array);
    }
}

void TNode::Delete(char *temp) {
    int index = FindKey(temp);
    if(index < nKeys && strcmp(temp, keys[index].key) == 0) {
        if(leaf) {
            DeleteFromLeaf(index);
        } else {
            DeleteFromNonLeaf(index);
        } 
    } else {
        if(leaf) {
            printf("NoSuchWord\n");
            return;
        }
        bool flag = index == nKeys ? true : false;
        if(ptrs[index]->nKeys < tCopy) {
            Fill(index);
        }
        if(flag && index > nKeys) {
            ptrs[index - 1]->Delete(temp);
        } else {
            ptrs[index]->Delete(temp);
        }
    }
    return;
}

bool TNode::NSerialize(FILE* f, TNode* node) {
    if (fwrite(&node->nKeys, sizeof(node->nKeys), 1, f) != 1) {
        return false;
    }

    if (fwrite(&node->leaf, sizeof(node->leaf), 1, f) != 1) {
        return false;
    }

    for (size_t i = 0; i < node->nKeys; ++i) {
        const TItem* data = &node->keys[i];
        const size_t strLen = strlen(data->key);
        const char* str = data->key;

        if (fwrite(&strLen, sizeof(strLen), 1, f) != 1) {
            return false;
        }

        if (fwrite(str, sizeof(char), strLen, f) != strLen) {
            return false;
        }

        if (fwrite(&data->keyValue, sizeof(data->keyValue), 1, f) != 1) {
            return false;
        }
    }

    if (!node->leaf) {
        for (size_t i = 0; i < node->nKeys + 1; ++i) {
            if (!NSerialize(f, node->ptrs[i])) {
                return false;
            }
        }
    }

    return true;
}

bool TNode::NDeserialize(FILE* f, TNode* node) {
    char buffer[257];

    if (fread(&node->nKeys, sizeof(node->nKeys), 1, f) != 1) {
        return false;
    }

    if (fread(&node->leaf, sizeof(node->leaf), 1, f) != 1) {
        return false;
    }

    for (size_t i = 0; i < node->nKeys; ++i) {
        TItem* data = &node->keys[i];
        size_t strLen = 0;

        if (fread(&strLen, sizeof(strLen), 1, f) != 1) {
            return false;
        }

        if (fread(buffer, sizeof(char), strLen, f) != strLen) {
            return false;
        }

        if (fread(&data->keyValue, sizeof(data->keyValue), 1, f) != 1) {
            return false;
        }

        buffer[strLen] = '\0';
        data->key = (char *)malloc(sizeof(char) * strLen);
        strcpy(data->key, buffer);
    }

    if (!node->leaf) {
        for (size_t i = 0; i < node->nKeys + 1; ++i) {
            node->ptrs[i] = new TNode(tCopy);

            if (!NDeserialize(f, node->ptrs[i])) {
                return false;
            }
        }
    }

    return true;
}

TNode::~TNode() {
    for(int i = 0; i < nKeys; ++i) {
        free(keys[i].key);
    }
    free(keys);
    free(ptrs);
}

void TNode::DeleteTree() {
    TNode *tmp = this;
    if (tmp == NULL) {
        return;
    }
    for (int i = 0; i < tmp->nKeys + 1; ++i) {
            tmp->ptrs[i]->DeleteTree();
    }
    delete(tmp);
}

// ################ TREE ##################

TBtree::TBtree(int tmp) {
    t = tmp < 2 ? 2 : tmp;  
    root = new TNode(t);
}

void TBtree::Insert(TItem& tmp) {
    root->Insert(&root, tmp);
}

TItem *TBtree::SearchWord(char *tmp) {
    if(root) {
        return root->Search(tmp);
    } else {
        return NULL;
    }
}

void TBtree::DeleteNode(char *tmp) {
    root->Delete(tmp);
    if (root->nKeys == 0) {
        TNode *temp = root;
        if (!root->leaf) {
            root = root->ptrs[0];
            temp->ptrs[0] = NULL;
            delete temp;
        }
    }
}

bool TBtree::Serialize(const char* file) {
    FILE* f = fopen(file, "wb");

    if (f == NULL) {
        return false;
    }

    if (fwrite(&t, sizeof(t), 1, f) != 1) {
        return false;
    }

    bool ans = root->NSerialize(f, root);

    fclose(f);

    return ans;
}

bool TBtree::Deserialize(const char* file) {
    FILE* f = fopen(file, "rb");

    if (f == NULL) {
        return false;
    }

    if (fread(&t, sizeof(t), 1, f) != 1) {
        return false;
    }

    TNode* rootNew = new TNode(t);
    bool ans = root->NDeserialize(f, rootNew);

    fclose(f);

    if (ans) {
        root->DeleteTree();

        root = rootNew;

        return true;
    }
    else {
        rootNew->DeleteTree();

        return false;
    }
}

TBtree::~TBtree() { 
    root->DeleteTree();
}
