#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "Hashtable_easy.h"

#define MAX_LINE_LENGTH 1024

 // A structure to help print only if there are actual anagrams
typedef struct AnagramList {
    uint64_t key;
    char **words;
    int size;
    int capacity;
} AnagramList;

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

char *sortWord(char *word) {
    int length = strlen(word);
    char *sortedWord = (char *)malloc(length + 1);
    snprintf(sortedWord, length + 1, "%s", word);
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (sortedWord[i] > sortedWord[j]) {
                swap(&sortedWord[i], &sortedWord[j]);
            }
        }
    }
    return sortedWord;
}

uint64_t charToIntThroughBit27(char* sortWord){
    uint64_t num = 0;
    uint64_t pow = 1;
    for(int i = 0; i < strlen(sortWord); i++){
        num += (sortWord[i] - 'a' + 1) * pow;
        pow *= 27;
    }
    return num;
}

AnagramList* buildHashtable(int* listSize) {
    AnagramList* lists = NULL;
    // int listSize = 0;
    int listCapacity = 0;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    

    fp = fopen("./words.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("%s\n", line);
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        char *content = strdup(line);
        // Sort the word to use as a key
        
        char *sortedWord = strdup(content);
        sortedWord = sortWord(sortedWord);

        HTKeyValue kvp = {charToIntThroughBit27(sortedWord), content}; 
        HTKeyValue old_KVP = {NULL, NULL};
        // printf("sortedWord : %s | %llu\n", sortedWord, (unsigned long long) kvp.key);
        // printf("%s\n", kvp.value);

        // Save to AnagramList
        

        // Traverse the entire hashtable
        int found = 0;
        // Check if the key has already been added to the anagrams list
        for (int i = 0; i < *listSize; i++) {
            if (lists[i].key == kvp.key) {
                // If the key is found, add the new word to the list
                if (lists[i].size == lists[i].capacity) {
                    lists[i].capacity *= 2;
                    lists[i].words = realloc(lists[i].words, lists[i].capacity * sizeof(char *));
                }
                lists[i].words[lists[i].size++] = strdup(kvp.value);
                found = 1;
                break;
            }
        }
        // If the key is not found, add a new entry to the lists
        if (!found) {
            if (*listSize == listCapacity) {
                if(listCapacity == 0){
                    lists = (AnagramList*)malloc(4 * sizeof(AnagramList));
                    listCapacity = 4;
                } else{
                    listCapacity *= 2;
                    lists = (AnagramList*)realloc(lists, listCapacity * sizeof(AnagramList));
                }
            }

            lists[*listSize].key = kvp.key;
            lists[*listSize].capacity = 4;
            lists[*listSize].words = malloc(lists[*listSize].capacity * sizeof(char *));
            lists[*listSize].words[0] = strdup(kvp.value);
            lists[*listSize].size = 1;
            (*listSize)++;
        }
    }
    fclose(fp);
    if (line)
        free(line);

    // printf("IN BUILD: %p\n", &lists);

    return lists;
}

void printAnagrams(AnagramList* lists, int listSize){    
    // Now print all anagram groups that have more than one element
    for (int i = 0; i < listSize; i++) {
        if (lists[i].size > 1) {
            // printf("Anagrams for the key '%llu':\n", (unsigned long long) lists[i].key);
            printf("Anagrams for the key '%s':  ", sortWord(lists[i].words[0]));
            for (int j = 0; j < lists[i].size; j++) {
                printf("%s\t", lists[i].words[j]);
            }
            printf("\n");
        }
        // Clean up
        for (int j = 0; j < lists[i].size; j++) {
            free(lists[i].words[j]);
        }
        free(lists[i].words);
        // free(lists[i].key);
    }
    free(lists);
}


int main() {
    // AnagramList* lists = NULL;
    int listSize = 0;


    AnagramList* lists = buildHashtable(&listSize);
    printf("MAIN: %p\n", &lists);
    printf("MAIN *lists: %p\n", lists);
    printAnagrams(lists, listSize);
    // DestroyHashtable(ht);
    return 0;
}