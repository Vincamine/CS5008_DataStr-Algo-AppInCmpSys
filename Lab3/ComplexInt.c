#include <stdio.h>
#include <stdlib.h>
#include "ComplexInt.h"

ComplexInt_t integer1;

void createComplexInt(ComplexInt_t* integer){
    integer->data = (int*)malloc(10 * sizeof(int));
    if(integer->data == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    printf("%d\n", integer->value); 
    printf("%p\n", &(integer->data));
    free(integer->data);
    integer->data = NULL;

}

int main(){
    ComplexInt_t integer1;
    scanf("%d",&integer1.value);
    createComplexInt(&integer1);
    return 0;
}