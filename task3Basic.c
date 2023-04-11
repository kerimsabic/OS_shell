#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
     

int main() {
    pid_t pid;
    pid = fork(); // Create a child process

    if (pid == 0) // Child process
                        // exec() system call is used to replace the current process image with a new process image
                        // exec() system call is used in the child process to replace its memory image with a new 
                        //process image. The new program runs independently of the parent process, and any changes made 
                        //to the child process's memory space will not be reflected in the parent process's memory space.
    {
        char *args[] = {"ls", "-l", NULL};
        if (execvp(args[0], args) < 0) {
            perror("exec failed");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0){ // Parent process
        printf("Hello from the parent process!\n");
        waitpid(pid, NULL, 0); // Wait for child process to finish
    }
    else if (pid < 0) { // Fork failed
        printf("Fork failed.\n");
        return 1;
    }

    return 0;
}

/*
->fork() is a system call in Linux that creates a new process by duplicating the calling process. 
The new process is called the child process, and the original process is called the parent process.
When fork() is called, a new process is created that is identical to the parent process in almost every way. 
This includes the contents of memory, the state of all file descriptors, and the program counter. However, the child process gets its own unique process ID (PID),
and it has its own copy of variables and data structures that are used by the process.
->wait() is used by a parent process to wait for its child process to terminate. When a child process terminates, it sends a signal to its parent process to inform 
it of its exit status. The wait() system call allows the parent process to retrieve this exit status and continue its own execution.
->exec() is used to replace the current process image with a new process image. It is often used to execute a new program within the context of the current process.
When exec() is called, the current process is replaced with the new process specified in the arguments to the exec() function.
The wait() system call blocks the execution of the parent process until one of its child processes terminates. If the parent process has multiple child processes, 
it can use the waitpid() system call to wait for a specific child process to terminate.

*/
