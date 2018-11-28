#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "trie.h"

#include <stdint.h>
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
    trie->finite = malloc(maxNode * sizeof(char));
    
    for (size_t i = 0; i < maxNode; ++i) {
        trie->finite[i] = 0;
        trie->transition[i] = malloc(UCHAR_MAX * sizeof(int));
        for (size_t c = 0; c < UCHAR_MAX; ++c) {
            trie->transition[i][c] = -1;
        }
    }

    return trie;
}

int nextNode(Trie trie, int start, unsigned char a) {
    return trie->transition[start][a];
}

int nextNodeOrNew(Trie trie, int start, unsigned char a, char finite) {
    int next = nextNode(trie, start, a);
    if (next == -1) {
        next = ++trie->lastNode;
        if (next >= trie->maxNode) {
            fprintf(stderr, "Maximum number of nodes reached: %d\n", trie->maxNode);
            return -1;
        }
        trie->transition[start][a] = next;
    }
    if (finite) {
        trie->finite[next] = 1;
    }
    return next;
}

TransList nextNodes(Trie trie, int start) {
    TransList res;
    int target;

    res = NULL;

    for (size_t c = 0; c < UCHAR_MAX; ++c) {
        target = trie->transition[start][c];
        if (target != -1 && start != target) {
            pushTrans(&res, start, target, c);
        }
    }

    return res;
}

void addSelfTrans(Trie trie) {
    for (size_t c = 0; c < UCHAR_MAX; ++c) {
        if (trie->transition[0][c] == -1) {
            trie->transition[0][c] = 0;
        }
    }
}

void freeTrie(Trie trie) {
    if (trie != NULL) {  
        for (size_t n = 0; n < trie->maxNode; ++n) {
            free(trie->transition[n]);
        }
        free(trie->transition);
        free(trie->finite);
        free(trie);
    }
}


#endif // TRIE_USE_MATRICE
