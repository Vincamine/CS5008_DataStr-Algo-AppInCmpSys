#include "LinkedList_easy.h"
#include <stdio.h>
#include <stdlib.h>
#include  <string.h>

LinkedListNode* CreateLinkedListNode(char *data){
    LinkedListNode* nodeP = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if(nodeP == NULL){return NULL;}
    else{
        nodeP->payload=data;
        /*
        nodeP->payload = (char *)malloc(sizeof(char)*(strlen(data)+1));
        if (nodeP->payload == NULL) {
            //remember to free
            free(nodeP);
            return NULL;
        }
        strcpy(nodeP->payload, data);
        */
        nodeP->prev = NULL;
        nodeP->next = NULL;
        return nodeP;
    }
}

int DestroyLinkedListNode(LinkedListNode *node){
    if(node == NULL){return 1;}
    // if(node->payload != NULL){
    //     free(node->payload);
    // }
    /*
    free(node->payload);  //necessary
    free(node->prev);
    free(node->next);
    node->payload = NULL;
    node->next = NULL;
    */
    free(node);
    return 0;
}

int RemoveHead(LinkedList list){
    if(list == NULL || list->head == NULL){return 1;}
    else{
        LinkedListNodePtr toRemove = list->head; 
        LinkedListNodePtr toRemoveNext = list->head->next;
        //free(toRemove);  //F
        if (DestroyLinkedListNode(toRemove) == 1) {
            return 1;
        }

        if(list->num_elements == 1){
            // //check
            // if (DestroyLinkedList(list) == 1) {
            //     return 1;
            // }
            list->head = NULL;
            list->tail = NULL;
        } else {
            // list->head = list->head->next;
            // list->head->prev = NULL;
            // if(list->head->next == NULL){
            //     list->tail = list->head;
            // }
            list->head = toRemoveNext;
            toRemoveNext->prev = NULL;
        }

        list->num_elements--;
        return 0;
    }  
}

int RemoveTail(LinkedList list){
    if(list == NULL || list->head == NULL || list->tail == NULL){ return 1;}
    else{   
        LinkedListNodePtr toRemove = list->tail;
        LinkedListNodePtr toRemovePrev = list->tail->prev;

        printf("------\n");
        for (LinkedListNodePtr ptr = list->head; ptr != NULL; ptr = ptr->next) {
            printf("%p %p %p\n", ptr->prev, ptr, ptr->next);
        }
        printf("------\n");
        printf("checkpoint1\n");
        if(DestroyLinkedListNode(toRemove) == 1){
            return 1;
        }
        printf("checkpoint2\n");
        // free(toRemove);
        if(list->num_elements == 1){
            list->head = NULL;
            list->tail = NULL;
            printf("checkpoint3\n");
        }
        else{
            // list->tail = list->tail->prev;
            // list->tail->next = NULL;
            // if(list->tail->prev == NULL){
            //     list->head = list->tail;
            // }
            printf("checkpoint4\n");
            list->tail = toRemovePrev;
            printf("checkpoint6\n");
            printf("toRemovePrev: %p\n", toRemovePrev);
            if(toRemovePrev->next !=NULL)
            toRemovePrev->next = NULL;
            printf("checkpoint5\n");
        }
        //DestroyLinkedListNode(toRemove);
        list->num_elements--;
        printf("END\n");
        return 0;
    }
}

int RemoveLLElem(LinkedList list, LinkedListNodePtr ptr){
    if(list == NULL || ptr == NULL){ return 1;}

    printf("head: %p\n", list->head);
    printf("tail: %p\n", list->tail);
    printf("element: %ld\n", list->num_elements);
    printf("ptr: %p\n", ptr);

    if(ptr == list->head){ 
        printf("Remove HEAD\n");
        return RemoveHead(list);
    } 
    else if (ptr == list->tail){
        printf("Remove Tail\n");
        return RemoveTail(list);
    }
    else{
        printf("OTHER\n");
        LinkedListNodePtr toRemove = ptr;
        printf("\n\n%p\t%p\t%p\n\n",ptr->prev, ptr, ptr->next);
        if(ptr->prev != NULL && ptr->next != NULL){
            ptr->prev->next = toRemove->next;
            ptr->next->prev = toRemove->prev;
        } else if (ptr->prev == NULL && ptr->next == NULL) {
            list->head = NULL;
            list->tail = NULL;
        }
        
        // DestroyLinkedListNode(toRemove);
        list->num_elements--;
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
    printf("=====\n");
    while(nodeP != NULL){
        printf("%p\n", nodeP);
        LinkedListNode* toRemove = nodeP;
        nodeP = nodeP->next;
        if (DestroyLinkedListNode(toRemove) == 1) {
            return 1;
        }
        // return 0;
    }
    free(list);

    return 0;
}

unsigned int NumElementsInLinkedList(LinkedList list){
    return list->num_elements;
}

int InsertLinkedList(LinkedList list, char* data){
    if(list == NULL || data == NULL){return 1;}
    LinkedListNode* nodeP = CreateLinkedListNode(data);
    //forgot
    if (list->num_elements >= 1) {
        list->head->prev = nodeP;
    }
    nodeP->next = list->head;
    list->head = nodeP;
    //add tail
    if(list->num_elements == 0){
        list->tail = nodeP;
    }
    list->num_elements++;
    return 0;
}

int PopLinkedList(LinkedList list, char** dataPtr){
    if (list == NULL || list->head == NULL || dataPtr == NULL) { return 1; }
    
    *dataPtr = (char*)malloc(sizeof(char)*(strlen(list->head->payload)+1));
    if (*dataPtr == NULL) {
        return 1;
    }
    strcpy(*dataPtr, list->head->payload);
    // *dataPtr = list->head->payload;
    LinkedListNodePtr toRemove = list->head;
    if (list->head == list->tail) { 
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    // DestroyLinkedListNode(toRemove); 
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