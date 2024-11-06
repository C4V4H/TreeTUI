#include <ncurses.h>
#include <locale.h>

#include "../include/shared.h"
#include "../include/backend.h"
#include "../include/frontend.h"

/** 
* Main function to run ncurses TUI to show the tree
* @todo Add the folder to analize name on the args
*/
int main() {
    Node *selected_dir = NULL;
    
    setlocale(LC_ALL, "");
    // Inizializzazione di ncurses
    initscr();            // Avvia la modalità ncurses
    cbreak();             // Disabilita il buffering della linea
    noecho();             // Non mostra i caratteri premuti

    curs_set(FALSE);      // boh

    Node *node = initNode("../../Algorithms");
    printNode(node, selected_dir);

    refresh();            // Mostra l'output sullo schermo
    getch();              // Aspetta un input per terminare

    // Termina ncurses
    endwin();
    return 0;    
}

