#include <stdio.h>
#include <limits.h>

#include "alg_ac.h"

#include "queue.h"

void init_ac_complete(struct ac_data *data) {
    Queue f;
    TransList l;
    int e, r, p, s, sup_p;
    char a;
    
    e = 0;

    f = createQueue(UCHAR_MAX + 1); // max breadth

    l = nextNodes(data->words, e);
    while (hasNextTrans(l)) {
        p = l->targetNode;

        enqueue(f, p);
        data->suppl[p] = e;

        nextTrans(&l);
    }

    while (!isEmpty(f)) {
        r = dequeue(f);

        l = nextNodes(data->words, r);
        while (hasNextTrans(l)) {
            r = l->startNode;
            a = l->letter;            
            p = l->targetNode;
            
            enqueue(f, p);

            s = data->suppl[r];
            while (nextNode(data->words, s, a) == -1) {
                s = data->suppl[s];
            }

            sup_p = nextNode(data->words, s, a);

            data->suppl[p] = sup_p;

            mergeTries(&data->sortie[p], data->sortie[sup_p], data->max_size);

            nextTrans(&l);
        }
    }

}
