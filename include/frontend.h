// frontend.h

#ifndef FRONTEND_H_jfweoifjweoifjwfoiwjfdoiewjf
#define FRONTEND_H_jfweoifjweoifjwfoiwjfdoiewjf

#include "shared.h"

#define STR_END 2



// #define KEY_UP A
// #define KEY_DOWN B
// #define KEY_RIGHT C
// #define KEY_LEFT D

void startTUI(Node*, bool);
void initColors();
// void printColored(short, char[], bool, bool);
void printNode(Node*, Node*, bool);
void printChilds(Node*, Node*, char[], bool, bool);
void removeLast(char[], const char[]);
// void printw_selected(char*, int);

void input_handler(Node*, bool);
Node* getNext(Node*, Node*);
Node* getPrevious(Node*, Node*);
Node* getInner(Node*, Node*);
Node* getOuter(Node*, Node*);

// void print_dir_sym(bool);
void toggle_dir(Node*);
void print_colored(int, bool, bool, const char *, ...);


#endif
