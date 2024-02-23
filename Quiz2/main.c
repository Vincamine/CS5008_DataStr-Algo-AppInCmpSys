#include<stdio.h>
#include"arraylist.h"

int main() {
    printf("hello world\n");
    ArrayList* list = create(10);
    printf("the size of the list is %d\n", list->size);

    char char1[2] = {'h', '\0'};
    char* char2 = "ehuh";

    // char* value1 = "h";
    char* value1 = char1;
    char* value2 = char2;

    add(list,value1);
    printf("test: %c\n", *value1);
    printf("value1 is: %s\n", get(list,0));

    destroyList(list);
}
