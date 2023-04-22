#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    struct Trie* children[ALPHABET_SIZE];
};

void insert(struct Trie** ppTrie, char* word) {
    struct Trie* pTrie = *ppTrie;
    if (pTrie == NULL) {
        pTrie = (struct Trie*)malloc(sizeof(struct Trie));
        pTrie->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            pTrie->children[i] = NULL;
        *ppTrie = pTrie;
    }
    if (*word != '\0')
        insert(&pTrie->children[*word - 'a'], word + 1);
    else
        pTrie->count++;
}

int numberOfOccurances(struct Trie* pTrie, char* word) {
    if (pTrie == NULL)
        return 0;
    if (*word != '\0')
        return numberOfOccurances(pTrie->children[*word - 'a'], word + 1);
    else
        return pTrie->count;
}

struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        deallocateTrie(pTrie->children[i]);
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie* trie = NULL;
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int len = sizeof(pWords) / sizeof(pWords[0]);
    for (int i = 0; i < len; i++) {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < len; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
