#include "LinkedList.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

LinkedListNode* CreateLinkedListNode(char *data) {
    if (!data)
        return NULL;

    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(struct ll_node));
    if (newNode) {
        size_t len = strlen(data) + 1;
        newNode->payload = (char*)malloc(len * sizeof(len));
        if (newNode->payload) {
            memcpy(newNode->payload, data, len);
            newNode->next = NULL;
            newNode->prev = NULL;
            return newNode;
        } else {
            free(newNode);
            return NULL;
        }
    }
    return NULL;
}

int DestroyLinkedListNode(LinkedListNode *node) {
    if (node) {
        if (node->prev) {
            if (node->next) {
                node->prev->next = node->next;
            } else {
                node->prev->next = NULL;
            }
        }
        if (node->next) {
            if (node->prev) {
                node->next->prev = node->prev;
            } else {
                node->next->prev = NULL;
            }
        }

        free(node->payload);
        free(node);
    }
    return (node == NULL);
}

int RemoveLLElem(LinkedList list, LinkedListNodePtr ptr) {
    if (!list || !ptr)
        return 1;

    LinkedListNodePtr current = list->head;
    LinkedListNodePtr previous = NULL;
    int i;

    // Traverse the list until the specified node is found
    while (current) {
        if (*(current->payload) == *(ptr->payload))
            break;
        previous = current;
        current = current->next;
    }

    // If the node was not found, return error
    if (!current) {
        return 1;
    }
    // Update the pointers to bypass the node to be removed
    if (!previous) {
    list->head = current->next;
    if (list->head)
        list->head->prev = NULL;
} else {
    previous->next = current->next;
    if (current->next) {
        current->next->prev = previous;
    }
}
    // Update the tail pointer if necessary
    if (current == list->tail)
        list->tail = previous;

    // Free the memory occupied by the removed node
    DestroyLinkedListNode(current);

    // Update the number of elements in the list
    list->num_elements--;

    return 0;  // Return success
}



LinkedList CreateLinkedList() {
    LinkedList list = (LinkedList)malloc(sizeof(struct ll_head));
    if (!list) {
        return NULL;  // Return NULL if malloc fails
    }
    list->num_elements = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int DestroyLinkedList(LinkedList list) {
    if (!list) {
        return 1;
    }

    LinkedListNode* current = list->head;
    LinkedListNode* next;

    while (current != NULL) {
        next = current->next;
        free(current->payload);
        free(current);
        current = next;
    }

    free(list);
    return 0;
}

unsigned int NumElementsInLinkedList(LinkedList list) {
    if (!list)
        return 0;
    return list->num_elements;
}

int InsertLinkedList(LinkedList list, char* data) {
    if (!list)
        return 1;

    LinkedListNode* newNode = CreateLinkedListNode(data);
    if (!newNode)
        return 1;

    newNode->next = list->head;
    if (list->head)
        list->head->prev = newNode;
    else
    list->tail = newNode;
    list->head = newNode;

    list->num_elements++;
    return 0;
}

int PopLinkedList(LinkedList list, char** dataPtr) {
    if (!list || !list->head || !dataPtr)
        return 1;

    LinkedListNodePtr temp = list->head;
    *dataPtr = temp->payload;
    list->head = list->head->next;

    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }

    free(temp);
    list->num_elements--;
    return 0;
}

void SortLinkedList(LinkedList list, unsigned int ascending) {
    if (!list)
        return;

    LinkedListNode *i, *j, *minNode, *temp;

    for (i = list->head; i != NULL; i = i->next) {
        minNode = i;

        for (j = i->next; j != NULL; j = j->next) {
            int payload1 = *(int*)(j->payload);
            int payload2 = *(int*)(minNode->payload);
            int comparisonResult;
            if (ascending) {
                comparisonResult = payload1 - payload2;
            } else {
                comparisonResult = payload2 - payload1;
            }
            if (comparisonResult < 0)
                minNode = j;
        }
        if (minNode != i) {
        temp->payload = i->payload;
        i->payload = minNode->payload;
        minNode->payload = temp->payload;
        }
    }
}

LLIter CreateLLIter(LinkedList list) {
    if (!list) {
        printf("No list/ Invalid List argument");
        return NULL;
    }
    LLIter iter = (LLIter)malloc(sizeof(*iter));
    if (iter) {
        iter->list = list;
        iter->cur_node  = list->head;
    }
    return iter;
}


int LLIterHasNext(LLIter iter) {
    if ( !iter || !iter->cur_node ) {
        return 0;
    }
    return (iter ->cur_node ->next != NULL);
}

int LLIterHasPrev(LLIter iter) {
    if ( !iter || !iter->cur_node ) {
        return 0;
    }
    return (iter ->cur_node ->prev != NULL);
}

int LLIterNext(LLIter iter) {
    if ( !iter || !iter->cur_node ) {
        return 0;
    }

    if ( LLIterHasNext(iter) ) {
        iter->cur_node = iter->cur_node->next;
        return 1;
    } else {
        return 0;
    }
}

int LLIterPrev(LLIter iter) {
    if ( !iter || !iter->cur_node ) {
        return 0;
    }

    if ( LLIterHasPrev(iter) ) {
        iter->cur_node = iter->cur_node->prev;
        return 1;
    } else {
        return 0;
    }
}

int DestroyLLIter(LLIter iter) {
    free(iter);
     return 0;
}

int LLIterGetPayload(LLIter iter, char** payload) {
    if (!iter || !iter->cur_node || !payload)
        return 1;

    *payload = iter->cur_node->payload;
    return 0;
}

int LLIterDelete(LLIter iter) {
    LinkedListNodePtr temp = iter->cur_node;

    if (!LLIterHasPrev(iter) && !LLIterHasNext(iter)) {
        free(temp);
        iter->cur_node = NULL;
        return 1;
    } else if (!LLIterHasPrev(iter) && LLIterHasNext(iter)) {
        iter->cur_node = temp->next;
        iter->cur_node->prev = NULL;
    } else if (LLIterHasPrev(iter) && !LLIterHasNext(iter)) {
        iter->cur_node = temp->prev;
        iter->cur_node->next = NULL;
    } else {
        iter->cur_node = temp->prev;
        iter->cur_node->next = temp->next;
        iter->cur_node->prev = temp->prev->prev;
    }

    free(temp);
    return 0;
}

int LLIterInsertBefore(LLIter iter, char* payload) {
    if (!iter || !payload)
        return 1;  // Return 1 to indicate failure

    LinkedListNode* newNode = CreateLinkedListNode(payload);
    if (!newNode)
        return 1;
    if (iter->cur_node) {
        newNode->prev = iter->cur_node->prev;
        newNode->next = iter->cur_node;
        if (iter->cur_node->prev)
            iter->cur_node->prev->next = newNode;
        else
            iter->list->head = newNode;
        iter->cur_node->prev = newNode;
    } else {
        newNode->next = iter->list->head;
        if (iter->list->head)
            iter->list->head->prev = newNode;
        else
        iter->list->tail = newNode;
        iter->list->head = newNode;
    }
    iter->list->num_elements++;
    return 0;
}