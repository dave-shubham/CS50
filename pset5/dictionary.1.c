/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>

#include "dictionary.h"

FILE *fp;
trie *root;
int count=0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    
    int len=strlen(word),index,level=0;
    char *search;
    search=(char *)malloc(len+1);
    strcpy(search,word);
    //Changing case of word to lower case so that Foo,FOO,fOO, etc are all detected when foo is present in dictionary.
    for(index=0;index<len;index++)
    {
        if(isalpha(search[index]))
        {
            if(isupper(search[index]))
            {
                search[index]=tolower(search[index]);
            }
        }
    }
    
    trie *traverse;
    traverse=root;
    for(level=0;level<len;level++)
    {
        index=indexOfChar(search[level]);
        if(traverse->alpha[index]==NULL)
        {
            return false;  
        }
        traverse=traverse->alpha[index];
    }
    bool answer;
    if(traverse != NULL && traverse->isEOW)
    {
        answer=true;
    }
    else
    {
        answer=false;
    }
//    free(traverse);
//    free(search);
    return answer;
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    root=initialize();
    char word[LENGTH+1];
    
    FILE *input;
    input=fopen(dictionary,"r");
    
    if(input==NULL)
    {
        fclose(input);
        return false;
    }
     int c,index=0,checkInsert;
     
     // spell-check each word in text
    for (c = fgetc(input); c != EOF; c = fgetc(input))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            word[index] = c;
            index++;

            // ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(input)) != EOF && isalpha(c));

                // prepare for new word
                index = 0;
            }
        }

        // ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // consume remainder of alphanumeric string
            while ((c = fgetc(input)) != EOF && isalnum(c));

            // prepare for new word
            index = 0;
        }

        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';

            checkInsert=insert(word);
            if(checkInsert==0)
            {
                fclose(input);
                return false;
            }
            else
            {
                count++;
            }
            /*if(checkInsert==1)
            {
                //printf("Word %s is added\n",word);
                count++;
                printf("%d\t",count);
            }*/
            // prepare for next word
            index = 0;
        }
    }
    fclose(input);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
     return(count);
    //return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    deletion(root);
    root=NULL;
    free(root);
    return true;
}


//Returns a trie node after allocating memory to it.
trie * initialize()
{
    trie * node;
    node=(trie *)malloc(sizeof(trie));
    if(node == NULL)
    {
        printf("Could not allocate node\n");
        return(NULL);
    }
    int i;
    for(i=0;i<27;i++)
    {
        node->alpha[i]=NULL;
    }
    node->isEOW=0;
    return(node);
}

//Returns the index of character in trie node.
int indexOfChar(const char character)
{
    if(character>='a' && character<='z')
    {
        return(character-'a');
    }
    else
    {
        return(26);
    }
}

//Inserts a word into trie
int insert(const char * word)
{
    trie *traverse;
    traverse=root;
    int level=0,len=strlen(word),index;
    for(level=0;level<len;level++)
    {
        index=indexOfChar(word[level]);
        //printf("%d\t%c\n",index,word[level]);
        if(traverse->alpha[index]==NULL)
        {
            traverse->alpha[index]=initialize();
        }
        traverse=traverse->alpha[index];
    }
    traverse->isEOW=1;      //the word is present
    return(1);              //1 is true
}

void deletion(trie * node)
{
    int i;
    for(i=0;i<27;i++)
    {
        if(node->alpha[i]!=NULL)
        {
            deletion(node->alpha[i]);
        }
    }
    node=NULL;
    free(node);
    return;
}
