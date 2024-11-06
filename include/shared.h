// shared.h

#ifndef SHARED_H_jfweoifjweoifjwfoiwjfdoiewjf
#define SHARED_H_jfweoifjweoifjwfoiwjfdoiewjf


typedef struct Node {
    char *name;
    struct Node *father;
    struct Node **children;
    int num_children;
    int is_expanded;    // Flag per il collasso/espansione
} Node;

#endif
