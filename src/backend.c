#include <string.h>
#include <dirent.h>
#include <sys/dirent.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/shared.h"
#include "../include/backend.h"


Node* initNode(char dir[]) {
    DIR *folder;
    Node *node = malloc(sizeof(Node));  // Alloca memoria per il nodo
    if (node == NULL) {
        perror("malloc");
        return NULL;
    }

    node->name = strdup(dir);  // Copia il nome della directory
    node->num_children = 0;
    node->is_expanded = 1;
    node->children = NULL;  // Inizialmente, nessun figlio

    folder = opendir(dir);
    
    struct dirent *entry;
    while ( (entry=readdir(folder)) != NULL ) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;  // Salta le directory speciali
        }

        //mette il path completo        
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        // Alloca memoria per un nuovo figlio
        node->num_children++;
        node->children = realloc(node->children, node->num_children * sizeof(Node *));
        if (node->children == NULL) {
            perror("realloc");
            closedir(folder);
            free(node->name);
            free(node);
            return NULL;
        }

        if (entry->d_type == DT_DIR) {
            node->children[node->num_children - 1] = initNode(path);  // Directory ricorsiva
        } else if (entry->d_type == DT_REG) {
            node->children[node->num_children - 1] = getFile(entry->d_name);  // File normale
        }    
    }

    closedir(folder);

    return node;   
}

Node* getFile(char *name) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        perror("malloc");
        return NULL;
    }
    node->name = strdup(name);  // Copia il nome del file
    node->children = NULL;
    node->num_children = 0;
    node->is_expanded = 0;
    return node;
}
