#include <cctype>

#include "rb.h"

void Parsing(char* action, char* buffer, ulli* value);

int main() {
    TRBtree tree;
    char buffer[257];
    char action;
    ulli value;
    while(true) {
        bool flag = true;
        TRBtree::TNode* tmp = nullptr;
        TRBtree::TNode* temp = new TRBtree::TNode;
        Parsing(&action, buffer, &value);
        if(action == 'E') {
            break;
        }
        switch(action) {
            case '+': {
                temp->key = new char[strlen(buffer) + 1];
                strcpy(temp->key, buffer);
                temp->value = value;
                temp->color = TRBtree::RED;

                if(!tree.Search(buffer)) {
                    tree.Insert(*temp);
                    std::cout << "OK\n";
                    flag = false;
                } else {
                    std::cout << "Exist\n";
                }
                break;
            }
            case '-': {
                tmp = tree.Search(buffer);
                if(tmp) {
                    tree.RBDelete(tmp);
                    std::cout << "OK\n";
                } else {
                    std::cout << "NoSuchWord\n";
                }
                break;
            }
            case 'S': {
                tree.Serialize(buffer);
                break;
            }
            case 'L': {
                tree.Deserialize(buffer);
                break;
            }
            case 'F': {
                tmp = tree.Search(buffer);
                tmp ? std::cout << "OK: " << tmp->value <<
                    "\n" : std::cout << "NoSuchWord\n";
                break;
            }
        }
        if(flag) {
            delete temp;
        }
    }
    return 0;
}

void Parsing(char* action, char* buffer, ulli* value) {
    char ch;
    size_t i = 0;
    bool flag = true;

    ch = std::cin.get();

    if(ch == EOF) {
        *action = 'E';
        return;
    }

    if(ch == '+' || ch == '-') {
        *action = ch;
        std::cin.get();
        while(flag) {
            ch = tolower(std::cin.get());
            if(!isalpha(ch)) {
                flag = false;
            } else {
                buffer[i++] = ch;
            }
        }
        buffer[i] = '\0';
        if(*action == '+') {
            *value = 0;

            while ((ch = std::cin.get()) != '\n') {
                *value = (*value) * 10 + ch - '0';
            }
        }
    } else if(ch == '!') {
        std::cin.get();
        while((ch = std::cin.get()) != ' ') {
            buffer[i++] = ch;
        }
        buffer[i] = '\0';
        i = 0;
        *action = buffer[0];
        while((ch = std::cin.get()) != '\n') {
            buffer[i++] = ch;
        }
        buffer[i] = '\0';
    } else {
        *action = 'F';
        buffer[0] = tolower(ch);
        i++;
        while((ch = std::cin.get()) != '\n') {
            buffer[i++] = tolower(ch);
        }
        buffer[i] = '\0';
    }
}
