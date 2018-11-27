#include <stdlib.h>

#include "alg_ac.h"

void dispose_ac(struct ac_data *data) {
    if (data != NULL) {
        freeTrie(data->words);
        for (size_t n = 0; n < data->max_size; ++n) {
            freeTrie(data->sortie[n]);
        }
        free(data->sortie);
        free(data->suppl);
        free(data);
    }
}
