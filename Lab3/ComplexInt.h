#ifndef COMPLEXINT_H
#define COMPLEXINT_H

typedef struct ComplexInt{
    int value; 
    int* data;
}ComplexInt_t;

void createComplexInt(ComplexInt_t* integer);  //use pointer

#endif