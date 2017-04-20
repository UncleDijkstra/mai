#ifndef B_TREE
#define B_TREE

#include <iostream>

struct TItem {
    char *key;
    unsigned long long keyValue;
};

void Swap(char *&x, char *&y);

class TNode {
private:
    unsigned short tCopy;
    bool leaf; // является ли листом
    unsigned short nKeys; // количество ключей
    TItem *keys; // указатель на массив ключей
    TNode **ptrs; // указатель на массив указателей на сыновей 
    void InsertNonFull(TItem& tmp); // Вставка в не заполн
    int FindKey(char *temp);
    void DeleteFromLeaf(int index); // удаление из узла
    void DeleteFromNonLeaf(int index); // удаление из внутреннего
    TItem &FindMax(); // найти max
    TItem &FindMin(); // найти min
    void Fill(int index); // заполнить
    void BorrowFromPrev(int index); // взять у предыдущего
    void BorrowFromNext(int index); // взять у следующего
    void Split(int i); // разрез
    void Merge(int index); // слияние
public:
    TNode(size_t temp); // конструктор
    void Insert(TNode **root ,TItem& temp); // Вставка
    TItem *Search(char *tmp); // Поиск и возвращение элемента
    void Delete(char *temp); // удаление элемента
    void DeleteTree(); // удаление дерева
    bool NSerialize(FILE* f, TNode* node);
    bool NDeserialize(FILE* f, TNode* node);
    ~TNode(); // деструктор
    friend class TBtree;
};

class TBtree {
private:
    size_t t; // минимальная степень дерева
    TNode *root; // указатель на корень
public:
    TBtree(int tmp); // конструктор 
    void Insert(TItem& tmp); // Вставка в дерево
    void DeleteNode(char *tmp); // Удаление из дерева
    TItem *SearchWord(char *tmp); // поиск Слова
    bool Serialize(const char *file);
    bool Deserialize(const char *file);
    ~TBtree(); // деструктор
    friend class TNode;
};

#endif
