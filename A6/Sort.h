#include "LinkedList.h"

#ifndef SORT_H

#define SORT_H

void SortInsertion(LinkedList* list);

void SortSelection(LinkedList* list);

void SortMerge(LinkedList* list);

void mergeSort(LinkedListNode** head);

void split(LinkedListNodePtr source, LinkedListNodePtr* front, LinkedListNodePtr* back);

LinkedListNodePtr merge(LinkedListNode* a, LinkedListNode* b);

#endif