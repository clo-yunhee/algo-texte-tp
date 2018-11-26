#ifndef ALG_AC_H
#define ALG_AC_H

#include <stddef.h>

#include "trie.h"


struct ac_data {
    Trie words;
    size_t word_count;

    size_t max_size;

    Trie *sortie;
    int *suppl;
};


struct ac_data *init_ac(const char *words[], int k);

void init_ac_complete(struct ac_data *data);

unsigned int count_occ_ac(struct ac_data *data, const char *text);

void dispose_ac(struct ac_data *data);

#endif // ALG_AC_H
