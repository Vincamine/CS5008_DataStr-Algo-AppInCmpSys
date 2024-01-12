#include <stdio.h> //<--- include or import statement

int main() { //<---- program entry point
    for(int count=1; count < 11; count++){
        char string[20]= "Hello, World!";
        printf("%s\n", string);
    } 
    return 0;
}