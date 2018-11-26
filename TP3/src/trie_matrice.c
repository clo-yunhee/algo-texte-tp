#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "trie.h"

#ifdef TRIE_USE_MATRICE



/* --- TRIE FUNCTIONS --- */

Trie createTrie(size_t maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    if (trie == NULL) {
        perror("createTrie");
        return NULL;
    }

    trie->maxNode = maxNode;
    trie->lastNode = 0;

    trie->transition = malloc(maxNode * sizeof(int *));
    for (size_t n = 0; n < maxNode; ++n) {
        trie->transition[n] = malloc(UCHAR_MAX * sizeof(int));
        for (size_t c = 0; c < UCHAR_MAX; ++c) {
            trie->transition[n][c] = -1;
        }
    }

    trie->finite = calloc(maxNode, sizeof(char));

    return trie;
}

int nextNode(Trie trie, int start, char a) {
    return trie->transition[start][(unsigned) a];
}

int nextNodeOrNew(Trie trie, int start, char a) {
    int next = nextNode(trie, start, a);
    if (next == -1) {
        next = trie->lastNode++;
        if (next >= trie->maxNode) {
            fprintf(stderr, "Maximum number of nodes reached: %d\n", trie->maxNode);
            return -1;
        }
        trie->transition[start][(size_t) a] = next;
    }
    return next;
}

void freeTrie(Trie trie) {
    if (trie == NULL) {  
        for (size_t n = 0; n < trie->maxNode; ++n)
            free(trie->transition[n]);
        free(trie->transition);
        free(trie->finite);
        free(trie);
    }
}

TransList nextNodes(Trie trie, int start) {
    TransList res;
    int target;

    res = NULL;

    for (size_t c = 0; c < UCHAR_MAX; ++c) {
        target = trie->transition[start][c];
        if (target != -1) {
            pushRes(&res, start, c, target);
        }
    }

    return res;
}

#endif // TRIE_USE_MATRICE
