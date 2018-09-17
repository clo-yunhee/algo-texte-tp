#ifndef TRIE_H
#define TRIE_H


#define TRIE_USE_HACHAGE
//#define TRIE_USE_MATRICE


#include "trie_hachage.h"
#include "trie_matrice.h"

Trie createTrie(int maxNode);

void insertInTrie(Trie trie, unsigned char *w);

int isInTrie(Trie trie, unsigned char *w);

#endif // TRIE_H
