#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

#ifdef TRIE_USE_HACHAGE



/* --- HASH TABLE FUNCTIONS --- */

int hashKey(size_t maxNode, int startNode, unsigned char letter) {
    return ((startNode + letter) * 2654435761) % maxNode;
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
    trie->transition = calloc((size_t) (LOAD_FACTOR * maxNode), sizeof(List));
    trie->finite = calloc(maxNode, sizeof(char));

    return trie;
}

int nextNode(Trie trie, int start, unsigned char a) {
    int key = hashKey(trie->maxNode, start, a);

    List list = trie->transition[key];

    while (list != NULL) {
        if (list->startNode == startNode
                && list->letter == letter) {
            break;
        }

        list = list->next;
    }

    return list != NULL ? list->targetNode : -1;
}

int nextNodeOrNew(Trie trie, int start, unsigned char a) {
    int key = hashKey(trie->maxNode, start, a);

    List list = trie->transition[key];

    while (list != NULL) {
        if (list->startNode == startNode
                && list->letter == letter) {
            break;
        }

        list = list->next;
    }

    if (list != NULL) {
        return list->targetNode;
    }
    
    // add the new node
    
    List head = malloc(sizeof(*head));
    if (head == NULL) {
        perror("Couldn't allocate new node");
        return -1;
    }
    
    int targetNode = ++trie->lastNode; // new node number

    if (targetNode >= trie->maxNode) {
        fprintf(stderr, "Maximum number of nodes reached: %d\n", trie->maxNode);
        return -1;
    }

    head->startNode = startNode;
    head->targetNode = targetNode;
    head->letter = letter;
    head->next = list;
    
    trie->transition[key] = head;

    return targetNode;
}

void freeList(List list) {
    if (list != NULL) {
        freeList(list->next);
        free(list);
    }
}

void freeTrie(Trie trie) {
    if (trie != NULL) {
        freeList(trie->transition);
        free(trie->finite);
        free(trie);
    }
}


#endif // TRIE_USE_HACHAGE
