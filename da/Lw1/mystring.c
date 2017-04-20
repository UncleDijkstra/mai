#include "mystring.h"

void MyStrcpy(char *output, char *input) {
    while (*input) {
        *output++ = *input++;
    }
    *output = '\0';
}

int MyStrlen(char *string) {
    register const char *pStr;
    
    for (pStr = string; *pStr; ++pStr);
    return(pStr - string);
}