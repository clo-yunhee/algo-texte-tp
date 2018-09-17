#include <stdlib.h>
#include <stdio.h>
#include "trie.h"


int main(void) {
    Trie trie = createTrie(10);

    insertInTrie(trie, "actag");
    //insertInTrie(trie, "ata");
    //insertInTrie(trie, "cata");

    printf("actag: %d", isInTrie(trie, "actag"));
    
    printf("\n");
    return EXIT_SUCCESS;
}
