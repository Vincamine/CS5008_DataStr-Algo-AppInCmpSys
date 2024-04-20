#include "Sort.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void SortInsertion(LinkedList* list) {
    if (*list == NULL || (*list)->num_elements <= 1) {
        return; 
    }

    LLIter current, prev;

    for (int i = 1; i < (*list)->num_elements; i++) {
        current = CreateLLIter(*list);
        prev = CreateLLIter(*list);
        for (int j = 0; j <i; j++) {
            LLIterNext(current);
            LLIterNext(prev);
        }
        char *current_payload;
        LLIterGetPayload(current, &current_payload);
        while (LLIterHasPrev(current)) {
            LLIterPrev(prev);
            char *prev_payload;
            LLIterGetPayload(prev, &prev_payload);

            int current_Int = atoi(current_payload);
            int prev_Int = atoi(prev_payload);

            if (current_Int >= prev_Int) {
                break;
            }
            char *temp = prev->cur_node->payload;
            prev->cur_node->payload = current->cur_node->payload;
            current->cur_node->payload = temp;
            LLIterPrev(current);
        }
        DestroyLLIter(current);
        DestroyLLIter(prev);
    }
}


void SortSelection(LinkedList* list) {
    if (*list == NULL || (*list)->num_elements <= 1) {
        return; 
    }

    LinkedListNodePtr current, min, temp;

    for (current = (*list)->head; current != NULL; current = current->next) {
        min = current;
        for (temp = current->next; temp != NULL; temp = temp->next) {
            if (strcmp(temp->payload, min->payload) < 0) {
                min = temp;
            }
        }

        if (min != current) {
            char *temp_payload = min->payload;
            min->payload = current->payload;
            current->payload = temp_payload;
        }
    }
}


// Define function prototypes
void SortMerge(LinkedList* list);
void mergeSort(LinkedListNode** head);
void split(
    LinkedListNode* source,
    LinkedListNode** front,
    LinkedListNode** back
);
LinkedListNodePtr merge(LinkedListNode* a, LinkedListNode* b);

void SortMerge(LinkedList* list) {
    if (*list == NULL || (*list)->num_elements <= 1) {
        return;  // Nothing to sort
    }

    mergeSort(&((*list)->head));
}

// Recursive function to perform merge sort
void mergeSort(LinkedListNode** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    LinkedListNode* a;
    LinkedListNode* b;
    split(*head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *head = merge(a, b);
}

// Function to split the list into two halves
void split(
    LinkedListNode* source,
    LinkedListNode** front,
    LinkedListNode** back
) {
    LinkedListNode* fast;
    LinkedListNode* slow;
    slow = source;
    fast = source->next;

    // Move 'fast' two nodes and 'slow' one node
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

// Function to merge two sorted lists
LinkedListNodePtr merge(LinkedListNode* a, LinkedListNode* b) {
    LinkedListNode* result = NULL;

    if (a == NULL) {
        return b;
    } else if (b == NULL) {
        return a;
    }

    if (strcmp(a->payload, b->payload) <= 0) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }

    return result;
}