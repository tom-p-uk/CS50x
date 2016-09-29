/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"



typedef struct node 
{
    char dicWord[LENGTH+1];
    struct node* next;
} 
node;



// global variables
node* hashTable[HASH_TABLE_SIZE];
int wordCount = 0;



// check function - returns true if word is in dictionary else false

bool check(const char* word)
{
    // calculate length of each string passed into function and store as an int
    int wordLength = strlen(word);
    
    // create char array to store converted lower case string
    char wordLower[LENGTH + 1];
    
    // iterate through string converting any upper case characters to lower case
    for (int i = 0; i < wordLength; i++)
    {
        if (isupper(word[i]))
        {
            wordLower[i] = tolower(word[i]);
        }
        
        else
        {
            wordLower[i] = word[i];
        }
    }
    
    // terminate the string
    wordLower[wordLength] = '\0';
    
    // run string into hash function to get hash table index
    int hashIndex = hashFunction(wordLower);
    
    // set up a node pointer to traverse linked list and check for matching strings
    node* trav = hashTable[hashIndex];
    
    // if hash table entry is null word is misspelled
    if (hashTable[hashIndex] == NULL)
    {
      return false;
    }
    
    // traverse linked list until hitting a null pointer, comparing strings each time
    while (trav != NULL)
    {
        if (strcmp(trav->dicWord,wordLower) == 0)
        {
            return true;
        }
        
        else 
        {
            trav = trav->next;
        }
    }
    return false;
}





// load function loads dictionary into memory
// returns true if successful else false

bool load(const char* dictionary)
{
    // open dictionary from file
    FILE* dicptr = fopen(dictionary,"r");
    
    if (dicptr == NULL)
    {
        printf("Couldn't open dictionary.\n");
        return false;
    }
    
    // set all node pointers in hashTable array to NULL
    for (int i = 0; i < HASH_TABLE_SIZE; i ++)
    {
        hashTable[i] = NULL;
    }
    
    // loop until end of end of dictionary file
    while(!feof(dicptr))
    {
        // create pointer to node on the heap and set its 'next' pointer to NULL
        node* newNode = malloc(sizeof(node));
        newNode->next = NULL;
        
        // load string from dictionary into newNode->word and check for end of dictionary file
        if (fscanf(dicptr, "%s", newNode->dicWord) != 1)
        {   
            // if end of dictionary file, free newNode and return true
            free(newNode);
            return true;
        }
        // store index returned from hash function as int
        int hashIndex = hashFunction(newNode->dicWord);
        
        // set hashTable[hashIndex] to newNode if that array entry is null
        if (hashTable[hashIndex] == NULL)
        {
            hashTable[hashIndex] = newNode;
        }

        // else set next pointer to previous head of linked list and make newNode the new head of the list
        else 
        {
            node* head = hashTable[hashIndex];
            newNode->next = head;
            head = newNode;
            hashTable[hashIndex] = head;
        }
        
        // update dictionary word count
        wordCount ++;
    }
    fclose(dicptr);
    return true;
}





// size function returns number of words in dictionary if loaded
// else 0 if not yet loaded.
unsigned int size(void)
{
    if (wordCount > 0)
    {
        return wordCount;
    }

    else 
    {
        return 0;
    }
}





// unload function unloads dictionary from memory
// returns true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASH_TABLE_SIZE; i ++)
    {
        // initialise a new node pointer that will traverse the list and set it to index 'i' of hash table
        node* trav = hashTable[i];
        
        // traverse through list freeing nodes until reaching a null pointer
        while (trav != NULL)
        {
            node* temp = trav;
            trav = trav->next;
            free(temp);
        }
        
        // ensure that index 'i' of the hash table is set to null
        hashTable[i] = NULL;
    }
    return true;
}





// hash function - returns int based on string passed into it
// credit to reddit user (and cs50 staff?) delipity for providing the function
int hashFunction(const char* hashString)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(hashString); i<n; i++)
    {
        hash = (hash << 2) ^ hashString[i];
    }
    return hash % HASH_TABLE_SIZE;
}