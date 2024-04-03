//A Binary Search Tree is a tree where given a node `N`, `N.left` is less than N
//and N.right is greater than N.
//    3
//   / \
//  1   5
//    /   \
//   4     6
// the above is a valid bst.
// the below is not.
//    3
//   / \
//  1   2
//    /   \
//   4     6

//You're given a simple implementation of a BinaryTree. Write code that does the following:

//Q1. Implement the function `isBST(tree) => boolean`. `isBst` takes as argument a tree
//and returns true if it is a BST, false otherwise.
//Q2. Implement the function `findNumsBelow(bst, num) => int[]`. FindNum traverses a BST and returns
//all values less than num in an array.

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <limits.h>

typedef struct Node {
  int value;
  struct Node* left;
  struct Node* right;
}Node;

typedef struct Tree {
  Node* root;
  int size;
}Tree;

bool isBstHelper(Node* node, int minVal, int maxVal){
  if(node == NULL){
    return true;
  }
  if(node->value <= minVal || node->value >= maxVal){
    return false;
  }
  return isBstHelper(node->left, minVal, node->value) && isBstHelper(node->right, node->value, maxVal);
}

bool isBst(Tree* t) {
  //implement me
  return isBstHelper(t->root, INT_MIN, INT_MAX);
}

void findNumsBelowHelper(Node* node, int num, int** array, int* size, int* capacity) {
  if (node == NULL) return;

  findNumsBelowHelper(node->left, num, array, size, capacity);

  if (node->value < num) {
    if (*size == *capacity) {
      *capacity *= 2;
      *array = (int*)realloc(*array, (*capacity + 1) * sizeof(int));
      if (*array == NULL) {
          perror("Failed to reallocate memory");
          exit(EXIT_FAILURE);
      }      
    }
    //(*array)[(*size)++] = node->value;
    (*array)[(*size) + 1] = node->value;
    (*size)++; 
  }
  findNumsBelowHelper(node->right, num, array, size, capacity);
}

int* findNumsBelow(Tree* t, int num) {
  if(!isBst(t)) {
    printf("error: tree given is not a bst");
    return NULL;
  }

  //implement me
  int* resultArray = (int*)malloc(sizeof(int) * 2);
  if (resultArray == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  int size = 0;
  int capacity = 1;

  findNumsBelowHelper(t->root, num, &resultArray, &size, &capacity);

  resultArray = (int*)realloc(resultArray, (size + 1) * sizeof(int));
  if (resultArray == NULL && size > 0) {
      perror("Failed to reallocate memory");
      exit(EXIT_FAILURE);
    }
  resultArray[0] = size;
  return resultArray;
}

void printNodeRecursive(Node* n) {
  if(n == NULL) return;
  printf("%d\n", n->value);
  printNodeRecursive(n->left);
  printNodeRecursive(n->right);
}

void printTree(Tree* t) {
  printNodeRecursive(t->root);
}

Node* createNode(int value) {
  Node* n1 = (Node*)malloc(sizeof(Node));
  n1->value = value;
  n1->left = NULL;
  n1->right = NULL;
  return n1;
}

Tree* createTree(Node* root) {
  Tree* t = (Tree*)malloc(sizeof(Tree));
  t->root = root;
  t->size = 1;
  return t;
}

Tree* getTestBst() {
  Node* n1 = createNode(10);
  Node* n2 = createNode(6);
  Node* n3 = createNode(13);
  Node* n4 = createNode(7);
  Node* n5 = createNode(5);

  n1->left = n2;
  n1->right = n3;
  n2->right = n4;
  n2->left = n5;

  Tree* t = createTree(n1);
  return t;
}

int main() {

//Here to make sure everything compiles.  Feel free to ignore.
  Node* n1 = createNode(10);
  n1->left = createNode(1);
  n1->right = createNode(11);
  Tree* t = createTree(n1);
  printTree(t);

  printf("------\n");
  Tree* t2 = getTestBst();
  printTree(t2);
  bool answer = isBst(t2);
  printf("here: %u", answer);

  int* resultArray = findNumsBelow(t2, 11);

    if (resultArray != NULL) {
      int resultSize = resultArray[0];
      printf("Numbers in BST less than 11:\n");
      for (int i = 1; i <= resultSize; i++) { 
        printf("%d\n", resultArray[i]);
      }
      free(resultArray);
    }

  return 0;
}