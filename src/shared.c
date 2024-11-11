#include "../include/shared.h"

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


