#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

typedef struct ac_data *SearchSet;

SearchSet init_search(const char *words[], size_t length); 

void dispose_search(SearchSet search);

unsigned int search(const char *words[], size_t words_length, const char *text);

unsigned int search_r(const SearchSet search, const char *text);

#endif // SEARCH_H
