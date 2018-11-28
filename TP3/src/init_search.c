#include <stdlib.h>
#include <string.h>

#include "search_internals.h"

struct ac_data *init_search(const char *words[], int k) {
    struct ac_data *data;
    size_t size;

    data = malloc(sizeof(*data));

    /* l'arbre préfixe à forcément moins d'états que la somme des longueurs */
    size = 0;
    for (size_t i = 0; i < k; ++i) {
        size += strlen(words[i]);
    }
    data->max_size = size;

    data->words = createTrie(size);
    data->sortie = malloc(size * sizeof(*data->sortie));
    data->suppl = malloc(size * sizeof(*data->suppl));

    for (size_t i = 0; i < size; ++i)
        data->sortie[i] = NULL; 

    Trie singleton;
    int last;

    // insert every word and mark the last state
    for (size_t i = 0; i < k; ++i) {
        last = insertInTrie(data->words, words[i]);

        singleton = createTrie(size);
        insertInTrie(singleton, words[i]);
        data->sortie[last] = singleton;
    }

    // self transition on the initial state
    addSelfTrans(data->words);

    // generate the rest of sortie and suppl
    init_search_complete(data);

    return data;
}
