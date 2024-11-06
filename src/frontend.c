#include <stdio.h>
#include <ncurses.h>

#include "../include/frontend.h"
#include "../include/shared.h"

void printNode(Node *node, Node *selected_node) {
    
    // EXAMPLE !!
    selected_node = node;    

    if (node == selected_node) {
        char str[sizeof(getFileName(node->name)) + 2 + STR_END];
        snprintf(str, sizeof(str), "%s\n", getFileName(node->name));
        printw_selected(str);
    } 
    else 
        printw("%s\n", getFileName(node->name));
    
    refresh();
    
    for (int i = 0; i < node->num_children; i++) {
        printChilds(node->children[i], selected_node, "", i == node->num_children-1);
    }
}

void printChilds(Node *node, Node *selected_node, char *tabs, bool isLast) {
    const char *toAdd = isLast ? "    " : "│   ";

    if (node == selected_node) {
        char str[sizeof(tabs) + sizeof(getFileName(node->name)) + 5 + STR_END];
        snprintf(str, sizeof(str), "%s%s── %s\n", tabs, isLast ? "└" : "├", getFileName(node->name));
        printw_selected(str);
    } 
    else 
        printw("%s%s── %s\n", tabs, isLast ? "└" : "├", getFileName(node->name));
    refresh();
    
    char new_tabs[255];
    snprintf(new_tabs, sizeof(new_tabs), "%s%s", tabs, toAdd);

    for (int i = 0; i < node->num_children; i++) {
        printChilds(node->children[i], selected_node, new_tabs, i == node->num_children-1);
    }
}

/**
* @todo make it blink
*/
void printw_selected(const char *str) {
    // int len = strlen(str);
    attron(A_BLINK | A_REVERSE);
    printw(str);
    attroff(A_BLINK | A_REVERSE);
}

char* getFileName(char path[]) {
    int last = 0;
    
    for (int i = 0; i < 255 && path[i] != '\0'; i++) {
        if (path[i] == '/') {
            last = i + 1; 
        }
    }

    // Restituisci il puntatore all'ultimo nome del file
    return &path[last];
}

