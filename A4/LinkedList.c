#include "LinkedList_easy.h"
#include<stdio.h>
#include<stdlib.h>

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
    if(node = NULL){return 1;}
    free(node->payload);
    free(node->prev);
    free(node->next);
    node->payload = NULL;
    node->next = NULL;
    return 0;
    //diff?

}

int RemoveHead(LinkedList list){
    if(list == NULL || list->head == NULL){ return 1;}
    else{
        LinkedListNodePtr toRemove = list->head;
        if(list->head->next == NULL){
            list->head == NULL;
            list->tail == NULL;
            DestroyLinkedList(list);
        }
        else{
            list->head = list->head->next;
            list->head->prev = NULL;
            if(list->head->next == NULL){
                list->tail == list->head;
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
            list->head == NULL;
            list->tail == NULL;
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
    else{
        if(ptr == list->head){ return RemoveHead;} 
        else if (ptr == list->tail){
            return RemoveTail;
        }
        else{
            LinkedListNodePtr toRemove = ptr;
            ptr->prev->next = toRemove->next;
            ptr->next->prev = toRemove->prev;
            free(toRemove);
        }
        return 0;
    }
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
    else{
        LinkedListNode* nodeP = list->head;
        while(nodeP != NULL){
            LinkedListNode* toRemove = nodeP;
            nodeP = nodeP->next;
            DestroyLinkedListNode(toRemove);
            return 0;
        } 
    }
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
    if(list == NULL || dataPtr == NULL){
        
    }
    
}

int AppendLinkedList(LinkedList list, void* payload){

}

int SliceLinkedList(LinkedList list, void** payload){

}
void SortLinkedList(LinkedList list, unsigned int ascending){

}

LLIter CreateLLIter(LinkedList list){}

int LLIterHasNext(LLIter iter){}

int LLIterHasPrev(LLIter iter){}

int LLIterNext(LLIter iter){}

int LLIterPrev(LLIter iter){}

int DestroyLLIter(LLIter iter){}

int LLIterGetPayload(LLIter iter, char** payload){}

int LLIterDelete(LLIter iter){}

int LLIterInsertBefore(LLIter iter, char* payload);
