#include <stdlib.h>
#include <string.h>
#include "trie.h"

Trie buildPref(unsigned char *w) {
    size_t length;
    unsigned char *prefix;
    Trie result;

    length = strlen(w);
    prefix = malloc((length + 1) * sizeof(char));
    strncpy(prefix, w, sizeof(prefix));

    result = createTrie(length + 1);

    for (int i = length; i >= 0; --i) {
        prefix[i] = '\0';

        insertInTrie(result, prefix);
    }

    return result;
}
