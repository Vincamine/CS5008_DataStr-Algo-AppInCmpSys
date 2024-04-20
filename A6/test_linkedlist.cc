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
    #include "LinkedList.h"
    #include "Sort.h"
    #include <string.h>
    #include <stdbool.h>
}
const char* first = "first";
const char* second="second";
const char* third = "third";
const char* fourth = "fourth";

bool contains(LinkedList list, char* str) {
    LinkedListNodePtr node = list->head;
    bool res = false;
    while(node != NULL) {
        res = res || strcmp(node->payload, str) == 0;
        node = node->next;
    }
    return res;
}

#define MAX_VALUE_LEN 75

// Function to create a linked list of random integers
LinkedList CreateRandomList(int size) {
    LinkedList list = CreateLinkedList();
    srand(time(NULL)); // Seed for random number generation

    for (int i = 0; i < size; i++) {
        // Generate a random integer between 100 and 999
        int random_num = rand() % 900 + 100;

        // Allocate memory for the string
        char *data = (char *)malloc(4 * sizeof(data));
        snprintf(data, 4, "%d", random_num);
        InsertLinkedList(list, data);

        // Free memory allocated for data after insertion
        free(data);
    }

    return list;
}
// Function to print the elements of a linked list
void PrintList(LinkedList list) {
    LLIter iter = CreateLLIter(list);
    char *payload;
    for (int i = 0; i < list->num_elements; i++) {
        LLIterGetPayload(iter, &payload);
        printf("%s ", payload);
        LLIterNext(iter);
    }
    printf("\n");
    DestroyLLIter(iter);
    printf("Number of elements in the list: %llu\n", list->num_elements);
}


int IsListSortedAscending(const LinkedList* list) {\
    if ((*list)->head == NULL || (*list)->head->next == NULL) {
        return 1;
    }

    LinkedListNodePtr current = (*list)->head;
    while (current->next != NULL) {
        // Convert payload strings to integers for comparison
        int current_value = atoi(current->payload);
        int next_value = atoi(current->next->payload);

        if (current_value > next_value) {
            printf("List is not sorted in ascending order: %d > %d\n",
             current_value, next_value);
            return 0;
        }
        current = current->next;
    }
    return 1;
}

TEST(SortInsertion, testforInsertionSort) {
    LinkedList list = CreateRandomList(10);
    PrintList(list);
    SortInsertion(&list);
    PrintList(list);
    ASSERT_TRUE(IsListSortedAscending(&list));
    DestroyLinkedList(list);
}

TEST(SortSelection, testforSelectionSort) {
    LinkedList list = CreateRandomList(10);
    PrintList(list);
    SortSelection(&list);
    PrintList(list);
    ASSERT_TRUE(IsListSortedAscending(&list));
    DestroyLinkedList(list);
}


TEST(SortMerge, testforMergeSort) {
    LinkedList list = CreateRandomList(10);
    PrintList(list);
    SortMerge(&list);
    PrintList(list);
    ASSERT_TRUE(IsListSortedAscending(&list));
    DestroyLinkedList(list);
}
TEST(MergeSort, testforMergeSortFunction) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, "5");
    InsertLinkedList(list, "3");
    InsertLinkedList(list, "8");
    InsertLinkedList(list, "1");
    InsertLinkedList(list, "7");

    mergeSort(&(list->head));

    ASSERT_TRUE(IsListSortedAscending(&list));
    DestroyLinkedList(list);
}

TEST(Merge, testforMergeFunction) {
    LinkedListNode* a = CreateLinkedListNode("1");
    a->next = CreateLinkedListNode("3");
    a->next->next = CreateLinkedListNode("5");

    LinkedListNode* b = CreateLinkedListNode("2");
    b->next = CreateLinkedListNode("4");

    LinkedListNodePtr result = merge(a, b);

    LinkedList list = CreateLinkedList();

    list->head = result;
    list->num_elements = 5;

    // Verify the merged list is sorted
    ASSERT_TRUE(IsListSortedAscending(&list));

    // Check if the merged list contains all elements
    ASSERT_TRUE(contains(list, "1"));
    ASSERT_TRUE(contains(list, "2"));
    ASSERT_TRUE(contains(list, "3"));
    ASSERT_TRUE(contains(list, "4"));
    ASSERT_TRUE(contains(list, "5"));

    DestroyLinkedList(list);
}



TEST(Split, testforSplitFunction) {
    LinkedList list = CreateLinkedList();
    InsertLinkedList(list, "5");
    InsertLinkedList(list, "3");
    InsertLinkedList(list, "8");
    InsertLinkedList(list, "1");
    InsertLinkedList(list, "7");

    printf("Original List: ");
    PrintList(list);

    LinkedListNodePtr front;
    LinkedListNodePtr back;

    split(list->head, &front, &back);
    printf("Front Node: %s\n", front->payload);
    printf("Back Node: %s\n", back->payload);

    // Create LinkedList structures for front and back lists
    LinkedList frontList = CreateLinkedList();
    frontList->head = front;
    LinkedList backList= CreateLinkedList();
    backList->head = back;

    // Verify elements of the front list
    ASSERT_TRUE(contains(frontList, "7"));
    ASSERT_TRUE(contains(frontList, "1"));
    ASSERT_TRUE(contains(frontList, "8"));

    // Verify elements of the back list
    ASSERT_TRUE(contains(backList, "3"));
    ASSERT_TRUE(contains(backList, "5"));


    DestroyLinkedList(frontList);
    DestroyLinkedList(backList);
    free(list);
}

//using givenWhenThen

// TEST(contains, givenEmptyListThenReturnsFalse) {
//     ll_node n1 = {strdup("test"), NULL, NULL};
//     ll_head l1 = {1, &n1, &n1};
//     EXPECT_TRUE(contains(&l1, strdup("test")));
// }

// TEST(CreateLinkedList, givenNoInputWhenCreatingListThenSizeIsZero) {
//   LinkedList list = CreateLinkedList();
//   EXPECT_TRUE(list->num_elements == 0);
// }

// TEST(CreateLinkedList, givenNoInputWhenCreatingListThenHeadAndTailAreNull) {
//     LinkedList list = CreateLinkedList();
//     EXPECT_TRUE(list->head == NULL);
//     EXPECT_TRUE(list->tail == NULL);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
