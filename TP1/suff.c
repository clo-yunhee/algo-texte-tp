#include <string.h>
#include "trie.h"

Trie buildSuff(unsigned char *w) {
    size_t length;
    unsigned char *suffix;
    Trie result;

    length = strlen(w);
    result = createTrie(length + 1);

    for (int i = 0; i <= length; ++i) {
        insertInTrie(result, w + i);

        suffix++;
    }

    return result;
}
