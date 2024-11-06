// frontend.h

#ifndef FRONTEND_H_jfweoifjweoifjwfoiwjfdoiewjf
#define FRONTEND_H_jfweoifjweoifjwfoiwjfdoiewjf

#include "shared.h"

#define STR_END 2

#define DEFAULT 0
// dir state ('+' when its open &  '-' when is closed)
#define DIR_STATE_SYMBOL_COLOR 1
#define DIR_COLOR 2
#define FILE_COLOR 3
// color for binary files
#define BIN_COLOR 4
// color for the obj dir
#define OBJ_DIR_COLOR 5
// color for the bin dir
#define BIN_DIR_COLOR 6
// color for the src dir
#define SRC_DIR_COLOR 7
// color for the include dir
#define INCLUDE_DIR_COLOR 8
// color for .c files
#define C_FILE_COLOR 9
// color for .h files
#define H_FILE_COLOR 10


// #define KEY_UP A
// #define KEY_DOWN B
// #define KEY_RIGHT C
// #define KEY_LEFT D

void startTUI(Node*);
void initColors();
void printColored(short, char[], bool, bool);
void printNode(Node*, Node*);
void printChilds(Node*, Node*, char[], bool);
char* getFileName(char[]);
void removeLast(char[], const char[]);
void printw_selected(const char*);
Node* getNext(Node*, Node*);
Node* getPrevious(Node*, Node*);
Node* getInner(Node*, Node*);
Node* getOuter(Node*, Node*);
void input_handler(Node*);

#endif
