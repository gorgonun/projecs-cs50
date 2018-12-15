// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

node *HEAD = NULL;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Temporary value
    int comp = -1;
    // Temporary storage
    node *checker = HEAD;
    // Compare until the second node
    while (comp != 0 && checker->next != NULL)
    {
        comp = strcasecmp(checker->word, word);
        checker = checker->next;
    }
    if (comp != 0)
    {
        // Compare the last node
        comp = strcasecmp(checker->word, word);
        if (comp != 0)
        {
            return false;
        }
    }
    return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file
    FILE *dict = fopen(dictionary, "r");
    // Allocate space
    char *word = malloc(LENGTH + 1);
    // Create a node
    node *list;
    // Copy strings from dict to word
    while (fscanf(dict, "%s", word) != EOF)
    {
        // If the list doesn't exists, create
        if (HEAD == NULL)
        {
            list = create(word);
            // If fail to create, unload anything and return false
            if (list == NULL)
            {
                unload();
                return false;
            }
            // Assign the first node to HEAD
            HEAD = list;
        }
        // If exists, insert
        else
        {
            HEAD = insert(HEAD, word);
        }
    }
    // Free space allocated and close file
    free(word);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int i = 1;
    node *next = HEAD;
    if (next == NULL)
    {
        return 0;
    }
    else
    {
        while (next->next != NULL)
        {
            next = next->next;
            i ++;
        }
    }
    return i;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = HEAD;
    while (cursor != NULL)
    {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    return true;
}

node *create(const char *word)
{
    node *newValue = malloc(sizeof(node));
    strcpy(newValue->word, word);
    newValue->next = NULL;
    return newValue;
}

node *insert(node *first, char *word)
{
    node *head = malloc(sizeof(node));
    strcpy(head->word, word);
    head->next = first;
    return head;
}