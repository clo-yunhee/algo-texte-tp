#include "search.h"
#include "search_internals.h"

unsigned int search(const char *words[], size_t words_length, const char *text) {

    struct ac_data *data;
    unsigned int occ;
    
    data = init_search(words, words_length);

    occ = search_r(data, text);

    dispose_search(data);

    return occ;
}
