#include "search_internals.h"

unsigned int search_r(struct ac_data *data, const char *text) {
    unsigned int occ;
    int e;
    Trie s;

    occ = 0;
    e = 0;

    while (*text != '\0') {
        while (nextNode(data->words, e, (unsigned char) *text, NULL) == -1) {
            e = data->suppl[e];
        }
        e = nextNode(data->words, e, (unsigned char) *text, NULL);

        s = data->sortie[e];

        if (s != NULL) {
            // found occurrence
            occ += countTrie(s);
        }

        ++text;
    }

    return occ;
}
