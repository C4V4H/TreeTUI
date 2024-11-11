// shared.h

#ifndef SHARED_H_jfweoifjweoifjwfoiwjfdoiewjf
#define SHARED_H_jfweoifjweoifjwfoiwjfdoiewjf


#include <wchar.h>

#define DEFAULT 0
#define T_DIR 1
#define T_HIDDEN_DIR 2
#define T_FILE 3
#define T_EXE 4
#define T_DIR_LINK 5
#define T_FILE_LINK 6
#define T_UNKNOWN 7
#define TABS_COLOR 8

typedef struct Node {
    char *path;
    struct Node *father;
    struct Node **children;
    int num_children;
    int is_expanded;    // Flag per il collasso/espansione
    int type;
    wchar_t icon;
    char *name;
} Node;


char* getFileName(char[]);

#endif
