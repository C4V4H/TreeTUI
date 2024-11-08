#include <alloca.h>
#include <stdbool.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>
#include <string.h>

#include "../include/frontend.h"
#include "../include/shared.h"

#define SELECTED 10

void startTUI(Node *node, bool all) {
    
    setlocale(LC_ALL, "");
    // Inizializzazione di ncurses
    initscr();            // Avvia la modalità ncurses
    keypad(stdscr, TRUE);
    cbreak();             // Disabilita il buffering della linea
    noecho();             // Non mostra i caratteri premuti

    curs_set(FALSE);      // boh

    // Inizializza i colori
    if (has_colors() == FALSE) {
        endwin();  // Termina ncurses se il terminale non supporta i colori
        printf("Il terminale non supporta i colori\n");
        return;
    }
    start_color();  // Abilita l'uso dei colori

    use_default_colors();
    
    initColors();

    input_handler(node, all);

    
    refresh();                          // Mostra l'output sullo schermo

    // Termina ncurses
    endwin();
}

void input_handler(Node *node, bool all) {
    Node *selected_dir = NULL;
    bool go_on = true, something_changed = true;
    char pressed_key;

    printNode(node, selected_dir, all);
    do {
      pressed_key = getch();

      if (something_changed)
        clear();
      
      something_changed = true;
      
      switch (pressed_key) {
        case 'q':
          go_on = false;
          break;
          
        case 'k':
        case 3: //KEY_UP:
          selected_dir = getPrevious(selected_dir, node);
          printNode(node, selected_dir, all);
          break;
        
        case 'j':
        case 2: //KEY_DOWN:
          selected_dir = getNext(selected_dir, node);
          printNode(node, selected_dir, all);
          break;
        
        case 'h':
        case 4: //KEY_LEFT:
          selected_dir = getOuter(selected_dir, node);
          printNode(node, selected_dir, all);
          break;
        
        case 'l':
        case 5: //KEY_RIGHT:
          selected_dir = getInner(selected_dir, node);
          printNode(node, selected_dir, all);
          break;

        case 10:
          toggle_dir(selected_dir);
          printNode(node, selected_dir, all);
          break;
          
        default:
          something_changed = false;
          break;  
      }

      refresh();
      
    } while (go_on);
}

void printNode(Node *node, Node *selected_node, bool all) {
   
    print_colored(node->type, true, (node==selected_node), "%s\n", getFileName(node->name));
    
    refresh();
    
    for (int i = 0; i < node->num_children; i++) {
        printChilds(node->children[i], selected_node, "", i == node->num_children-1, all);
    }
}

void printChilds(Node *node, Node *selected_node, char *tabs, bool isLast, bool all) {
    const char *toAdd = isLast ? "       " : "│      ";
    
    if (node->type == T_HIDDEN_DIR && !all) return;

    bool is_dir = node->type == T_DIR || node->type == T_HIDDEN_DIR;

    print_colored(
                  TABS_COLOR, false, false,
                  "%s%s── ", tabs, isLast ? "└" : "├"
                );
    
    if (is_dir) {
      print_colored(
                    DEFAULT, false, false, 
                    "%s", node->is_expanded ? " ▼ " : " ▶ "
                   );
    }
    
    print_colored(
                  node->type, is_dir, (node == selected_node), 
                  "%s\n", getFileName(node->name)
                );
   
    refresh();
    
    char new_tabs[255];
    snprintf(new_tabs, sizeof(new_tabs), "%s%s", tabs, toAdd);

    if (node->is_expanded == 1) {
      for (int i = 0; i < node->num_children; i++) {
          printChilds(node->children[i], selected_node, new_tabs, i == node->num_children-1, all);
      }
    }
}

void toggle_dir(Node *node) {
  node->is_expanded = node->is_expanded == 0 ? 1 : 0; 
}



Node* getNext(Node *node, Node *origin) {
  if (node == NULL) 
    return origin;

  if (node->father == NULL)
    return node;

  Node **children = node->father->children;
  int index = 0;
  
  for (int i = 0; i < node->father->num_children; i++) {
    if (node == children[i])
      index = i;
  } 

    return (index + 1 < node->father->num_children) ? children[index + 1] : children[0];
}

Node* getPrevious(Node *node, Node *origin) {
  if (node == NULL) 
    return origin;

  if (node->father == NULL)
    return node;

  Node **children = node->father->children; 
  int index = 0;
  
  for (int i = 0; i < node->father->num_children; i++) {
    if (node == children[i])
      index = i;
  } 
  
  return (index > 0) ? children[index - 1] : children[node->father->num_children - 1];
  
}

Node* getInner(Node *node, Node *origin) {
  if (node == NULL)
    return origin;

  if (node->children == NULL) 
    return node;

  if (node->is_expanded == 0)
    node->is_expanded = 1;

  return node->children[0];
}

Node* getOuter(Node *node, Node *origin) {
  if (node == NULL) 
    return origin;

  if (node->father == NULL)
    return node;

  return node->father;
}


void print_colored(int color, bool bold, bool underlined, const char *format, ...) {
    attron(COLOR_PAIR(color));
    if (bold)       attron(A_BOLD);
    if (underlined) attron(A_UNDERLINE);

    // Gestione degli argomenti variabili
    va_list args;
    va_start(args, format);
    vw_printw(stdscr, format, args); // vw_printw funziona come vprintf, ma con ncurses
    va_end(args);

    if (bold)       attroff(A_BOLD);
    if (underlined) attroff(A_UNDERLINE);
    attroff(COLOR_PAIR(color));
}


void initColors() {
  int default_bg = -1;
  
  init_pair(SELECTED,                 -1,             COLOR_WHITE );
  init_pair(DEFAULT,                  COLOR_WHITE,    default_bg  );
  init_pair(T_DIR,                    COLOR_BLUE,     default_bg  );      // Directory generali (in grassetto)
  init_pair(T_HIDDEN_DIR,             COLOR_BLUE,     default_bg  );      // Directory generali (in grassetto)
  init_pair(T_FILE,                   COLOR_WHITE,    default_bg  );      // File generici
  init_pair(T_BIN,                    COLOR_GREEN,    default_bg  );      // File binari
  init_pair(TABS_COLOR,               COLOR_BLACK,    default_bg  );
}

