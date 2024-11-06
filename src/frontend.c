#include <stdbool.h>
#include <stdio.h>
#include <ncurses.h>
#include <locale.h>

#include "../include/frontend.h"
#include "../include/shared.h"


void startTUI(Node *node) {
    
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

    initColors();
    use_default_colors();


    input_handler(node);
    // printNode(node, selected_dir);

    
    refresh();                          // Mostra l'output sullo schermo

    // Termina ncurses
    endwin();
}

void input_handler(Node *node) {
    Node *selected_dir = NULL;
    bool go_on = true;
    char pressed_key;

    printNode(node, selected_dir);
    do {
      pressed_key = getch();

      clear();

      switch (pressed_key) {
        case 'q':
          go_on = false;
          break;
          
        case 'k':
        case 3: //KEY_UP:
          selected_dir = getPrevious(selected_dir, node);
          printNode(node, selected_dir);
          break;
        
        case 'j':
        case 2: //KEY_DOWN:
          selected_dir = getNext(selected_dir, node);
          printNode(node, selected_dir);
          break;
        
        case 'h':
        case 4: //KEY_LEFT:
          selected_dir = getOuter(selected_dir, node);
          printNode(node, selected_dir);
          break;
        
        case 'l':
        case 5: //KEY_RIGHT:
          selected_dir = getInner(selected_dir, node);
          printNode(node, selected_dir);
          break;
        
        default:
          break;  
      }

      refresh();
      
    } while (go_on);
}

void printNode(Node *node, Node *selected_node) {
    
    if (node == selected_node) {
        // char str[sizeof(getFileName(node->name)) + 2 + STR_END];
        // snprintf(str, sizeof(str), "%s\n", getFileName(node->name));
        printw_selected(getFileName(node->name));
        printw("\n");
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
        // char str[sizeof(tabs) + sizeof(getFileName(node->name)) + 5 + STR_END];
        printw("%s%s── ", tabs, isLast ? "└" : "├");
        // snprintf(str, sizeof(str), "%s%s── %s\n", tabs, isLast ? "└" : "├", getFileName(node->name));
        printw_selected(getFileName(node->name));
        printw("\n");
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

void print_dirSymbol() {
  attron(A_REVERSE | A_BLINK);
  printw("+");
  attroff(A_REVERSE | A_BLINK);
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
  int default_bg = -1;

  // Definizione delle coppie di colori
  init_pair(DEFAULT,                  COLOR_WHITE,    default_bg  );
  init_pair(DIR_STATE_SYMBOL_COLOR,   default_bg,     COLOR_BLACK );      // Simboli di stato (+ o -)
  init_pair(DIR_COLOR,                COLOR_BLUE,     default_bg  );      // Directory generali (in grassetto)
  init_pair(FILE_COLOR,               COLOR_WHITE,    default_bg  );      // File generici
  init_pair(BIN_COLOR,                COLOR_GREEN,    default_bg  );      // File binari
  init_pair(OBJ_DIR_COLOR,            COLOR_RED,      default_bg  );      // Cartella obj
  init_pair(BIN_DIR_COLOR,            COLOR_GREEN,    default_bg  );      // Cartella bin
  init_pair(SRC_DIR_COLOR,            COLOR_CYAN,     default_bg  );      // Cartella src
  init_pair(INCLUDE_DIR_COLOR,        COLOR_MAGENTA,  default_bg  );      // Cartella include
  init_pair(C_FILE_COLOR,             COLOR_BLUE,     default_bg  );      // File .c
  init_pair(H_FILE_COLOR,             COLOR_MAGENTA,  default_bg  );      // File .h 
}

