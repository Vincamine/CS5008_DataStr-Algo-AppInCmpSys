/*
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */
#include "gtest/gtest.h"

extern "C" {
    #include "LinkedList_easy.h"
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
}
const char* first = "first";
const char* second = "second";
const char* third = "third";
const char* fourth = "fourth";

int contains(LinkedList list, char* str) {
    LinkedListNode* node = list->head;
    bool res = false;

    while (node != NULL) {
      res = res || strcmp(node->payload, str) == 0;
      node = node->next;
    }
    return res;
}

#define MAX_VALUE_LEN 75


TEST(LinkedList, CreateAndDestroy) {
  LinkedList list = CreateLinkedList();
  EXPECT_TRUE(list->num_elements == 0);
  DestroyLinkedList(list);
}

TEST(LinkedListNode, CreateAndDestroy) {
  LinkedListNode* node = CreateLinkedListNode((char*)first);
  EXPECT_TRUE(node->payload == first);
  DestroyLinkedListNode(node);
}


TEST(LinkedList, InsertAndRemove) {
  LinkedList list = CreateLinkedList();
  InsertLinkedList(list, (char*)first);
  EXPECT_TRUE(list->num_elements == 1);
  EXPECT_TRUE(list->head->payload == first);
  
  InsertLinkedList(list, (char*)second);
  EXPECT_TRUE(list->num_elements == 2);
  EXPECT_TRUE(list->head->payload == second);
  
  InsertLinkedList(list, (char*)third);

  RemoveLLElem(list, list->head);
  EXPECT_TRUE(list->num_elements == 2);
  EXPECT_TRUE(list->head->payload == second);
  
  RemoveLLElem(list, list->tail);
  EXPECT_TRUE(list->num_elements == 1);
  EXPECT_TRUE(list->head->payload == second);

  InsertLinkedList(list, (char*)first);
  InsertLinkedList(list, (char*)third);
  RemoveLLElem(list, list->head->next);
  EXPECT_TRUE(list->num_elements == 2);
  EXPECT_TRUE(list->head->payload == third);
  EXPECT_TRUE(list->tail->payload == second);
  
  DestroyLinkedList(list);
}
 

TEST(LinkedList, Pop) {
  LinkedList list = CreateLinkedList();
  InsertLinkedList(list, (char*)first);
  InsertLinkedList(list, (char*)second);

  char** dataPtr = (char**)malloc(sizeof(char*));
  LinkedListNode* node = list->head;
  PopLinkedList(list, dataPtr);
  EXPECT_EQ(0, strcmp(*dataPtr, (char*)second));
  
  DestroyLinkedList(list);
  free(*dataPtr);
  free(dataPtr);
  DestroyLinkedListNode(node);
}

TEST(LLIter, Create) {
  LinkedList list = CreateLinkedList();
  InsertLinkedList(list, (char*)first);
  InsertLinkedList(list, (char*)second);
  LLIter iter = CreateLLIter(list);
  EXPECT_TRUE(list->head == iter->cur_node);
  EXPECT_TRUE(list == iter->list);

  DestroyLinkedList(list);
  DestroyLLIter(iter);
}

TEST(LLIter, HasPrevNext) {
  LinkedList list = CreateLinkedList();
  InsertLinkedList(list, (char*)first);
  InsertLinkedList(list, (char*)second);
  
  LLIter iter = CreateLLIter(list);

  EXPECT_TRUE(LLIterHasPrev(iter) == 0);
  EXPECT_TRUE(LLIterHasNext(iter) == 1);
  
  DestroyLinkedList(list);
  DestroyLLIter(iter);
}

TEST(LLIter, PrevNext) {
  LinkedList list = CreateLinkedList();
  InsertLinkedList(list, (char*)first);
  InsertLinkedList(list, (char*)second);
  LLIter iter = CreateLLIter(list);

  EXPECT_TRUE(LLIterPrev(iter) == 1);
  EXPECT_TRUE(LLIterNext(iter) == 0);
  EXPECT_TRUE(iter->cur_node->payload == (char*)first);

  DestroyLinkedList(list);
  DestroyLLIter(iter);
}

TEST(LLIter, Get) {
  LinkedList list = CreateLinkedList();
  InsertLinkedList(list, (char*)first);
  InsertLinkedList(list, (char*)second);
  LLIter iter = CreateLLIter(list);
  
  LLIterNext(iter);
  char** payload = (char**)malloc(sizeof(char*));
  LLIterGetPayload(iter, payload);
  
  EXPECT_EQ(0, strcmp(*payload, (char*)first));

  DestroyLinkedList(list);
  DestroyLLIter(iter);
  free(*payload);
  free(payload);
}

