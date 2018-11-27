#include "alg_ac.h"

#include <stdio.h>

unsigned int count_occ_ac(struct ac_data *data, const char *text) {
    unsigned int occ;
    int e;

    occ = 0;
    e = 0;

    while (*text != '\0') {
        while (nextNode(data->words, e, *text) == -1) {
            e = data->suppl[e];
        }
        e = nextNode(data->words, e, *text);

        if (data->sortie[e] != NULL) {
            // found occurrence
            occ++;
        }

        ++text;
    }

    return occ;
}
