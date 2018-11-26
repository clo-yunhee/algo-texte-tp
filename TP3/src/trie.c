#include <stdlib.h>
#include <stdio.h>

#include "trie.h"

int insertInTrie(Trie trie, const char *w) {
    int node = 0;

    // iterate on the string from start to finish
    while (w != NULL && *w != '\0') {
        node = nextNodeOrNew(trie, node, *w);

        ++w;
    }

    // end of string, last node is final state
    trie->finite[node] = 1;

    return node;
}

int isInTrie(Trie trie, const char *w) {
    int node = 0;

    while (w != NULL && *w != '\0') {
        node = nextNode(trie, node, *w);
        if (node == -1) {
            return 0; // isn't in the set
        }
    }

    return trie->finite[node];
}
