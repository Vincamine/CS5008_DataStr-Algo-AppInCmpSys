#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dllNode{
    int value;
    struct dllNode* prev;
    struct dllNode* next;
}dllNode;

typedef struct dll{
    struct dllNode* head;
    struct dllNode* tail;
    int size;
}dll;

dllNode* createNode (int value){
    dllNode* nodeP = (dllNode*)malloc(sizeof(dllNode));
    if(nodeP == NULL){return NULL;}
    else{
        nodeP->value = value;
        nodeP->prev = NULL;
        nodeP->next = NULL;
        return nodeP;
    }
}

dll* createDll(){
    dll* listP = (dll*)malloc(sizeof(dll));
    if(listP == NULL){return NULL;}
    else{
        listP->head = NULL;
        listP->tail = NULL;
        listP->size = 0;
        return listP;
    }
}

void addLeft(dll* list, int value){
    dllNode* newNodeL = createNode(value);
    if(list == NULL || newNodeL == NULL){return;}
    else{
        newNodeL->prev = NULL;
        newNodeL->next = list->head;
        newNodeL->value = value;

        if(list->head != NULL){
            list->head->prev = newNodeL;
        }
        list->head = newNodeL;
        if(list->tail == NULL){
            list->tail = newNodeL;
        }
        list->size += 1;
    }
}

void addRight(dll* list, int value){
    dllNode* newNodeR = createNode(value);
    if(list == NULL || newNodeR == NULL){return;}
    else{
        newNodeR->next = NULL;
        newNodeR->prev = list->tail;
        newNodeR->value = value;
        if(list->tail != NULL){
            list->tail->next = newNodeR;
        }
        list->tail = newNodeR;
        if(list->head == NULL){
            list->head = newNodeR;
        }
        list->size += 1;
    }
}

void removeLeft(dll* list){
    if(list == NULL || list->head == NULL){return;}
    else{
        dllNode* toRemove = list->head;
        if(list->head == list->tail){
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            list->head = list->head->next; 
            list->head->prev = NULL;
        }
        free(toRemove);
    }
    list->size -= 1;
}


void removeRight(dll* list){
    if(list == NULL || list->head == NULL){return;}
    else{
        dllNode* toRemove = list->tail;
        if(list->head == list->tail){
            list->head = NULL;
            list->tail = NULL;
        }
        else{
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
        free(toRemove);
    }
    list->size -= 1;
}

void insertAt(dll* list, int index, int value){
    if(list == NULL || index < 0 || index > list->size){return;}
    else{   
        if(index == 0){
            addLeft(list, value);   
        }else if (index == list->size-1){
            addRight(list, value);
        }
        else{
            dllNode* newNode = createNode(value);
            if(newNode == NULL){return;}
            dllNode* current = list->head;
            for(int i = 0; i < index-1; i++){
                current = current->next;
            }
            newNode->prev = current;
            newNode->next = current->next;
            current->next = newNode;
            list->size++;
        } 
    }
}
 
void removeAt(dll* list, int index){
    if(list == NULL || index < 0 || index >= list->size){return;}
    else{
        if(index == 0){
            removeLeft(list);
        }
        else if(index == list->size-1){
            removeRight(list);
        }
        else{
            dllNode* toRemove = list->head;
            for(int i = 0; i < index; i++){
                toRemove = toRemove->next;
            }
            toRemove->next->prev = toRemove->prev;
            toRemove->prev->next = toRemove->next;
            free(toRemove);
            list->size--;   
        }
    }
}

bool hasValue(dll* list, int value){
    if(list == NULL || list->head == NULL){
        printf("The value: %d doesn't exit.\n", value);
        return false;
    }
    else{
        dllNode* loc = list->head;
        int count = 0;
        while(loc != NULL){
            if(loc->value == value){
                printf("The value exits in loc: %d.\n", count);
                return true;
            }
            count++;
            loc = loc->next;
        }
    }
    printf("The value: %d doesn't exit.\n", value);
    return false;
}

int printDll(dll* list){
    if(list == NULL || list->head == NULL || list->size <= 0){return 0;}
    else{
        dllNode* current = list->head;
        while(current != NULL){
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
    }
    return 1;
}

void freeMemory(dll* list){
    if(list == NULL){return;}
    else{
        dllNode* needFree = list->head;
        while(needFree != NULL){
            dllNode* temp = needFree;
            needFree = needFree->next;
            free(temp);
        }
        free(list);
    }
}

int main(){
    dll* myList = createDll();
    addLeft(myList,10);
    addLeft(myList,9);
    addLeft(myList,8);
    addLeft(myList,7);
    addRight(myList,11);
    addRight(myList,12);
    addRight(myList,13);
    addLeft(myList,6);
    printDll(myList);
    removeRight(myList);
    printDll(myList);
    removeLeft(myList);
    printDll(myList);
    removeAt(myList,0);
    printDll(myList);

    removeAt(myList,2);
    printDll(myList);
    insertAt(myList, 2, 10);
    printDll(myList);
    hasValue(myList, 20);
    hasValue(myList, 10);
    freeMemory(myList);
    return 0;
}
