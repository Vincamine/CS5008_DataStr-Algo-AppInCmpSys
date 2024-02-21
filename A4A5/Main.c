#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    LinkedList myLinkedList = CreateLinkedList();
    if (myLinkedList == NULL) {
        printf("Failed to create linked list.\n");
        return 1;
    }

    char* data1 = strdup("Data 1");
    char* data2 = strdup("Data 2");
    char* data3 = strdup("Data 3");

    if (InsertLinkedList(myLinkedList, data1) != 0 ||
        InsertLinkedList(myLinkedList, data2) != 0 ||
        InsertLinkedList(myLinkedList, data3) != 0) {
        printf("Failed to insert into linked list.\n");
        // Clean up allocated strings in case of failure
        free(data1);
        free(data2);
        free(data3);
        DestroyLinkedList(myLinkedList);
        return 1;
    }

    LLIter iter = CreateLLIter(myLinkedList);
    if (iter == NULL) {
        printf("Failed to create iterator.\n");
        DestroyLinkedList(myLinkedList);
        return 1;
    }

    printf("Traversing linked list:\n");
    char* payload;
    do {
        LLIterGetPayload(iter, &payload);
        printf("%s\n", payload);
    } while (LLIterNext(iter) == 0);

    DestroyLLIter(iter);
    DestroyLinkedList(myLinkedList);

    return 0;
}
