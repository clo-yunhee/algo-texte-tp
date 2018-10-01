#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "trie.h"

#ifdef TRIE_USE_MATRICE




/* --- TRIE FUNCTIONS --- */

Trie createTrie(int maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    if (trie == NULL) {
        perror("createTrie");
        return NULL;
    }

    trie->maxNode = maxNode;
    trie->nextNode = 0;

    trie->transition = malloc(maxNode * sizeof(int *));
    for (int n = 0; n < maxNode; ++n) {
        trie->transition[n] = malloc(UCHAR_MAX * sizeof(int));
        for (int c = 0; c < UCHAR_MAX; ++c) {
            trie->transition[n][c] = -1;
        }
    }

    trie->finite = calloc(maxNode, sizeof(char));

    return trie;
}

void insertInTrie(Trie trie, unsigned char *w) {
    int node, next;

    node = 0;

    while (w != NULL && *w != '\0') {
        next = trie->transition[node][*w];

        if (next == -1) {
            // no transition, have to add one.
            next = trie->nextNode++;
            if (next >= trie->maxNode) {
                fprintf(stderr, "Maximum number of nodes reached: %d\n", trie->maxNode);
                return;
            }
            
            trie->transition[node][*w] = next;
        }

        node = next;

        ++w;
    }

    trie->finite[node] = 1;
}

int isInTrie(Trie trie, unsigned char *w) {
    int node;
    
    node = 0;

    while (w != NULL && *w != '\0') {
        node = trie->transition[node][*w];
        if (node == -1) {
            return 0;
        }
        ++w;
    }

    return trie->finite[node];
}


#endif // TRIE_USE_MATRICE
