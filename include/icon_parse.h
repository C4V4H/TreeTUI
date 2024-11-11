#ifndef ICON_PARSE_H_fiojnewiojdfweoifcjewoiw
#define ICON_PARSE_H_fiojnewiojdfweoifcjewoiw

#include "shared.h"
#include <wchar.h>
#include "uthash.h"


#define DEFAULT_DIR_ICON L'\U0001f4c2'
#define DEFAULT_FILE_ICON L'\U0001f4c4'
#define DEFAULT_EXE_ICON L'\U0001f3d7'
#define DIR_LINK_ICON L'\U0001f5c2'
#define FILE_LINK_ICON L'\U0001f516'


typedef struct {
    char *key;
    wchar_t icon;
    UT_hash_handle hh;
} HashMapElement;

HashMapElement* icons_by_extension  = NULL;
HashMapElement* icons_by_name       = NULL;


void init_icon_by_extension_map();
void init_icon_by_name_map();

void add_icon(HashMapElement[], char[], wchar_t);
void free_icon_map(HashMapElement[]);
wchar_t get_icon(HashMapElement[], char[]);

void init_all();
void free_all();

wchar_t get_icon_for_path(Node*);

#endif
