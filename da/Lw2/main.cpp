#include <cstdio>
#include "btree.h"
#include <string.h>
#include <stdlib.h>

char LowerCase(char c);
bool IsLetter(char c);
void Parsing(char *action, char *buffer, unsigned long long *value);
void PrintItem(TItem *temp);

const size_t T = 200;

int main() {
    TBtree tree(T);
    char buffer[257];
    char action;
    unsigned long long value;
    TItem temp;
    while(true) {
        Parsing(&action, buffer, &value);
        if(action == 'E') {
            break;
        }
        switch(action) {
            case '+':
                temp.key = (char *)malloc(sizeof(char) * strlen(buffer) + 1);
                strcpy(temp.key, buffer);
                temp.keyValue = value;
                if(!tree.SearchWord(buffer)) {
                    tree.Insert(temp);
                } else {
                    printf("Exist\n");
                }
                 free(temp.key);
                break;
            case '-':
                    tree.DeleteNode(buffer);
                break;
            case 'S':
                if (tree.Serialize(buffer)) {
                    printf("OK\n");
                }
                else {
                    printf("ERROR: Couldn't create file\n");
                }
                break;
            case 'L':
                if (tree.Deserialize(buffer)) {
                    printf("OK\n");
                }
                else {
                    printf("ERROR: Couldn't load file\n");
                }
                break;
            case 'F':
                PrintItem(tree.SearchWord(buffer));
                break;
        }
    }
    return 0;
}

char LowerCase(char c) {
    return c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c; 
}

bool IsLetter(char c) {
    return c >= 'a' && c <= 'z' ? true : false;
}

void Parsing(char *action, char *buffer, unsigned long long *value) {
    char ch;
    size_t i = 0;
    bool flag = true;

    ch = getchar();

    if(ch == EOF) {
        *action = 'E';
        return;
    }

    if(ch == '+' || ch == '-') {
        *action = ch;
        getchar();
        while(flag) {
            ch = LowerCase(getchar());
            if(!IsLetter(ch)) {
                flag = false;
            } else {
                buffer[i++] = ch;
            }
        }
        buffer[i] = '\0';
        if(*action == '+') {
            *value = 0;

            while ((ch = getchar()) != '\n') {
                *value = (*value) * 10 + ch - '0';
            }
        }
    } else if(ch == '!') {
        getchar();
        while((ch = getchar()) != ' ') {
            buffer[i++] = ch;
        }
        buffer[i] = '\0';
        i = 0;
        *action = buffer[0];
        while((ch = getchar()) != '\n') {
            buffer[i++] = ch;
        }
        buffer[i] = '\0';
    } else {
        *action = 'F';
        buffer[0] = LowerCase(ch);
        i++;
        while((ch = getchar()) != '\n') {
            buffer[i++] = LowerCase(ch);
        }
        buffer[i] = '\0';
    }
}

void PrintItem(TItem *temp) {
    if(temp) {
        printf("OK: %llu\n", temp->keyValue);
    } else {
        printf("NoSuchWord\n");
    }
}