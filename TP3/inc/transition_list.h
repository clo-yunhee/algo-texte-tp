#ifndef TRANS_LIST_H
#define TRANS_LIST_H


struct _tr_list {
    int startNode,          // état de départ
        targetNode;         // état d'arrivée
    char letter;            // étiquette de la transition
    struct _tr_list *next;  // chaine suivante, ou NULL
};

typedef struct _tr_list * TransList;


#define EMPTY_LIST (NULL)

void pushTrans(TransList *listptr, int startNode, int targetNode, char letter);

void nextTrans(TransList *listptr);

int hasNextTrans(TransList list);

TransList findTrans(TransList list, int startNode, char letter);

void freeList(TransList list);

#endif // TRANS_LIST_H
