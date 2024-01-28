#ifndef HEADER_FILE
#define HEADER_FILE

typedef struct User {
    char* firstName;
    char* lastName;
    int age;
}User;

// Greetings and goodbyes 

void StandardGreeting(User*); 
void FormalGreeting(User*); 
void InformalGoodbye(User*); 
void FormalGoodbye(User*);

#endif
