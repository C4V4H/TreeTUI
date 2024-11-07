// shared.h

#ifndef SHARED_H_jfweoifjweoifjwfoiwjfdoiewjf
#define SHARED_H_jfweoifjweoifjwfoiwjfdoiewjf

#define DEFAULT 0
#define T_DIR 1
#define T_HIDDEN_DIR 2
#define T_FILE 3
#define T_BIN 4
#define T_UNKNOWN 5
#define DIR_STATE_SYMBOL_COLOR 6

typedef struct Node {
    char *name;
    struct Node *father;
    struct Node **children;
    int num_children;
    int is_expanded;    // Flag per il collasso/espansione
    int type;
} Node;


char* getFileName(char[]);

#endif
