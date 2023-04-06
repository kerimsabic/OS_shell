# OS_shell

Read pdf file 



Q1: What does the mmap() function do?

The mmap() function is a system call in Unix-like operating systems that allows a process to map a file or device into its virtual memory address space. When a file or device is mapped into memory, the operating system sets up a range of virtual memory addresses that correspond to the file/device's physical addresses. This allows the process to directly access the file/device's data from memory, without needing to perform any explicit I/O operations.

There are several benefits to using mmap(). First, it can improve performance by avoiding the need for explicit I/O operations, which can be slow and introduce overhead. Second, it allows the process to manipulate the file/device's data as if it were regular memory, which can simplify programming and reduce errors. Finally, mmap() also provides a mechanism for inter-process communication, as multiple processes can map the same file/device into their address spaces and communicate via shared memory.

Q2: What happens during a context switch? Do we want the OS to perform many or few context switches? Explain.

A context switch is the process of saving the current state of a running process and restoring the saved state of a different process, so that the CPU can switch to executing the other process. Context switches are a fundamental mechanism for multitasking, which allows multiple processes to run on a single CPU.

During a context switch, the operating system saves the state of the currently running process, including its CPU registers, program counter, and other relevant information, into a data structure known as a process control block (PCB). It then selects a different process to run, restores the saved state of that process from its PCB, and resumes execution of the process. The time it takes to perform a context switch can be significant, especially for processes with large memory footprints, because the operating system needs to update the CPU's memory management unit (MMU) to map the process's virtual addresses to physical addresses.

While context switches are necessary for multitasking, they come with a performance cost. Therefore, it is generally desirable for the operating system to perform as few context switches as possible, in order to maximize overall system performance. This can be achieved by using scheduling algorithms that prioritize processes that are likely to make progress and avoiding unnecessary preemption, as well as by optimizing the context switch code itself to minimize overhead. However, there are some cases where more frequent context switches may be desirable, such as for real-time systems or for load balancing in distributed systems.







#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t child_pid;
    int status;

    // Fork a child process
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process: PID=%d, PPID=%d\n", getpid(), getppid());

        // Execute a new program
        char *args[] = {"ls", "-l", NULL};
        execv("/bin/ls", args);

        // If execv returns, it means an error occurred
        perror("execv failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), child_pid);

        // Send a signal to the child process
        int result = kill(child_pid, SIGTERM);
        if (result == -1) {
            perror("kill failed");
            exit(1);
        }

        // Wait for the child process to terminate
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}





 printf(" ---------------\n");
	    printf("        \\   ^__^\n");
	    printf("         \\  (oo)\\_______\n");
	    printf("            (__)\\       )\\/\\\n");
	    printf("                ||----w |\n");
	    printf("                ||     ||\n");
