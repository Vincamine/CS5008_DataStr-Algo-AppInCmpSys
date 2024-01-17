#include <stdio.h>
int main(){
    // 1st way
    int i;
    char warmup[] = "VICTORY!";
    for (i = 0; i < 3; i++)
        printf("%s\n", warmup);

    // 2nd way
    printf("VICTORY!\n");
    printf("VICTORY!\n");
    printf("VICTORY!\n");

    return 0;
}