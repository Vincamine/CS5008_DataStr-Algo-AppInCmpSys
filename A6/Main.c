#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sort.h"

// Function to create a linked list of random integers
LinkedList CreateRandomList(int size) {
    LinkedList list = CreateLinkedList();
    unsigned int seed = time(NULL);

    for (int i = 0; i < size; i++) {
        int randomNum = rand_r(&seed) % 900 + 100;
        char *data = (char *)malloc((sizeof(randomNum) + 1) * sizeof(data));
        snprintf(data, sizeof(randomNum) + 1, "%d", randomNum);
        InsertLinkedList(list, data);
    }
    return list;
}

// Function to print the elements of a linked list
void PrintList(LinkedList list) {
    LLIter iter = CreateLLIter(list);
    char *payload;
    for (int i = 0; i < list->num_elements; i++) {
        LLIterGetPayload(iter, &payload);
        printf("%s ", payload);
        LLIterNext(iter);
    }
    printf("\n");
    DestroyLLIter(iter);

    printf("Number of elements in the list: %llu\n", list->num_elements);
}

int IsListSortedAscending(const LinkedList *list) {
    if ((*list)->head == NULL || (*list)->head->next == NULL) {
        return 1;
    }

    LinkedListNodePtr current = (*list)->head;

    while (current->next != NULL) {
        // Convert payload strings to integers for comparison
        int current_value = atoi(current->payload);
        int next_value = atoi(current->next->payload);

        if (current_value > next_value) {
        printf(" not sorted ascending : %d > %d\n",
        current_value, next_value);
        return 0;
        }
        current = current->next;
    }
    return 1;
}

int main() {
    LinkedList list = CreateRandomList(10);

    printf("Unsorted list:\n");
    PrintList(list);

    SortInsertion(&list);
    printf("\nSorted list using insertion sort:\n");
    PrintList(list);

    if (IsListSortedAscending(&list)) {
        printf("true");
    }

    if (!IsListSortedAscending(&list)) {
        printf("false ");
    }


    DestroyLinkedList(list); 
    list = CreateRandomList(10);

    printf("\nUnsorted list:\n");
    PrintList(list);

    SortSelection(&list);
    printf("\nSorted list using selection sort:\n");
    PrintList(list);

    if (IsListSortedAscending(&list)) {
        printf("true");
    }

    DestroyLinkedList(list);

    list = CreateRandomList(10);

    printf("\nUnsorted list:\n");
    PrintList(list);

    SortMerge(&list);
    printf("\nSorted list using Merge sort:\n");
    PrintList(list);

    if (IsListSortedAscending(&list)) {
        printf("true");
    }

    DestroyLinkedList(list);

    return 0;
}