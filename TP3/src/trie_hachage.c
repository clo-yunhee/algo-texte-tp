#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "trie.h"

#ifdef TRIE_USE_HACHAGE


/* --- HASH TABLE FUNCTIONS --- */

int hashKey(size_t capacity, int startNode, char letter) {
    return ((startNode + letter) * 2654435761) % capacity;
}

/* --- TRIE FUNCTIONS --- */

Trie createTrie(size_t maxNode) {
    Trie trie = malloc(sizeof(*trie));
    if (trie == NULL) {
        perror("createTrie");
        return NULL;
    }

    trie->maxNode = maxNode;
    trie->lastNode = 0;
    trie->capacity = (size_t) (LOAD_FACTOR * maxNode);
    trie->transition = malloc(trie->capacity * sizeof(TransList));
    trie->finite = malloc(maxNode * sizeof(char));

    for (size_t i = 0; i < trie->capacity; ++i)
        trie->transition[i] = NULL;
    for (size_t i = 0; i < maxNode; ++i)
        trie->finite[i] = 0;

    return trie;
}

int nextNode(Trie trie, int start, char letter) {
    int key = hashKey(trie->capacity, start, letter);

    TransList list = findTrans(trie->transition[key], start, letter);

    return hasNextTrans(list) ? list->targetNode : -1;
}

int nextNodeOrNew(Trie trie, int start, char letter) {
    int key = hashKey(trie->capacity, start, letter);

    TransList list = findTrans(trie->transition[key], start, letter);

    if (hasNextTrans(list)) {
        return list->targetNode;
    }
    
    // add the new node
    
    int targetNode = ++trie->lastNode; // new node number
    if (targetNode >= trie->maxNode) {
        fprintf(stderr, "Maximum number of nodes reached: %lu\n", trie->maxNode);
        return -1;
    }

    pushTrans(&trie->transition[key],
            start, targetNode, letter);

    return targetNode;
}

TransList nextNodes(Trie trie, int start) {
    TransList res, cur;

    res = NULL;

    for (size_t n = 0; n < trie->capacity; ++n) {
        cur = trie->transition[n];

        while (hasNextTrans(cur)) {
            if (cur->startNode == start && cur->targetNode != start) {
                pushTrans(&res, start, cur->targetNode, cur->letter);
            }

            nextTrans(&cur);
        }
    }
    
    return res;
}

void addSelfTrans(Trie trie) {
    TransList cur;
    int key;

    for (size_t c = 0; c < UCHAR_MAX; ++c) {
        key = hashKey(trie->capacity, 0, c);
        cur = findTrans(trie->transition[key], 0, c);

        if (cur == NULL) {
            pushTrans(&trie->transition[key], 0, 0, c);
        }
    }
}

void freeTrie(Trie trie) {
    if (trie != NULL) {
        for (size_t n = 0; n < trie->capacity; ++n) {
            freeList(trie->transition[n]);
        }
        free(trie->transition);
        free(trie->finite);
        free(trie);
    }
}


#endif // TRIE_USE_HACHAGE
