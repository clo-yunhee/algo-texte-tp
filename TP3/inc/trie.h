#ifndef TRIE_H
#define TRIE_H


//#define TRIE_USE_HACHAGE
#define TRIE_USE_MATRICE

#include <stddef.h>

#include "transition_list.h"

#include "trie_hachage.h"
#include "trie_matrice.h"


Trie createTrie(size_t maxNode);

int insertInTrie(Trie trie, const char *w);

int isInTrie(Trie trie, const char *w);

int nextNode(Trie trie, int start, char a);

int nextNodeOrNew(Trie trie, int start, char a);

TransList nextNodes(Trie trie, int start);

void addSelfTrans(Trie trie);

void mergeTries(Trie *dest, Trie src, size_t maxNode);

void freeTrie(Trie trie);

#endif // TRIE_H
