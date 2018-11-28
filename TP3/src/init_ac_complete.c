#include <stdio.h>
#include <limits.h>

#include "alg_ac.h"

#include "queue.h"

void init_ac_complete(struct ac_data *data) {
    Queue f;
    TransList l, it;
    int e, r, p, s, sup_p;
    unsigned char a;
    
    e = 0;

    f = createQueue(UCHAR_MAX + 1); // max breadth

    l = it = nextNodes(data->words, e);
    while (hasNextTrans(it)) {
        p = it->targetNode;

        enqueue(f, p);
        data->suppl[p] = e;

        nextTrans(&it);
    }
    freeList(l);

    while (!isEmpty(f)) {
        r = dequeue(f);

        l = it = nextNodes(data->words, r);
        while (hasNextTrans(it)) {
            r = it->startNode;
            a = it->letter;            
            p = it->targetNode;
            
            enqueue(f, p);

            s = data->suppl[r];
            while (nextNode(data->words, s, a, NULL) == -1) {
                s = data->suppl[s];
            }

            data->suppl[p] = sup_p = nextNode(data->words, s, a, NULL);            

            mergeTries(&data->sortie[p], data->sortie[sup_p], data->max_size);

            nextTrans(&it);
        }
        freeList(l);
    }

    freeQueue(f);

}
