#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;
    
    // Fork a child process
    pid = fork();
    
    if (pid < 0) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        
        // Execute the "ls" command
        char *args[] = {"ls", "-l", NULL};
        if (execv("/bin/ls", args) == -1) {
            perror("execv error");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        
        // Wait for the child process to complete
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid error");
            exit(EXIT_FAILURE);
        }
        
        // Send a SIGTERM signal to the child process
        if (kill(pid, SIGTERM) == -1) {
            perror("kill error");
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;

}
/*
-> kill() is a system call in Linux that sends a signal to a process or a group of processes. 
The kill() system call takes two arguments: the process ID of the target process and the signal to be sent. kill() is often used in Unix-like systems to 
communicate with running processes. For example, a process may use kill() to send a SIGTERM signal to a child process that is misbehaving or taking too long to 
complete. The child process would then receive the signal and terminate.
-> execv() is a system call used to execute a new program within the context of the current process. It is a variant of the exec(). 
The execv() system call takes two arguments: the path of the new program to be executed and an array of pointers to null-terminated strings that 
represent the program arguments. 

*/
