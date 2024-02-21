#include "LinkedList_easy.h"
#include <stdio.h>
#include <stdlib.h>
#include  <string.h>

LinkedListNode* CreateLinkedListNode(char *data){
    LinkedListNode* nodeP = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if(nodeP == NULL){return NULL;}
    else{
        nodeP->payload=data;
        nodeP->prev = NULL;
        nodeP->next = NULL;
        return nodeP;
    }
}

int DestroyLinkedListNode(LinkedListNode *node){
    if(node == NULL){return 1;}
    /*
    free(node->payload);
    free(node->prev);
    free(node->next);
    node->payload = NULL;
    node->next = NULL;
    */
    free(node);
    return 0;
}

int RemoveHead(LinkedList list){
    if(list == NULL || list->head == NULL){ return 1;}
    else{
        LinkedListNodePtr toRemove = list->head;
        if(list->head->next == NULL){
            list->head = NULL;
            list->tail = NULL;
            DestroyLinkedList(list);
        }
        else{
            list->head = list->head->next;
            list->head->prev = NULL;
            if(list->head->next == NULL){
                list->tail = list->head;
            }
        }
        free(toRemove);
        return 0;
    }  
}

int RemoveTail(LinkedList list){
    if(list == NULL || list->head == NULL || list->tail == NULL){ return 1;}
    else{   
        LinkedListNodePtr toRemove = list->tail;
        if(list->tail->prev == NULL){
            list->head = NULL;
            list->tail = NULL;
            DestroyLinkedList(list);
        }
        else{
            list->tail = list->tail->prev;
            list->tail->next = NULL;
            if(list->tail->prev == NULL){
                list->head = list->tail;
            }
        }
        free(toRemove);
        return 0;
    }
}

int RemoveLLElem(LinkedList list, LinkedListNodePtr ptr){
    if(list == NULL || ptr == NULL){ return 1;}

    if(ptr == list->head){ return RemoveHead(list);} 
    else if (ptr == list->tail){
        return RemoveTail(list);
    }
    else{
        LinkedListNodePtr toRemove = ptr;
        ptr->prev->next = toRemove->next;
        ptr->next->prev = toRemove->prev;
        free(toRemove);
    }
    return 0;
    
}

LinkedList CreateLinkedList(){
    LinkedList list = (LinkedList)malloc(sizeof(LinkedListHead));
    list->num_elements = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int DestroyLinkedList(LinkedList list){
    if(list == NULL || list->head == NULL) {return 1;}

    LinkedListNode* nodeP = list->head;
    while(nodeP != NULL){
        LinkedListNode* toRemove = nodeP;
        nodeP = nodeP->next;
        DestroyLinkedListNode(toRemove);
        return 0;
    }
    return 0;
}

unsigned int NumElementsInLinkedList(LinkedList list){
    return list->num_elements;
}

int InsertLinkedList(LinkedList list, char* data){
    if(list == NULL || data == NULL){return 1;}
    LinkedListNode* nodeP = CreateLinkedListNode(data);
    nodeP->next = list->head->next;
    list->head = nodeP;
    list->num_elements++;
    return 0;
}

int PopLinkedList(LinkedList list, char** dataPtr){
    if (list == NULL || list->head == NULL || dataPtr == NULL) { return 1; }
    *dataPtr = list->head->payload;
    LinkedListNodePtr toRemove = list->head;
    if (list->head == list->tail) { // Single element
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    free(toRemove); // Adjust to proper node deallocation if needed
    list->num_elements--;
    return 0;
}

int AppendLinkedList(LinkedList list, void* payload){
    if (list == NULL || payload == NULL) { return 1; }
    LinkedListNode* newNode = CreateLinkedListNode(payload);
    if (newNode == NULL) { return 1; }
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->num_elements++;
    return 0;
}


void SortLinkedList(LinkedList list, unsigned int ascending){
    if (list->head == NULL){ return;}
    if (ascending == 0){
        LinkedListNode* curNode = list->head;
        while(curNode->next != NULL){
            if (strcmp(curNode->payload, curNode->next->payload) < 0){
                char* temp = curNode->next->payload;
                curNode->payload = temp;
                curNode = list->head;
            } else {
                curNode = curNode->next;
            }
        }
    } else if (ascending == 1){
        LinkedListNode* curNode = list->head;
        while(curNode->next != NULL){
            if (strcmp(curNode->payload, curNode->next->payload) > 0){
                char* temp = curNode->next->payload;
                curNode->payload = temp;
                curNode = list->head;
            } else {
                curNode = curNode->next;
            }
        } 
    } else {
        return;
    }
}

LLIter CreateLLIter(LinkedList list) {
    LLIter iter = (LLIter)malloc(sizeof(LLIterSt));
    if (iter == NULL) { return NULL;}
    iter->list = list;
    iter->cur_node = list->head;
    return iter;
}

int LLIterHasNext(LLIter iter) {
    if (iter->cur_node == NULL || iter->cur_node->next == NULL) {
        return 0;
    }
    return 1;
}


int LLIterHasPrev(LLIter iter) {
    if (iter->cur_node == NULL || iter->cur_node->prev == NULL) {
        return 0;
    }
    return 1;
}


int LLIterNext(LLIter iter) {
    if (LLIterHasNext(iter) == 0) {
        return 1;
    }
    iter->cur_node = iter->cur_node->next;
    return 0;
}


int LLIterPrev(LLIter iter) {
    if (LLIterHasPrev(iter) == 0) {
        return 1;
    }
    iter->cur_node = iter->cur_node->prev;
    return 0;
}


int DestroyLLIter(LLIter iter) {
    free(iter);
    return 0;
}


int LLIterGetPayload(LLIter iter, char** payload) {
    if (iter->cur_node == NULL) {
        return 1;
    }

    int len = strlen(iter->cur_node->payload) + 1;
    *payload = (char*)malloc(len);
    if(payload == NULL){return 1;}
    strcpy(*payload, iter->cur_node->payload);
    //snprintf(*payload, len, iter->cur_node->payload);
    return 0;
}


int LLIterDelete(LLIter iter) {
    if (!LLIterHasPrev(iter) && !LLIterHasNext(iter)) {
        RemoveHead(iter->list);
        free(iter);
        return 1;
    }

    if (!LLIterHasNext(iter)) {
        iter->cur_node = iter->cur_node->prev;
        RemoveTail(iter->list);
        return 0;
    }

    iter->cur_node = iter->cur_node->next;
    RemoveLLElem(iter->list, iter->cur_node->prev);

    return 0;
}


int LLIterInsertBefore(LLIter iter, char* payload) {
    if (iter->list->head == iter->cur_node) {
        InsertLinkedList(iter->list, payload);
    } else {
        LinkedListNode* node = CreateLinkedListNode(payload);
        node->next = iter->cur_node;
        node->prev = iter->cur_node->prev;
        iter->cur_node->prev->next = node;
        iter->cur_node->prev = node;
        iter->list->num_elements++;
    }

    return 0;
}