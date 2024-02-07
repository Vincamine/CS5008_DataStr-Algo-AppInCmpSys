#include<stdio.h>
#include<stdlib.h>
#include "node.h"

typedef struct L_List {
    L_Node* head;
    int size;
}L_List;

L_List* createList(void) {
    L_List* listP = (L_List*)malloc(sizeof(L_List));
    if(listP == NULL){
        return NULL;
    }
    listP->head = NULL;
    listP->size = 0;
    return listP;
}

void addNode(L_List* list, int value) {
    L_Node* newNode = createNode(value);
    if(newNode == NULL)
        return;
    if(list->head == NULL)
        list->head = newNode;
    else{
        L_Node* current = list->head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
    list->size += 1;
}

void removeNodeAt(L_List* list, int index) {
    if(list == NULL || list->head == NULL || index < 0 || index >= list->size){
        return;
    }
    L_Node* toRemove = NULL;
    if(index == 0){
        toRemove = list->head;
        list->head = list->head->next;
    }
    else{
        L_Node* current = list->head;
        for(int i = 0; i < index-1; i++){
            current = current->next;
        }
        toRemove = current->next;
        current->next = toRemove->next;
    }
    if(toRemove != NULL){
        free(toRemove);
    }
    list->size -= 1;
}

void removeAllNodesWithValue(L_List* list, int value) {
    if(list == NULL || list->head == NULL) return;
    L_Node *prev = NULL, *current = list->head;
    while(current != NULL){
        if(current->value == value){
            if(prev == NULL){
                list->head = current->next;
                free(current);
                current = list->head;
            }
            else{
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
            list->size -= 1;
        }
        else{
            prev = current;
            current = current->next;
        }
    }
}

void printList(L_List* list){
    L_Node* current = list->head;
    while(current != NULL){
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeList(L_List* list){
    L_Node* currentNode = list->head;
    L_Node* nextNode;
    while (currentNode != NULL){
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(list);
}

int main() {
    L_List* myList = createList();
    if(!myList){
        printf("Failed to create list. \n");
        return 1;
    }
    L_Node* n1 = createNode(1);
    if(!n1){
        printf("Failed to create node. \n");
        return 1;
    }
    myList->head = n1;
    myList->size = 1;
    addNode(myList, 3);
    addNode(myList, 5);
    addNode(myList, 7);
    addNode(myList, 9);
    addNode(myList, 7);
    addNode(myList, 9);
    addNode(myList, 9);
    printList(myList);

    removeNodeAt(myList,10);
    printList(myList);
    removeNodeAt(myList,1);
    printList(myList);
    removeAllNodesWithValue(myList, 9);
    printList(myList);
    freeList(myList);
    return 0;
}
