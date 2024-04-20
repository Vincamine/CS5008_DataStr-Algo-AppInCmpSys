#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#define MAXARGS 5
#define MAXLINE 8192

// TODO: Put your command names here
char* commands[3] = {"cd", "help", "exit", "game"};

//void* cd(char* input) {
int cd(char* input) {
  printf("input is %s",input);

  
  char* asString = (char*)input;
  // TODO: Implement cd
  if(input[1] == NULL){
    chdir(getenc("HOME"));
    return 1;
  } else {
    if(chdir(input[1] == -1)){
      printf("%s: no such directory\n", input[1]);

      return -1;
    }
    return 0;
  }
  
  
}

// TODO: Put your command function pointers here
//void* (*command_functions[1])(void*) = {cd};
int (*command_functions[]) (char **) = {
  &cd;
  &help;
  &exit;
}


/***
 **  Wrapper of fork(). Checks for fork errors, quits on error. 
 **/
pid_t Fork(void) {
  pid_t pid;  
  if ((pid = fork()) < 0) {
    fprintf(stderr, "%s: %s\n", "fork error", strerror(errno));
    exit(0);
  }
  return pid;
}

/***
 **  Wrapper of fgets. Checks and quits on Unix error. 
 **/
char* Fgets(char *ptr, int n, FILE *stream) {
  char *rptr;
  if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
    //fprintf(stdout)
    fprintf(stderr, "%s\n", "fgets error");
    exit(0);
  }
  return rptr;
}

// Is the command one built into the shell?
// That is, that the *shell* has implemented?
// If so, execute it here
int builtin_command(char** argv) {
//   for (int i = 0; i < MAXARGS; i++) {
//     printf("%s\n", argv[i]);
//   }
  // Loop through
  // write loop to get the "right" i
  
  for(int i = 0;  i < sizeof(commands) / sizeof(commands[0]); i++){
    //int res = strcmp(commands[i], argv[0]);
    if (strcmp(commands[i], argv[0]) == 0) {
      // call the right function.
      (command_functions[i])(argv[0]); // some argument
      return 1;
    }
  }
  return 0;
}



void eval(char *cmdline) {
  char *argv[MAXARGS]; /* Argument list execve() */
  char buf[MAXLINE]; /* Holds modified command line */
  pid_t pid; /* Process id */

  strcpy(buf, cmdline);
  // Split buf into args
  
  char * token = strtok(buf, " \n");

  int i = 0;
  while(token != 0 && i < MAXARGS -1){  //not <=, cause save a position for NULL
    //argv[i] = token;  //not change buffer
    argv[i] = (char*)malloc(sizeof(char)* strlen(token+1));  //*
    strcpy(argv[i], token);  //*

    token = strtok(0, " \n\t");
    i++;
  }
  argv[i] = NULL;

  if (argv[0] == NULL)
    return; /* Ignore empty lines */

  if (!builtin_command(argv)) {  //my builtin not terminal
    //write: arvg[0] = "/bin/" + argv[0];
    size_t new_size = strlen("/bin/") + strlen(argv[0]) + 1;
    char *new_argv = (char *)malloc(new_size);
    if(new_argv == NULL){
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    snprintf(new_argv, new_size, "/bin/%s", argv[0]);
    // back to the problem of strtok.
    // 1234 5678 99
    // argv[0] = buffer[0], argv[1] = buffer[5], argv[2] = buffer[10]
    //need to rectify how to save tokens in while(token != 0 && i < MAXARGS -1{}
    strcpy(argv[0], new_argv);
    
    for (int k = 0; k < MAXARGS; k++) {
      if (argv[k] == NULL) break;
      printf("argv[%d]: %s\n", k, argv[k]);
    }
    
    // Check that the command/program exists in Unix (ie /bin/) OR (see below) 
    // Create a child process 
    // Run the program/command (execve...)-- what is the result of exec if the command is bogus?
    //printf("new_argv is %s\n", new_argv);

    printf("-----\n");
    for (int i = 0; i < MAXARGS; i++) {
      if (argv[i] == NULL) break;
      printf("argv[%d]: %s\n", i, argv[i]);
    }

    int res = execve(argv[0], argv, NULL); // see run_ls.c for an example
    //printf("new_argv is %s\n", new_argv);
    printf("new_argv[0] is %s\n", argv[0]);
    if (res < 0) {
      //print error message
      printf("%s", "res should less than 0");
    }

  } else {
    // What do we do if it *IS* a command built into the shell?
    if(fork() == 0){
      printf("3\n");
      execve(argv[0], argv, NULL);
      printf("4\n");
      exit(1);
    } else {
      printf("1\n");
      wait(NULL);
      printf("2\n");
    }
    
  }
  
  
  // TODO: Be sure to wait for the child process to terminate
  wait(NULL);
  return;
}

int main() {
  char cmdline[MAXLINE]; /* command line buffer */
  while (1) {
    // Print command prompt
    printf("> ");
    // Read input from user
    Fgets(cmdline, MAXLINE, stdin);
    //printf("%s", cmdline);
    // If we get the eof, quit the program/shell
    if (feof(stdin)) {
        printf("END oF FILE\n");  //ctrl+D
        exit(0);
    }

    // Otherwise, evaluate the input and execute. 
    eval(cmdline);
  }
}