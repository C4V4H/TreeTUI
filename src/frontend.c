#include <alloca.h>
#include <stdbool.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

#include "../include/frontend.h"
#include "../include/shared.h"


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
    // printNode(node, selected_dir);

    
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

      //printf("%d: %c", pressed_key, pressed_key);
      
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
          // printNode(node, selected_dir, all);
          break;  
      }

      refresh();
      
    } while (go_on);
}

void printNode(Node *node, Node *selected_node, bool all) {
    
    if (node == selected_node) {
        // char str[sizeof(getFileName(node->name)) + 2 + STR_END];
        // snprintf(str, sizeof(str), "%s\n", getFileName(node->name));
        printw_selected(getFileName(node->name), node->type);
        printw("\n");
    } 
    else 
        printw("%s\n", getFileName(node->name));
    
    refresh();
    
    for (int i = 0; i < node->num_children; i++) {
        printChilds(node->children[i], selected_node, "", i == node->num_children-1, all);
    }
}

void printChilds(Node *node, Node *selected_node, char *tabs, bool isLast, bool all) {
    const char *toAdd = isLast ? "       " : "│      ";
    
    if (node->type == T_HIDDEN_DIR && !all) return;

    bool is_dir = node->type == T_DIR;
    
    if (node == selected_node) {
      char str[sizeof(getFileName(node->name)) + 5 + STR_END];
      printw("%s%s── ", tabs, isLast ? "└" : "├");
      snprintf(str, sizeof(str), "%s%s", is_dir ? (node->is_expanded ? " ▼ " : " ▶ ") : "", getFileName(node->name));
      printw_selected(str, node->type);
      printw("\n");
    } 
    else {
      // printw("%s%s── ", tabs, isLast ? "└" : "├");
      // if (node->type == T_DIR) print_dir_sym(node->is_expanded);
      printw("%s%s── %s", 
             tabs, 
             isLast ? "└" : "├", 
             is_dir ? (node->is_expanded ? " ▼ " : " ▶ ") : ""//, 
             // getFileName(node->name)
           );
      printColored(node->type, getFileName(node->name), is_dir, false);
      printw("\n");
    }
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

void print_dir_sym(bool opened) {
  printColored(DEFAULT, opened ? "▼" : "▶", true, false);
  // printw(opened ? "+" : "-");
  printw(" ");
  // attroff(A_REVERSE | A_BLINK);
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
  // int index = (int)(node - children[0]); // Calcola l'indice di node
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
  // int index = (int)(node - children[0]); // Calcola l'indice di node
  return (index > 0) ? children[index - 1] : children[node->father->num_children - 1];
}

Node* getInner(Node *node, Node *origin) {
  if (node == NULL)
    return origin;

  if (node->children == NULL) 
    return node;

  return node->children[0];
}

Node* getOuter(Node *node, Node *origin) {
  if (node == NULL) 
    return origin;

  if (node->father == NULL)
    return node;

  return node->father;
}

/**
* @todo make it blink
*/
void printw_selected(char *str, int type) {
    // int len = strlen(str);
    // attron(A_REVERSE);
    // attron(A_BLINK);
    // printw(str);
    // attron(A_BLINK);
    // attroff(A_REVERSE);
    printColored(type + 100, str, true, false);
}




void printColored(short color, char str[], bool bold, bool reverse) {

  attron(COLOR_PAIR(color));
  if (bold   )  attron(A_BOLD);
  if (reverse)  attron(A_REVERSE);
  
  printw(str);
  
  if (bold   )  attroff(A_BOLD);
  if (reverse)  attroff(A_REVERSE);
  attroff(COLOR_PAIR(color));
}


void initColors() {
  int default_bg = -1, offset = 0;

  for (int i = 0; i<2; i++) {
    if (i != 0) {
      default_bg = COLOR_BLACK;
      offset = 100;
    }
      
    // attroff(A_DIM);
    // Definizione delle coppie di colori
    init_pair(offset + DEFAULT,                  COLOR_WHITE,    default_bg  );
    // init_pair(offset + DIR_STATE_SYMBOL_COLOR,   default_bg,     COLOR_BLACK );      // Simboli di stato (+ o -)
    init_pair(offset + T_DIR,                    COLOR_BLUE,     default_bg  );      // Directory generali (in grassetto)
    init_pair(offset + T_HIDDEN_DIR,             COLOR_BLUE,     default_bg  );      // Directory generali (in grassetto)
    init_pair(offset + T_FILE,                   COLOR_WHITE,    default_bg  );      // File generici
    init_pair(offset + T_BIN,                    COLOR_GREEN,    default_bg  );      // File binari
    // init_pair(1, COLOR_WHITE, -1);
    // init_pair(offset + OBJ_DIR_COLOR,            COLOR_RED,      default_bg  );      // Cartella obj
    // init_pair(offset + BIN_DIR_COLOR,            COLOR_GREEN,    default_bg  );      // Cartella bin
    // init_pair(offset + SRC_DIR_COLOR,            COLOR_CYAN,     default_bg  );      // Cartella src
    // init_pair(offset + INCLUDE_DIR_COLOR,        COLOR_MAGENTA,  default_bg  );      // Cartella include
    // init_pair(offset + C_FILE_COLOR,             COLOR_BLUE,     default_bg  );      // File .c
    // init_pair(offset + H_FILE_COLOR,             COLOR_MAGENTA,  default_bg  );      // File .h 
  }
}

