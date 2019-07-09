// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;
//var for dictionary size
int dictSize = 0;
node *currentNode;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    //insertion vars
    int index = 0;
    
    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF){
        //count number of words in dictionary
        dictSize++;
        
        currentNode = root;
        //iterate over each char and put everything into structure
        for(int i = 0; i<strlen(word); i++){
            if(word[i]=='\''){
                index = 26;
            }
            else{
                index = toupper(word[i]) - 65;
            }
            //create node if required
            if(currentNode->children[index]==NULL){
                node *next = malloc(sizeof(node));
                currentNode->children[index] = next;
                for (int j= 0; j < N; j++){
                    next->children[j] = NULL;
                    next->is_word = false;
                }
            }
            //set currentNode to the next "depth"
            currentNode = currentNode->children[index];
        }
        //indicate that word like this exist
        currentNode->is_word = true;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(dictSize>0){
        return dictSize;
    }
    else{
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = 0;
    currentNode = root;
    for(int i = 0; i<strlen(word); i++){
        if(word[i]=='\''){
            index = 26;
        }
        else{
            index = toupper(word[i]) - 65;
        }
        
        //optimization
        if(currentNode->children[index] == NULL){
            return false;
        }
        currentNode = currentNode->children[index];
        
    }
    if(currentNode->is_word == true){
        return true;
    }
    return false;
}

bool currentNodeUnloader(node *nodeToFree){
    //recursively crawl to each node
    for(int j= 0; j < N; j++){
        if(nodeToFree->children[j]!=NULL){
            currentNodeUnloader(nodeToFree->children[j]);
        }
    }
    //free node start from the most deep and "left"
    free(nodeToFree);
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    currentNode = root;
    if(currentNodeUnloader(currentNode) ){
        return true;
    }
    else{
        return false;
    }
}