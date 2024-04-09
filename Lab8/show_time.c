/* Program to demonstrate time taken by function fun() */
#include <stdio.h> 
#include <time.h> 
#include <unistd.h>     // for sleep()
#include <sys/time.h>   // for gettimeofday()
#include "quicksort.h"
#include <stdlib.h>


// A function that terminates when enter key is pressed 
void fun() 
{ 
    printf("fun() starts \n"); 
    printf("Press enter to stop fun \n"); 
    while(1) 
    { 
        if (getchar()) 
            break; 
    } 
    printf("fun() ends \n"); 
} 

void report_time(){
  int num_elems[] = {16,32,64,128,256,512,1024,2048};
  
  int* integers = (int*)malloc(sizeof(int) * num_elems[7]);

  time_t t;
  srand(42); // (unsigned)time(&t));

  
  for(int i = 0; i < sizeof(num_elems) / sizeof(num_elems[0]); i++){
    for (int j = 0; j < num_elems[i]; j++) {
        integers[j] = (rand() % 90) + 10;
    }
    //PrintArray(integers, num_elems);

    struct timeval begin, end;
    gettimeofday(&begin, NULL);

    Quicksort(integers, 0, num_elems[i]-1);

    gettimeofday(&end, NULL);
    long seconds = (end.tv_sec - begin.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (begin.tv_usec);

    //CheckArray(num_elems, integers);
    //PrintArray(num_elems, integers);
    
    printf("Time elpased is %ld seconds and %ld micros\n", seconds, micros);
  }
  

  free(integers);

}

// The main program calls fun() and measures time taken by fun() 
int main() 
{
    report_time();
    // struct timeval begin, end;
    // gettimeofday(&begin, NULL);
    // //do some stuff here

    
    // //fun();
    // gettimeofday(&end, NULL);
    // long seconds = (end.tv_sec - begin.tv_sec);
    // long micros = ((seconds * 1000000) + end.tv_usec) - (begin.tv_usec);
    // printf("Time elpased is %ld seconds and %ld micros\n", seconds, micros);


    // Report time taken by Quicksort to sort the array
    //report_time(arr);

    return 0; 
} 
