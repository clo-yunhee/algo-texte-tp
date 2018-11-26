#include <stdlib.h>
#include <string.h>

#include "alg_ac.h"

struct ac_data *init_ac(const char *words[], int k) {
    struct ac_data *data;
    size_t size;

    data = malloc(sizeof(*data));

    /* l'arbre préfixe à forcément moins d'états que la somme des longueurs */
    size = 0;
    for (size_t i = 0; i < k; ++i) {
        size += strlen(words[i]);    
    }
    data->max_size = size;

    data->words = createTrie(data->max_size);
    data->sortie = calloc(data->max_size, sizeof(*data->sortie));
    data->suppl = malloc(data->max_size * sizeof(*data->suppl));

    Trie singleton;

    // insert every word and mark the last state
    for (size_t i = 0; i < k; ++i) {
        insertInTrie(data->words, words[i]);

        singleton = createTrie(data->max_size);
        insertInTrie(singleton, words[i]);
        data->sortie[data->words->lastNode] = singleton;
    }

    // generate the rest of sortie and suppl
    init_ac_complete(data);

    return 0;
}
