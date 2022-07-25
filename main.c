#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "autocorrect.h"

void main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    /*initialization of variables and array*/
    FILE *fmain = NULL;
    int choice;
    int cnt;
    char * temp_word;
    char data[100];
    char ch[100];
    char word[1000];
    char output[][32] = {"incorrect word ", "correct word"};
    struct TrieNode *root = getNode();
        
    printf("            -------------WELCOME TO SPELLING CHECKER AND AUTO Suggestion SYSTEM !! -----------------\n\n");
    fmain = fopen("trie.txt" , "r");        //opening file in read mode
    while(fscanf(fmain,"%s",ch)!=EOF)       //reading character 
    {
        insert(root,ch);        //calling insert function 
    }
    fclose(fmain);      //closing file after reading all the words 
    
    printf("Enter a line: ");
    scanf("%[^\n]",word); 
    for(int i=0;i<=strlen(word);i++){
        if(word[i]>=65&&word[i]<=90)
            word[i]=word[i]+32;
    }        
      //scan for whole line
    temp_word = strtok (word," ,.-");
    while (temp_word != NULL)           
    {
            printf ("\n%s  --- %s\n\n", temp_word , output[search(root, temp_word)] );
            if(search(root, temp_word)==0)           
            {
                        //this will traverse through all auto correction methods which we implemented
                        for(cnt=0;cnt<=3;cnt++)
                        {
                            if(cnt==0)
                                autocorrect_swap(root,temp_word);
                            else if(cnt==1)
                                autocorrect_hiddenletter(root,temp_word);
                            else if(cnt==2)
                                autocorrect_repeat(root,temp_word);
                            else 
                                autocorrect_letter(root,temp_word);
                        }
                        if(cnt==0)
                            printf("\nSuggestion of a word not found !!\n\n");
            
            }    
            temp_word = strtok (NULL, " ,.-");
    }    
    /*This is for if we want to add any word to the file*/
    printf("\nDo you want to add any word in our list ('1' for yes '0' for no): ");
    scanf("%d",&choice);        
    if(choice==1)          
    {
            printf("\nGive the word which you want to add into list : ");
            scanf("%s",data);     
            for(int i=0;i<=strlen(data);i++){
                if(data[i]>=65&&data[i]<=90)
                    data[i]=data[i]+32;
   }  //ask for the word which user want to insert in file
            if(search(root,data)==0)
            {
                fmain = fopen("trie.txt" , "a");            //open file in append mode
                fputs(data , fmain);                        //putting that word into file 
                fputs("\n" , fmain);                        //this is for enter,because in our list there are each word in new line
                printf("\nYour word is successfully entered !!\n\n");
                fclose(fmain);
            }
            else
                printf("\nWord already exist !!\n\n");
    }
}