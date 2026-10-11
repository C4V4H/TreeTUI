#include <ncurses.h>
#include <locale.h>
#include <stdbool.h>

#include "../include/shared.h"
#include "../include/backend.h"
#include "../include/frontend.h"
#include "../include/icon_parse.h"
/** 
* Main function to run ncurses TUI to show the tree
* @todo Add the folder to analize name on the args
*/
int main() {
    init_all();
    // @todo get the dir by arg and check if it exist
    Node *node = initNode("../../Algorithms", NULL, T_DIR);
    free_all();
    startTUI(node, false);    
}

