#include <stdio.h>

void printThreeTimesV1(void);
void printThreeTimesV2(void);

int main() {
    printf("Use a for loop:\n");
    printThreeTimesV1();
    printf("\nUse a single printf:\n");
    printThreeTimesV2();
    return 0;
}

void PrintThreeVictories() {
    for (int i = 0; i < 3; i++) {
        printf("VICTORY!\n");
    }
}

void PrintThreeVictoriesInOne() {
    printf("VICTORY!\nVICTORY!\nVICTORY!\n");
}