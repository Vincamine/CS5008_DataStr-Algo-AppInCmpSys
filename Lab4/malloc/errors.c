#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node {
  Node* nextNode; 
};


int main() {

  int stringLength = 7;
  int *stringOnHeap = (int*) malloc((sizeof(int) * (stringLength + 1)));

  Node* foo;

  foo->nextNode = 4; 
  
  
  stringOnHeap[0] = 'e';
  stringOnHeap[1] = 'x';
  stringOnHeap[2] = 'a';
  stringOnHeap[3] = 'm';
  stringOnHeap[4] = 'p';
  stringOnHeap[5] = 'l';
  stringOnHeap[6] = 'e';
  stringOnHeap[7] = '\0';

  printf("%d\n", stringOnHeap);

  free(stringOnHeap);
  
  return 0;
}
