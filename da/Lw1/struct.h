#ifndef STRUCT_H
#define STRUCT_H

// const static int MY_STRING_SIZE = 64;
// const static int MY_KEY_SIZE = 32;
// const static int MY_NUMERAL_SYSTEM = 16;
// const static int SPACE4NULL = 1;

enum {MY_STRING_SIZE = 64};
enum {MY_KEY_SIZE = 32};
enum {MY_NUMERAL_SYSTEM = 16};
enum {SPACE4NULL = 1};

typedef struct TElem {
    char key[MY_KEY_SIZE + SPACE4NULL];
    char string[MY_STRING_SIZE + SPACE4NULL];
} TElem;

#endif