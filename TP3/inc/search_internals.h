#ifndef ALG_AC_H
#define ALG_AC_H


#include "trie.h"

struct ac_data {
    Trie words;
    size_t word_count;

    size_t max_size;

    Trie *sortie;
    int *suppl;
};

void init_search_complete(struct ac_data *data);

#endif // ALG_AC_H
