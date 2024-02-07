#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INITIAL_SIZE 4

typedef struct deque{
    int *array;
    int head, tail, size, capacity;
}deque;

deque* createDeque(){
    deque* newDeque = (deque*)malloc(sizeof(deque));
    if(!newDeque){return NULL;}
    else{
        newDeque->array = (int*)malloc(INITIAL_SIZE * sizeof(int));
        if(!newDeque->array){
            free(newDeque);
            return NULL;
        }
        else{
            newDeque->head = newDeque->tail = newDeque->size = 0;
            newDeque->capacity = INITIAL_SIZE;
            return newDeque;
        }
    }
}

void resizeDeque(deque* thisDeque){
    int *newArray = (int*)malloc(2 * thisDeque->capacity * sizeof(int));
    if(!newArray){return;}
    else{
        /*
        printf("head = %d\n", thisDeque->head);
        printf("tail = %d\n", thisDeque->tail);
        printf("size = %d\n", thisDeque->size);
        printf("capacity = %d\n", thisDeque->capacity);
        */
        int j = 0;
        for(int i = thisDeque->head; i != thisDeque->tail; i = (i+1) % thisDeque->capacity){
            newArray[j++] = thisDeque->array[i];
        }
        free(thisDeque->array);
        thisDeque->array = newArray;
        thisDeque->head = 0;
        thisDeque->tail = thisDeque->size;
        thisDeque->capacity *= 2;
        /*
        printf("after head = %d\n", thisDeque->head);
        printf("after tail = %d\n", thisDeque->tail);
        printf("after size = %d\n", thisDeque->size);
        printf("after capacity = %d\n", thisDeque->capacity);
        */
        
    }
}

void pushLeft(deque* thisDeque, int value){
    if(thisDeque == NULL || thisDeque->array == NULL){return;}

    if(thisDeque->size == thisDeque->capacity-1){
        resizeDeque(thisDeque);
    }
    thisDeque->head = (thisDeque->head-1 + thisDeque->capacity) % thisDeque->capacity;
    thisDeque->array[thisDeque->head] = value;
    thisDeque->size++;

}

void pushRight(deque* thisDeque, int value){
    if(thisDeque == NULL || thisDeque->array == NULL){return;}

    if(thisDeque->size == thisDeque->capacity-1){
        resizeDeque(thisDeque);
    }

    thisDeque->array[thisDeque->tail] = value;
    thisDeque->tail = (thisDeque->tail + 1) % thisDeque->capacity;
    thisDeque->size++;

}

bool isEmpty(deque* thisDeque){
    if(thisDeque == NULL || thisDeque->array == NULL || thisDeque->size == 0){ // 3 conditions!
        return true;
    }
    else{
        return false;
    }
}

void peekLeft(deque* thisDeque){
    if(thisDeque == NULL || thisDeque->array == NULL || isEmpty(thisDeque)){return;}
    int leftOf = thisDeque->array[thisDeque->head];
    printf("%d\n", leftOf);
}

void peekRight(deque* thisDeque){
    if(thisDeque == NULL || thisDeque->array == NULL || isEmpty(thisDeque)){return;} 

    // Consider the property of circular array
    // Cannot directly return $thisDeque->array[thisDeque->tail];
    int tailIndex = (thisDeque->tail - 1 + thisDeque->capacity) % thisDeque->capacity;
    int rightOf =  thisDeque->array[tailIndex];
    printf("%d\n", rightOf);
}

int popLeft(deque* thisDeque){
    if(thisDeque == NULL || thisDeque->array == NULL || isEmpty(thisDeque)){return 0;}
    int left = thisDeque->array[thisDeque->head];
    // head may out of the array boundary $thisDeque->head++;
    thisDeque->head = (thisDeque->head + 1) % thisDeque->capacity;    
    thisDeque->size--;
    return left;
}

void insertAt(deque* thisDeque){

}


int popRight(deque* thisDeque){
    if(thisDeque == NULL || thisDeque->array == NULL || isEmpty(thisDeque)){return 0;}
    thisDeque->tail = (thisDeque->tail - 1 + thisDeque->capacity) % thisDeque->capacity;
    int right = thisDeque->array[thisDeque->tail];
    thisDeque->size--;
    return right;
}

void printDeque(deque* thisDeque){
    if(thisDeque == NULL || thisDeque->array == NULL || thisDeque->size == 0){return;}
    else{
        // Index of head may bigger than index of tail
        int i = thisDeque->head;
        while(i != thisDeque->tail){
            printf("%d ", thisDeque->array[i]);
            // Ensure loop traversal
            i = (i + 1) % thisDeque->capacity;
        }
        printf("\n");
    }
}

void freeDeque(deque* thisDeque){
    // Unecessay checking "thisDeque->array == NULL || thisDeque->size == 0"
    if(thisDeque == NULL){return;}
    else{
        free(thisDeque->array);
        // Unecessary: thisDeque->head = thisDeque->tail = thisDeque->size = 0; thisDeque->capacity = INITIAL_SIZE;
        // Once free(thisDeque); these fields become inaccessible memory.
        free(thisDeque);
        // After this step, pointer "thisDeque" becomes dangling pointer.

    }
}

int main(){
    deque* myDeque = createDeque();
    pushLeft(myDeque, 10);
    pushLeft(myDeque, 9);
    pushLeft(myDeque, 8);
    pushLeft(myDeque, 7);
    pushLeft(myDeque, 6);

    pushRight(myDeque, 11);
    pushRight(myDeque, 12);
    pushRight(myDeque, 13);
    printDeque(myDeque);
    
    popLeft(myDeque);
    printDeque(myDeque);
    popRight(myDeque);
    printDeque(myDeque);

    peekLeft(myDeque);
    peekRight(myDeque);
    
    freeDeque(myDeque);
    // In C, since arguments are passed by value, changes to pointer variables inside the function do not affect pointer variables outside the function
    myDeque = NULL;

    return 0;
}