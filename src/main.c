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
    // @todo get the dir by arg and check if it exist
    Node *node = initNode("../../Algorithms", NULL);
    
    startTUI(node);    
}