TEST(LLIter, Delete) {
  LinkedList list = CreateLinkedList();
  InsertLinkedList(list, (char*)first);
  InsertLinkedList(list, (char*)second);
  LLIter iter = CreateLLIter(list);

  EXPECT_TRUE(LLIterDelete(iter) == 0);

  EXPECT_TRUE(iter->list->num_elements == 1);
  EXPECT_TRUE(iter->list->head->payload == (char*)first);
  EXPECT_TRUE(iter->cur_node->payload == (char*)first);
  
  DestroyLinkedList(list);
  DestroyLLIter(iter);
}

TEST(LLIter, Insert) {
  LinkedList list = CreateLinkedList();
  InsertLinkedList(list, (char*)first);
  InsertLinkedList(list, (char*)second);
  LLIter iter = CreateLLIter(list);

  LLIterInsertBefore(iter, (char*)third);
  EXPECT_TRUE(iter->list->num_elements == 3);
  EXPECT_TRUE(iter->cur_node->payload == (char*)second);
  LLIterPrev(iter);
  EXPECT_TRUE(iter->cur_node->payload == (char*)third);

  DestroyLinkedList(list);
  DestroyLLIter(iter);
}

// ----------------------------------------- TESTS------------------------------------------//

TEST(contains, givenEmptyListThenReturnsFalse) {
    ll_node n1 = {strdup("test"), NULL, NULL};
    ll_head l1 = {1, &n1, &n1};
    char* searchStr = strdup("test");
    EXPECT_TRUE(contains(&l1, searchStr));
    free(searchStr);
    free(n1.payload);
}

TEST(CreateLinkedList, givenNoInputWhenCreatingListThenSizeIsZero) {
  LinkedList list = CreateLinkedList();
  EXPECT_TRUE(list->num_elements == 0);

  DestroyLinkedList(list);
}

TEST(CreateLinkedList, givenNoInputWhenCreatingListThenHeadAndTailAreNull) {
    LinkedList list = CreateLinkedList();
    EXPECT_TRUE(list->head == NULL);
    EXPECT_TRUE(list->tail == NULL);

    DestroyLinkedList(list);
}

TEST(InsertLinkedList, givenNonNullStringWhenInsertedThenStringIsInList){
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);
    int hasString = contains(list, testString);
    EXPECT_EQ(hasString, 1);

    free(testString);
    DestroyLinkedList(list);
}

TEST(InsertLinkedList, givenNonNullStringWhenInsertedThenStringHead){
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);

    LinkedListNodePtr head = list->head;
    EXPECT_EQ(0, strcmp(testString, head->payload));

    LinkedListNodePtr tail = list->tail;
    EXPECT_EQ(0, strcmp(testString, tail->payload));

    free(testString);
    DestroyLinkedList(list);
}

TEST(RemoveLLElem, givenNonNullStringWhenRemovedThenStringIsNotInList) {
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);
    //assert list->num_elements == 1
    char* toDelete = strdup("test");
    LinkedListNodePtr node = CreateLinkedListNode(toDelete);
    RemoveLLElem(list, node);
    int hasString = contains(list, testString);
    EXPECT_EQ(hasString, 0);
    EXPECT_EQ(list->num_elements, 0);

    free(testString);
    free(toDelete);
    
    DestroyLinkedListNode(node);
    DestroyLinkedList(list);
}

TEST(EmptyListHasNullHeadAndTell, givenEmptyListWhenInsertAndRemoveThenHeadAndTailAreNull) {
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);
    LinkedListNodePtr node = list->head;
    RemoveLLElem(list, node);

    EXPECT_EQ(list->head, nullptr);
    EXPECT_EQ(list->tail, nullptr);

    free(testString);
    DestroyLinkedList(list);
}


TEST(NumElementsInLinkedList, givenEmptyListThenNumElementsIsZero) {
    LinkedList list = CreateLinkedList();
    int size = NumElementsInLinkedList(list);
    EXPECT_EQ(size, 0);
    DestroyLinkedList(list);
}

TEST(NumElementsInLinkedList, givenListWithSingleNodeThenNumElementsIsOne) {
    LinkedList list = CreateLinkedList();
    char* test = strdup("test");
    InsertLinkedList(list, test);
    int size = NumElementsInLinkedList(list);
    EXPECT_EQ(size, 1);

    free(test);
    DestroyLinkedList(list);
}

TEST(NumElementsInLinkedList, givenListWith_N_NodeThenNumElementsIsN) {
    LinkedList list = CreateLinkedList();
    char* test = strdup("test");
    InsertLinkedList(list, test);
    InsertLinkedList(list, test);
    InsertLinkedList(list, test);

    int size = NumElementsInLinkedList(list);
    EXPECT_EQ(size, 3);

    free(test);
    DestroyLinkedList(list);
}

