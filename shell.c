#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <sys/wait.h>

#define RED "\033[0;31m"                               //colors declaration
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

#define MAX_ARGS 10
#define COMMAND_SIZE 100

int main(){
    char input[COMMAND_SIZE];                           //for user input
    char *arguments[MAX_ARGS];
    char *commandFirst[MAX_ARGS];
    char *commandSecond[MAX_ARGS];
    char machineName[COMMAND_SIZE];                               //machine name that is read is stored here
    char *login = getlogin();                                    //for login
    gethostname(machineName, COMMAND_SIZE);                   //for getting the machine name 

    while (1){
    printf(MAGENTA"%s@%s\033[0m"CYAN":~$ \033[0m", machineName, login);
    fgets(input, COMMAND_SIZE, stdin);
    input[strlen(input) - 1] = '\0';  

    if(strcmp(input, "") == 0) {
      continue;
    }

    //tokenization
    char *token = strtok(input, " ");
    int i = 0;
    while(token != NULL && i < MAX_ARGS) {
      arguments[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    arguments[i]=NULL;        //last element always has to be null for execvp()

    int a = 0;
    int confrim1= 0;
    while(arguments[a] != NULL) {          
      if(strcmp(arguments[a], "|") == 0) {      //when it comes to | it will set confirm1=1, meaning we will use this variable to see whether it will be piping or not
        confrim1= 1;
        break;
      }
      a++;
    }

    if(confrim1) {                             //if confirm 1 is 1 meaning that we will have piping later on we will call it, so we will break up the arguments array
      int b = 0;                               //so that we will store first command in commandFirst and second command in commandSecond
      int c = 0;
      while(strcmp(arguments[b], "|")) {
        commandFirst[c] = arguments[b];
        b++;
        c++;
      }

      int d = 0;
      int e = 0;
      int confirm2= 0;
      while(arguments[d] != NULL) {            
        if(strcmp(arguments[d], "|") == 0) {           //confirm2 is 0 until we reach |
          confirm2 = 1;
        } else if(confirm2) {
          commandSecond[e] = arguments[d];           //this part is for storing commands and arguments after |
          e++;
        }
        d++;
      }
        commandFirst[c] = NULL;                      //last element has to be null because of execvp()
        commandSecond[e] = NULL;
    }
    if(strcmp(arguments[0], "leave") == 0) {
        printf(YELLOW"Goodbye i ćao\033[0m\n");
        break;
    }
    else if(strcmp(arguments[0], "name") == 0) {
        printf("Shell Name: "RED"Školjka Amine i Kerima\033[0m\n");
        continue;
    }
    else if(strcmp(arguments[0], "cowsay")==0){
      printf(" %s\n", arguments[1]);
      printf ("_______________\n");
      printf("----------------\n");
      printf ("       \\      ^__^\n");
      printf("         \\     (oo)\\_______\n");
      printf("               (__)\\        )\\/\\\n");
      printf("                   ||-----w  |\n");
      printf("                   ||       ||\n");
    }
    else if(confrim1) {
        int pipefd[2];
        pid_t pid1, pid2;          //pid_t is used for storing process id             

    pipe(pipefd);           //array pipefd is used for piping, file decriptors for reading and writing will be stored here

    pid1 = fork();

    
    if (pid1 == 0) {           //this is child one
          
        close(pipefd[0]);       //close reading end of pipe

        dup2(pipefd[1], STDOUT_FILENO);        //child process writing into writing end of pipe, instead of standard output

        execvp(commandFirst[0], commandFirst);      //exicute the first command/program
      }
      else {                                        // parent process, to make child two
        pid2 = fork();

        if (pid2 == 0) {                            //chid process 2
        
        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);        //child process reading from reading end of pipe, instead od standard input

        execvp(commandSecond[0], commandSecond);   //exicute the second command/program

        }
        else {                                    // parent process
            close(pipefd[0]);                    //Close both ends of the pipe
            close(pipefd[1]);

            waitpid(pid1, NULL, 0);               // Wait for both child processes to finish
            waitpid(pid2, NULL, 0);
          }
      }
    }
    else{                                    //for case if we don't have piping, for example if we put clear
        pid_t pid = fork();
        if (pid==0){                   //child process
            execvp(arguments[0], arguments);
            perror("Error, command not found\n");
            exit(1);
        }
        else if (pid>0){ 
            waitpid(pid, NULL, 0);
        }
    }
}
}
