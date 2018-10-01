#include <stdlib.h>
#include <stdio.h>
#include "trie.h"


int main(void) {
    /*Trie trie = createTrie(50);

    insertInTrie(trie, "actag");
    insertInTrie(trie, "ata");
    insertInTrie(trie, "cata");

    printf("actag: %d\n", isInTrie(trie, "actag"));
    printf("act: %d\n", isInTrie(trie, "act"));
    printf("ata: %d\n", isInTrie(trie, "ata"));
    printf("cata: %d\n", isInTrie(trie, "cata"));
    printf("gagaga: %d\n", isInTrie(trie, "gagaga"));
    printf(": %d\n", isInTrie(trie, ""));*/

    Trie trie = buildPref("abcd");
    
    printf("\n");

    return EXIT_SUCCESS;
}
