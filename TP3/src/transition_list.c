#include <stdlib.h>

#include "transition_list.h"

void pushTrans(TransList *listptr, int startNode, int targetNode, char letter) {
    if (listptr == NULL) return;

    TransList head = malloc(sizeof(*head));

    head->startNode = startNode;
    head->targetNode = targetNode;
    head->letter = letter;
    head->next = *listptr;

    *listptr = head;
}

void nextTrans(TransList *listptr) {
    if (listptr == NULL
            || *listptr == NULL) return;

    *listptr = (*listptr)->next;
}

int hasNextTrans(TransList list) {
    return list != NULL;
}

TransList findTrans(TransList list, int startNode, char letter) {
    while (hasNextTrans(list)) {
        if (list->startNode == startNode
                && list->letter == letter) {
            return list;
        }

        nextTrans(&list);
    }

    return NULL;
}

void freeList(TransList list) {
    if (list != NULL) {
        freeList(list->next);
        free(list);
    }
}
