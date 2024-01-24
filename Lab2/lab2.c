#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int array1[100]; // This array holds strictly integers.
unsigned int array2[100]; // This array holds strictly unsigned ints.
float array3[100]; // This array holds strictly floats.


/* statically allocated arrays */
int numbers[10];	// 'numbers' is large enough to store exactly 10 integers.
char firstName[15];	// 'firstName' stores up to 15 char's
float piDigits[5000];	// 'piDigits' holds 3.1415....well, up to 5000 digits.

/* Declaring the array */
int a[50];          /* array of 50 ints */
char *cp[100];      /* array of 100 pointers to char */

/* Initializing the Array */
int n[ 10 ] = { 32, 27, 64, 18, 95, 14, 90, 70, 60, 37 };
// int n[ 10 ] = { 0 };


/* Arrays and functions */
int sumNumbers(int num1, int num2) {
    return num1 + num2;
}
int sumArray(int n, const int *a) {
    int i;
    int sum;

    sum = 0;
    for(i = 0; i < n; i++) {
        sum += a[i];
    }

    return sum;
}


/**
 * Write a function that replaces all numbers greater
 * than ceiling in arr with ceiling.
 *
 * Precondition(s):
 * - len > 0 (i.e. arrays MUST have at least one element)
 *
 * Example(s):
 * - crop_hi([1, 2, 3, 4], 4, 2) :: [1, 2, 2, 2]
 * - crop_hi([-3, 17,  7, -12, 10], 5, 8) :: [-3, 8, 7, -12, 8]
 *
 * @param arr     array of integers
 * @param len     length of arr
 * @param ceiling upper limit for ints in array
 */
void crop_hi(int* arr, int len, int ceiling) {
    //implement your code here
    if(len > 0){
        for(int i = 0; i < len; i++){
            if(arr[i] > ceiling){
                arr[i] = ceiling;
            }
        }
        printf("Modified array of crop_hi(): ");
        printf("[");
        for(int i = 0; i < len; i++){
            printf("%d", arr[i]);
            if(i < len-1){
                printf(",");
            }
        }
        printf("]\n");
    }
    else{
        printf("arrays MUST have at least one element\n");
    }

}


/**
 * Swaps the the last int in arr with the middle element in arr.
 *
 * Precondition(s):
 * - len > 0 (i.e. arrays MUST have at least one element)
 *
 * Example(s):
 * - swap_mid_back([1, 2, 3], 3) :: [1, 3, 2]
 * - swap_mid_back([-4, 3, 0, 1], 4) :: [-4, 1, 0, 3]
 *
 * @param arr array of integers
 * @param len length of arr
 */
void swap_mid_back(int* arr, int len){
    //implement your code here
    if(len > 0){
        int save_last = arr[len-1];
        arr[len-1] = arr[(len - 1) / 2];
        arr[(len - 1) / 2] = save_last;
        printf("array of swap_mid_back() is: ");
        printf("[");
        for (int i = 0; i < len; i++){
            printf("%d",arr[i]);
            if(i < len-1){
                printf(",");
            }
        }
        printf("]\n");
        
    }
    else{
        printf("arrays MUST have at least one element\n");
    }
}

/**
 * Replaces all digits in a string with a '*'. 
 *
 *
 * Example(s):
 * - redact("The part failed 58% of the time") ::
 *          "The part failed **% of the time"
 * - redact("There were 13 As in the class") :: "There were ** As in the class"
 *
 * @param  str     host string for old_char
 */
void redact(char* str){
    //implement your code here
    for(int i = 0; str[i] != '\0'; i++){
        if(isdigit(str[i])){
            str[i] = '*';
        }
    }
    printf("Redacted String: %s\n", str);
}

/**
 * Compares two integer arrays and tests for equality
 */
bool equalArrays(int* arr1, int size1, int* arr2, int size2) {
    if(size1 != size2) return 0;
    bool res = true;
    int i;
    for(i=0; i <size1; i++) {
        res = res && arr1[i] == arr2[i];
    }
    return res;
}

void testEqualArrays() {
    int arr1[] = {1,2,3,4};
    int arr2[] = {1,2,3,4};
    int arr3[] = {4,3,2,1};
    //printf("test1: %d\n", equalArrays(arr1, 4, arr2, 4));
    //printf("test2: %d\n", equalArrays(arr1, 3, arr2, 4));
    //printf("test3: %d\n", equalArrays(arr1, 4, arr3, 4));
}

int main() {
    testEqualArrays();
    int array1[] = {1, 2, 3, 4};
    crop_hi(array1, 4, 2);
    int array2[] = {-3, 17, 7, -12, 10};
    crop_hi(array2, 5, 8);
    int array3[]= {1, 2, 3};
    int array4[]= {-4, 3, 0, 1};
    swap_mid_back(array3, 3);
    swap_mid_back(array4, 4);
    char chars1[]= "The part failed 58% of the time";
    redact(chars1);
    char chars2[] = "There were 13 As in the class"; 
    redact(chars2);

    return 0;
}