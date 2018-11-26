#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

#ifdef TRIE_USE_HACHAGE


/* --- HASH TABLE FUNCTIONS --- */

int hashKey(size_t maxNode, int startNode, char letter) {
    return ((startNode + letter) * 2654435761) % ((int) LOAD_FACTOR * maxNode);
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
    trie->transition = calloc((size_t) (LOAD_FACTOR * maxNode), sizeof(TransList));
    trie->finite = calloc(maxNode, sizeof(char));

    return trie;
}

int nextNode(Trie trie, int start, char letter) {
    int key = hashKey(trie->maxNode, start, letter);

    TransList list = findTrans(trie->transition[key], start, letter);

    return !hasNextTrans(list) ? list->targetNode : -1;
}

int nextNodeOrNew(Trie trie, int start, char letter) {
    int key = hashKey(trie->maxNode, start, letter);

    TransList list = findTrans(trie->transition[key], start, letter);

    if (!hasNextTrans(list)) {
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

void freeTrie(Trie trie) {
    if (trie != NULL) {
        for (size_t n = 0; n < trie->maxNode; ++n) {
            freeList(trie->transition[n]);
        }
        free(trie->transition);
        free(trie->finite);
        free(trie);
    }
}


#endif // TRIE_USE_HACHAGE
