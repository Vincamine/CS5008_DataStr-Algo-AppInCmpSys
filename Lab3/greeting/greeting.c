#include <stdio.h>
#include "user.h"

void StandardGreeting(User* user){
    printf("Hi %s %s!\n", user->firstName, user->lastName);
}; 

void FormalGreeting(User* user){
    printf("Hello %s %s! How are you!\n", user->firstName, user->lastName);
}; 
