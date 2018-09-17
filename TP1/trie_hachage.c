#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

#ifdef TRIE_USE_HACHAGE


/* --- HASH TABLE FUNCTIONS --- */

int hashKey(int maxNode, int startNode, unsigned char letter) {
    return ((startNote + letter) * 2654435761) % (maxNode + 1);
}

List listFind(List list, int startNode, unsigned char letter) {
    while (list != NULL) {
        if (list->startNode == startNode
                && list->letter == letter) {
            return list;
        }

        list = list->next;
    }

    return NULL;
}

int pushIfAbsent(Trie trie, int startNode, unsigned char letter) {
    if (trie == NULL) return -1;

    int key;
    List list, found;

    key = hashKey(trie->maxNode, startNode, letter);
    list = trie->transition[key];

    found = listFind(list, startNode, letter);
    if (found != NULL) {
        return found->endNode; // it exists, don't do more.
    }

    // push the missing entry at the head of the list.

    List head = malloc(sizeof(struct _list));
    if (head == NULL) {
        perror("pushIfAbsent");
        return -1;
    }
    
    int endNode = ++trie->nextNode; // new node number

    head->startNode = startNode;
    head->endNode = endNode;
    head->letter = letter;
    head->next = list;
    
    trie->transition[key] = head;

    return endNode;
}

/* --- TRIE FUNCTIONS --- */

Trie createTrie(int maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    if (trie == NULL) {
        perror("createTrie");
        return NULL;
    }

    trie->maxNode = maxNode;
    trie->nextNode = 0;
    trie->transition = calloc(maxNode, sizeof(List));
    trie->finite = calloc(maxNode, sizeof(char));

    return trie;
}

void insertInTrie(Trie trie, unsigned char *w) {

    int node = 0;

    // iterate to the end of the string
    while (w != NULL && *w != '\0') {
        node = pushIfAbsent(trie, node, *w);

        ++w;
    }

    // end of string, the last node is a final state
    
    trie->finite[node] = 1;
}

int isInTrie(Trie trie, unsigned char *w) {
    int node, key;
    List list, found;

    node = 0;
    key = hashKey(trie->maxNode, 0, *w);
    // repeat pushIfAbsent but with tests only
}


#endif // TRIE_USE_HACHAGE
