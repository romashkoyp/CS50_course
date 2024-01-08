// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Done. Choose number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // done
    // Convert the input word to lowercase
    char lowercase_word[LENGTH + 1];
    for (int i = 0; word[i] != '\0'; i++)
    {
        lowercase_word[i] = tolower(word[i]);
    }
    lowercase_word[strlen(word)] = '\0';

    // Hash word to obtain a hash value
    unsigned int hash_value = hash(lowercase_word);

    // Access linked list at that index in the hash table
    node *cursor = table[hash_value];

    // Traverse linked list, looking for the word (strcasecmp), keep moving until cursor get to NULL
    while (cursor != NULL)
    {
        // Compare word with the current node's word case-insensitively
        int len_word = strlen(lowercase_word);
        if (len_word > 0 && len_word < 46 && strcasecmp(cursor->word, lowercase_word) == 0)
        {
            // Word found in the dictionary
            return true;
        }

        // Check posessive
        if (len_word > 2 && lowercase_word[len_word - 2] == '\'' && strcasecmp(cursor->word, lowercase_word) == 0)
        {
            // Word found in the dictionary
            return true;
        }

        // Move to the next node in the linked list
        cursor = cursor->next;
    }

    // Word did not find in the dictionary
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function
    const unsigned int multiplier = 61543;
    unsigned int hash_value = 77621;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value = hash_value * multiplier + word[i];
    }

    hash_value = hash_value % N;
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file for reading
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        // Print error message if file cannot be opened
        printf("Error opening file!\n");
        return false;
    }

    // Create array for storing words from dictionary
    char buffer[LENGTH + 1];

    // Read dictionary file line by line
    while (fscanf(infile, "%s", buffer) != EOF)
    {
        // Allocate memory for new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        unsigned int hash_value = hash(buffer);

        // Copy word to new node
        strcpy(new_node->word, buffer);

        // Add new node to hash table
        new_node->next = table[hash_value];
        table[hash_value] = new_node;
    }
    // Close dictionary file
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Create unsigned integer for counting nodes' quantity
    unsigned int node_count = 0;

    // Iterate over each bucket and count the number of nodes in each bucket
    for (int i = 0; i < N; i++)
    {
        // Point cursor to the first node
        node *cursor = table[i];

        // Iterate over each node in the bucket and count the nodes
        while (cursor != NULL)
        {
            node_count++;
            cursor = cursor->next;
        }

        if (cursor != NULL)
        {
            node_count = 0;
        }
    }
    return node_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate each bucket in hash table
    for (int i = 0; i < N; i++)
    {
        // Point cursor to the first node
        node *cursor = table[i];

        // Traverse the linked list for each bucket and free the memory for each node
        while (cursor != NULL)
        {
            // Store the next node temporarily in tmp
            node *tmp = cursor->next;

            // Free the memory for the current node (pointed to by cursor)
            free(cursor);

            // Move cursor to the next node in the linked list (previously stored in tmp)
            cursor = tmp;
        }

        if (cursor != NULL)
        {
            return false;
        }
        // After traversing the bucket, set the bucket to NULL to indicate an empty list
        table[i] = NULL;
    }
    return true;
}