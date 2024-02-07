#include<stdio.h>
#include<stdlib.h>

int main()
{
    float *p, sum = 0;
    int i, n;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    // allocate memory to store n variables of type float
    p = (float*)malloc(n * sizeof(float));

    // if dynamic allocation failed exit the program
    if (p==NULL) {
        printf("Memory allocation failed");
        exit(1); // exit the program
    }

    // ask the student to enter marks
    for(i = 0; i < n; i++)
    {
        printf("Enter marks for %d student: ", i+1);
        scanf("%f", p+i);
    }
    
    // calculate sum
    for(i = 0; i < n; i++)
    {
        sum += *(p+i);
    }

    printf("\nAverage marks = %.2f\n", sum/n);
    

    for (i = 0; i < n + 3; i++) {
      printf("%f\n", p[i]);
    }
    /*
    int foo[5];
    for (i = 0; i < 5 + 3; i++) {
      foo[i] = i;
    }
    for (i = 0; i < 5 + 3; i++) {
      printf("%d\n", foo[i]);
    }
    */
    
    // signal to operating system program ran fine

    free(p);
    
    return 0;
}
