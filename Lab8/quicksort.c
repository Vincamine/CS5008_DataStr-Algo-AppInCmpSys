#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int num_partition_calls = 0;
int num_quicksort_calls = 0;
int num_comparisons = 0; 

void Swap(int* array, int ind1, int ind2) {
  int tmp = array[ind1];
  array[ind1] = array[ind2];
  array[ind2] = tmp;
}


int Partition(int* data, int low, int high) {
  num_partition_calls++; 
  int pivot = data[low];
  int leftwall = low;
  int i;
  for (i = low + 1; i <= high; i++) {
  	num_comparisons++;
    if (data[i] < pivot) {
      leftwall++;
      Swap(data, i, leftwall); 
    }
  }
  Swap(data, low, leftwall);
  return leftwall;
}

void Quicksort(int* data, int low, int high) {
  num_quicksort_calls++;
  if (low < high) {
    int pivot_location = Partition(data, low, high);
    Quicksort(data, low, pivot_location);
    Quicksort(data, pivot_location+1, high);
  }
}

void PrintArray(int* array, int num_elems) {
  int i;
  printf("[");
  for (i = 0; i < num_elems; i++) {
    printf("%d ", array[i]);
  }
  printf("]\n");
}

int CheckArray(int* array, int num_elems) {
  int i;
  for (i = 1; i < num_elems; i++) {
    if (array[i] < array[i - 1]) {
      printf("NOT SORTED!!!\n");
      return 0;
    }
  }
  printf("SORTED!!\n");
  return 1;
}

// int main() {
  
//   int num_elems = 32;
//   int* integers = (int*)malloc(sizeof(int) * num_elems);

//   time_t t;
//   srand(42); // (unsigned)time(&t));

//   int i;
//   for (i = 0; i < num_elems; i++) {
//     integers[i] = (rand() % 90) + 10;
//   }

//   PrintArray(integers, num_elems);
//   Quicksort(integers, 0, num_elems - 1);
//   printf("\n\n");
//   PrintArray(integers, num_elems);
//   CheckArray(integers, num_elems);

//   free(integers);
  

//   printf("num partition calls: %d\n", num_partition_calls);
//   printf("Num quicksort calls: %d\n", num_quicksort_calls);
//   printf("Num comparisons calls: %d\n", num_comparisons);
  
// }
