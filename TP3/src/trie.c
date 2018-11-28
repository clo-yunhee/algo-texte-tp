#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "trie.h"

int insertInTrie(Trie trie, const char *w) {
    int node = 0;

    // iterate on the string from start to finish
    while (w != NULL && *w != '\0') {
        node = nextNodeOrNew(trie, node, (unsigned char) *w);

        ++w;
    }

    // end of string, last node is final state
    trie->finite[node] = 1;

    return node;
}

int isInTrie(Trie trie, const char *w) {
    int node = 0;

    while (w != NULL && *w != '\0') {
        node = nextNode(trie, node, (unsigned char) *w);
        if (node == -1) {
            return 0; // isn't in the set
        }
        ++w;
    }

    return trie->finite[node];
}

void mergeTriesFrom(Trie dest, int destStart, Trie src, int srcStart) {
    int destTarget, srcTarget;

    for (size_t c = 0; c < UCHAR_MAX; ++c) {
        srcTarget = nextNode(src, srcStart, c);
        if (srcTarget != -1 && srcStart != srcTarget) {
            destTarget = nextNodeOrNew(dest, destStart, c);
            mergeTriesFrom(dest, destTarget, src, srcTarget); 
        }
    }
}

void mergeTries(Trie *dest, Trie src, size_t maxNode) {
    if (src == NULL) { // if there's nothing to merge, do nothing
        return;
    }
    if (*dest == NULL) { // if the destination is empty, create a trie
        *dest = createTrie(maxNode);
    }

    mergeTriesFrom(*dest, 0, src, 0);
}


