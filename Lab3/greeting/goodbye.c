#include <stdio.h>
#include "user.h"

void InformalGoodbye(User* user){
    printf("Bye %s!\n", user->firstName);
}; 

void FormalGoodbye(User* user){
    printf("Goodbye human %s %s!\n", user->firstName, user->lastName);
};
