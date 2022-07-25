#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ALPHABET_SIZE (26)

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];       //making pointer array of size 26 
    int isLeaf;     // If isLeaf is 1 then end of word is true and if not then it is false
};
struct TrieNode *getNode(void);
void insert(struct TrieNode *root, const char *key) ;
bool search(struct TrieNode *root, const char *key) ;
void autocorrect_swap(struct TrieNode *root,char word[100]);
void autocorrect_repeat(struct TrieNode *root,char word[100]) ;
void autocorrect_letter(struct TrieNode *root,char word[100]);
void autocorrect_hiddenletter(struct TrieNode *root,char word[100]);