TEST(PopLinkedList, givenEmptyListWhenPoppedThenReturnsTheInputDataPtr) {
    LinkedList list = CreateLinkedList();
    char* str = strdup("");
    char** buffer = &str;

    char** ref = buffer;

    PopLinkedList(list, buffer);
    EXPECT_EQ(ref, buffer);

    free(str);
    DestroyLinkedList(list);
}

TEST(PopLinkedList, givenNonEmptyListWhenPoppedThenDoesNotReturnTheInputDataPtr) {
    LinkedList list = CreateLinkedList();
    char* test = strdup("test");
    InsertLinkedList(list, test);
    LinkedListNodePtr node = list->head;
    char* str;
    char** buffer = &str;
    EXPECT_EQ(list->num_elements, 1);
    PopLinkedList(list, buffer);
    EXPECT_EQ(0, strcmp(test, *buffer));
    EXPECT_EQ(list->num_elements, 0);
    EXPECT_TRUE(list->head == NULL);

    free(test);
    free(str);
    DestroyLinkedListNode(node);
    DestroyLinkedList(list);
}

TEST(PopLinkedList, givenListWithMultipleItemsWhenPoppedThenDoesNotReturnTheInputDataPtr) {
    LinkedList list = CreateLinkedList();
    char* test = strdup("test");
    InsertLinkedList(list, test);
    char* test2 = strdup("test2");
    InsertLinkedList(list, test2);
    LinkedListNodePtr node = list->head;
    char* str;
    char** buffer = &str;
    EXPECT_EQ(list->num_elements, 2);
    PopLinkedList(list, buffer);
    EXPECT_EQ(0, strcmp(test2, *buffer));
    EXPECT_EQ(0, strcmp(list->head->payload, test));
    EXPECT_EQ(list->num_elements, 1);

    free(test);
    free(test2);
    free(str);
    DestroyLinkedListNode(node);
    DestroyLinkedList(list);
}

TEST(TestIterator, givenValidListTestIteratorOnEmptyList) {
    LinkedList list = CreateLinkedList();
    LLIter iter = CreateLLIter(list);
    EXPECT_NE(iter, nullptr);
    EXPECT_EQ(LLIterHasNext(iter), 0);
    EXPECT_EQ(LLIterHasPrev(iter), 0);

    DestroyLinkedList(list);
    DestroyLLIter(iter);
}

TEST(Test_Iterator, givenValidListTestIteratorOnListWithSingleValue) {
    LinkedList list = CreateLinkedList();
    char* testString = strdup("test");
    InsertLinkedList(list, testString);

    LLIter iter = CreateLLIter(list);
    EXPECT_NE(iter, nullptr);
    EXPECT_EQ(LLIterHasNext(iter), 0);
    EXPECT_EQ(LLIterHasPrev(iter), 0);

    free(testString);
    DestroyLinkedList(list);
    DestroyLLIter(iter);
}

TEST(Test_Iterator, givenValidListTestIteratorOnListWithMultipleValues) {
    LinkedList list = CreateLinkedList();
    char* testString1 = strdup("test1");
    char* testString2 = strdup("test2");
    InsertLinkedList(list, testString1);
    InsertLinkedList(list, testString2);

    LLIter iter = CreateLLIter(list);
    EXPECT_NE(iter, nullptr);
    EXPECT_EQ(LLIterHasNext(iter), 1);
    EXPECT_EQ(LLIterHasPrev(iter), 0);

    LLIterNext(iter);

    EXPECT_EQ(LLIterHasNext(iter), 0);
    EXPECT_EQ(LLIterHasPrev(iter), 1);

    LLIterPrev(iter);

    EXPECT_EQ(LLIterHasNext(iter), 1);
    EXPECT_EQ(LLIterHasPrev(iter), 0);

    char* str = NULL;
    char** data = &str;

    LLIterGetPayload(iter, data);

    EXPECT_STRNE(testString1, *data);

    free(testString1);
    free(testString2);
    free(str);

    DestroyLinkedList(list);
    DestroyLLIter(iter);
}

TEST(Test_Sort, sort) {
    LinkedList list = CreateLinkedList();
    char* testString1 = strdup("test1");
    char* testString2 = strdup("apple");
    InsertLinkedList(list, testString1);
    InsertLinkedList(list, testString2);
    SortLinkedList(list, 0);
    EXPECT_TRUE(strcmp(testString1, list->head->payload) == 0);
    SortLinkedList(list, 1);
    EXPECT_TRUE(strcmp(testString2, list->head->payload) == 0);

    free(testString1);
    free(testString2);
    DestroyLinkedList(list);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}