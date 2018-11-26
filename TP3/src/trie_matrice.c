#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "trie.h"

#include <stdint.h>
#ifdef TRIE_USE_MATRICE


#define TRIE_TRANSITION(trie, n, c)  (trie->transition[n * (trie->maxNode) + (size_t) c])

/* --- TRIE FUNCTIONS --- */

Trie createTrie(size_t maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    if (trie == NULL) {
        perror("createTrie");
        return NULL;
    }

    trie->maxNode = maxNode;
    trie->lastNode = 0;

    trie->transition = malloc(maxNode * UCHAR_MAX * sizeof(int));
    trie->finite = malloc(maxNode * sizeof(char));
    
    for (size_t i = 0; i < maxNode * UCHAR_MAX; ++i)
        trie->transition[i] = -1;
    for (size_t i = 0; i < maxNode; ++i)
        trie->finite[i] = 0;

    return trie;
}

int nextNode(Trie trie, int start, char a) {
    return TRIE_TRANSITION(trie, start, a);
}

int nextNodeOrNew(Trie trie, int start, char a) {
    int next = nextNode(trie, start, a);
    if (next == -1) {
        next = trie->lastNode++;
        if (next >= trie->maxNode) {
            fprintf(stderr, "Maximum number of nodes reached: %d\n", trie->maxNode);
            return -1;
        }
        TRIE_TRANSITION(trie, start, a) = next;
    }
    return next;
}

TransList nextNodes(Trie trie, int start) {
    TransList res;
    int target;

    res = NULL;

    for (size_t c = 0; c < UCHAR_MAX; ++c) {
        target = TRIE_TRANSITION(trie, start, c);
        if (target != -1 && start != target) {
            pushTrans(&res, start, target, c);
        }
    }

    return res;
}

void addSelfTrans(Trie trie) {
    for (size_t c = 0; c < UCHAR_MAX; ++c) {
        if (TRIE_TRANSITION(trie, 0, c) == -1) {
            TRIE_TRANSITION(trie, 0, c) = 0;
        }
    }
}

void freeTrie(Trie trie) {
    if (trie != NULL) {  
        free(trie->transition);
        free(trie->finite);
        free(trie);
    }
}


#endif // TRIE_USE_MATRICE
