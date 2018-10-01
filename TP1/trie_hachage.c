#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

#ifdef TRIE_USE_HACHAGE



/* --- HASH TABLE FUNCTIONS --- */

int hashKey(int maxNode, int startNode, unsigned char letter) {
    return ((startNode + letter) * 2654435761) % maxNode;
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
    if (trie == NULL) {
        fprintf(stderr, "Trie is NULL.\n");
        return -1;
    }

    int key;
    List list, found;

    key = hashKey(trie->maxNode, startNode, letter);
    list = trie->transition[key];

    found = listFind(list, startNode, letter);
    if (found != NULL) {
        return found->targetNode; // it exists, don't do more.
    }

    // push the missing entry at the head of the list.

    List head = malloc(sizeof(struct _list));
    if (head == NULL) {
        perror("pushIfAbsent");
        return -1;
    }
    
    int targetNode = ++trie->nextNode; // new node number

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

/* --- TRIE FUNCTIONS --- */

Trie createTrie(int maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    if (trie == NULL) {
        perror("createTrie");
        return NULL;
    }

    trie->maxNode = maxNode;
    trie->nextNode = 0;
    trie->transition = calloc((size_t) (LOAD_FACTOR * maxNode), sizeof(List));
    trie->finite = calloc(maxNode, sizeof(char));

    return trie;
}

void insertInTrie(Trie trie, unsigned char *w) {
    int node = 0;

    // iterate to the end of the string
    while (w != NULL && *w != '\0') {
        node = pushIfAbsent(trie, node, *w);
        if (node == -1) {
            fprintf(stderr, "Could not insert in trie.\n");
            return;
        }

        ++w;
    }

    // end of string, the last node is a final state
    
    trie->finite[node] = 1;
}

int isInTrie(Trie trie, unsigned char *w) {
    int node, key;
    List list, found;

    node = 0;
    
    while (w != NULL && *w != '\0') {
        key = hashKey(trie->maxNode, node, *w);
        list = trie->transition[key];

        found = listFind(list, node, *w);
        if (found == NULL) {
            // no entry, return false
            return 0;
        }

        node = found->targetNode;

        ++w;
    }

    // if everything passed check if the last node is a terminal state.

    return trie->finite[node];
}

void printDepth(char buff[], int depth, Trie trie) {
    
    int node;

    List list;

}

void printTrie(Trie trie) {
    
    size_t length = (size_t) (LOAD_FACTOR * trie->maxNode);

    int node;
    List list;

    for (int k = 0; k < length; ++k) {
        
        

    }



    void allwords( char buff[], int depth, Trie trie) {
      buff[depth] = current char at this depth
      //    
      //      // recursive calls
      //        allwords(buff,depth+1,t->child);
      //         
      //           // print buff when you reach a leaf of some sort.
      //           }
}


#endif // TRIE_USE_HACHAGE
