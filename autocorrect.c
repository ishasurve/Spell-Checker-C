
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include"autocorrect.h"

 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 

 
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
 
// Making structure of TRIE node
#define ALPHABET_SIZE (26)

// Returns new TRIE node (initialized to NULL)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;      //initialize pNode
 
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));     //Dynamic memory allocation for pNode
 
    if (pNode)      //If pNode is not equal to NULL 
    {
        int i;
 
        pNode->isLeaf = 0;      //Making leaf as 0
 
        for (i = 0; i < ALPHABET_SIZE; i++)     //To make new node
            pNode->children[i] = NULL;
    }
 
    return pNode;       //returning pNode
}
 
int count=0;
// If word not present, inserts key into TRIE
// If the key is prefix of TRIE node, just marks leaf node 
void insert(struct TrieNode *root, const char *key)         //This function is for inserting words in TRIE tree
{
    //initialization of variables
    int level;
    int index;
    int length;
    struct TrieNode *curr = root;

    length  = strlen(key);         //Finding length of the word
    
    for (level = 0; level < length; level++)        
    {
        index = CHAR_TO_INDEX(key[level]);          //To find index of every character 
        if (!curr->children[index])
            curr->children[index] = getNode();          //calling getNode function for creating new node
 
        curr = curr->children[index];           //Traverse to the children
    }
    
    // mark last node as leaf
    curr->isLeaf = 1;       //is leaf is 1 means that spelling is complete there
}
 
// Returns true if key presents in TRIE tree, else false
bool search(struct TrieNode *root, const char *key)         //Searching word in TRIE tree
{
    //initialization of variables
    int level;
    int length ;
    int index;
    struct TrieNode *curr = root;
    
    length = strlen(key);       //Finding length of the word

    for (level = 0; level < length; level++)         
    {
        index = CHAR_TO_INDEX(key[level]);          //To find index of every character
        if (!curr->children[index])                 
            return false;
 
        curr = curr->children[index];               //Traverse to the children
    }
 
    return (curr != NULL && curr->isLeaf);          //returning word to the user (basically means the word which you were finding is present in TRIE)
}

/*From here we make logic of AUTO correction of words*/

/*Function correct the word 'aplpe' to 'apple' basically it means swap the character in the word*/
void autocorrect_swap(struct TrieNode *root,char word[100])         //Swapping of character in word 
{
    //initialization of variables
    int length_word,i,j,k;
    char temp,original[100];
    
    length_word=strlen(word);       //find length of the word which user enter (This length will need for finding similar size of word)
    
    for(i=0;i<length_word;i++)      //converting word to original array
        original[i]=word[i];
    
    for(i=0;i<length_word;i++)    
    {
        for(j=i+1;j<length_word;j++)       
        {
            /*swapping logic*/
            temp=word[i];
            word[i]=word[j];
            word[j]=temp;
            if(search(root, word)==1)           //calling search function if the function returns 1 means the word is correct
            {
                printf("Do you mean %s ?\n",word);  
                count++;
            }
            for(k=0;k<length_word;k++)      //now again to make our old word which user entered we need to have to transfer original array to word array
                word[k]=original[k];
        }
    }
}

/*Function correct the word by character which are repeat it self in that word . if we enter 'aray' it will give output 'array'*/
void autocorrect_repeat(struct TrieNode *root,char word[100])           //adding repeat character in word
{
    //initialization of variables and array
    int i,j,cn=0,length_word;
    char new[101],new1[101];
    
    length_word=strlen(word);           //finding length of word which user entered
    
    while(cn<length_word)         
    {
        i=0;

        while(i<=cn)            //for copying every character of word to new 
        {
            new[i]=word[i];
            i++;
        }
        /*logic for entering every character to word at once*/
        for(j=i-1;i<=length_word;i++,j++)       
        {
            new[i]=word[j];
        }
        for(i=0;i<=length_word;i++)
        {
            new1[i]=new[i];
        }
        new1[length_word+1]=0;      
        if(search(root, new1)==1)           //calling search function if the function returns 1 means the word is correct
        {    
            printf("Do you mean %s ?\n",new1);
            count++;
        }
        cn++;           
    }
}

/*auto correction of character which is not correct in our word e.g. if user enters realise then it will suggest realize */
void autocorrect_letter(struct TrieNode *root,char word[100])           //correct the character which is not correct in the word
{
    //initialization of variables and array
    int i=0,length_word,j,cn=0;
    char c;
    char new2[100];

    length_word=strlen(word);           //finding length of word which user entered
    
    while(cn<length_word)           
    {
            j=0;
            while(j<26)         //while loop will change value of every character to a to z 
            {
                i=0;
                while(i<cn)     //for copying every character of word to new2 
                {
                    new2[i]=word[i];
                    i++;
                }
            
                c = j + 'a';        //making integer to character 
                new2[i]=c;      
                i++;
                while(i<length_word)        //putting other elements in the array
                {
                    new2[i]=word[i];
                    i++;
                }
                new2[i]=0;           
                if(search(root, new2)==1)           //calling search function if the function returns 1 means the word is correct
                {
                    printf("Do you mean %s ?\n",new2);
                    count++;
                }
                j++;    
                
            }
            cn++; 
    } 

}

/*We use this type of auto correction for silent word . which while speaking we don't speak but in writing of spelling we write it
 * e.g.if user enter nock then it will check for knock */
void autocorrect_hiddenletter(struct TrieNode *root,char word[100])         //for hidden letter present in word
{
    //initialization of variable and array
    int length_word,i,cn=0,j,k;
    char c;
    char new3[101],new4[101];
    
    length_word=strlen(word);           //finding length of word which user entered
    
    while(cn<length_word)           
    {
        j=0;
        while(j<26)         //while loop will change value of every character to a to z
        {
            i=0;
            while(i<cn)     //for copying every character of word to new3 TO use it  
            {
                new3[i]=word[i];
                i++;
            }
            c = j + 'a';        //making integer to character 
            new3[i]=c;           
            i++;            
            /*logic for hidden letter*/
            for(k=i-1;i<=length_word;i++,k++)
            {
                new3[i]=word[k];
            }
            for(i=0;i<=length_word;i++)
            {
                new4[i]=new3[i];
            }
            new4[length_word+1]=0;      
            if(search(root,new4)==1)            //calling search function if the function returns 1 means the word is correct
            {
                printf("Do you mean %s ?\n",new4);
                count++;
            }
            j++;         
        }
        cn++;        
    }
}

