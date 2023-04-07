# OSProjekat-Shell
Group Members: Kerim Šabić, Amina Merić

List of files within this submission:
  1. shell.c
  2. shell (compiled)
  3. task3Basic.c 
  4. task3Basic (compiled)
  5. task3Intermediate.c 
  6. task3Intermediate (compiled)
  6. task3Additionally.c
  7. task2Additionally (compiled)
  8. docs.txt (used for testing)
  9. docs2.txt (used for testing)
  10. docs3.txt (used for testing)
  
Q1: What does the mmap() function do?

The mmap() function is a system call in Unix-like operating systems that allows a process to map a file or device into its virtual memory address space. When a file or device is mapped into memory, the operating system sets up a range of virtual memory addresses that correspond to the file/device's physical addresses. This allows the process to directly access the file/device's data from memory, without needing to perform any explicit I/O operations.
There are several benefits to using mmap(). First, it can improve performance by avoiding the need for explicit I/O operations, which can be slow and introduce overhead. Second, it allows the process to manipulate the file/device's data as if it were regular memory, which can simplify programming and reduce errors. Finally, mmap() also provides a mechanism for inter-process communication, as multiple processes can map the same file/device into their address spaces and communicate via shared memory.

Q2: What happens during a context switch? Do we want the OS to perform many or few context switches? Explain.

A context switch is the process of saving the current state of a running process and restoring the saved state of a different process, so that the CPU can switch to executing the other process. Context switches are a fundamental mechanism for multitasking, which allows multiple processes to run on a single CPU.
During a context switch, the operating system saves the state of the currently running process, including its CPU registers, program counter, and other information, into a data structure known as a process control block (PCB). It then selects a different process to run, restores the saved state of that process from its PCB, and resumes execution of the process. The time it takes to perform a context switch can be significant, especially for processes with large memory footprints, because the operating system needs to update the CPU's memory management unit (MMU) to map the process's virtual addresses to physical addresses.
While context switches are necessary for multitasking, they come with a performance cost. Therefore, it is generally desirable for the operating system to perform as few context switches as possible, in order to maximize overall system performance. This can be achieved by using scheduling algorithms that prioritize processes that are likely to make progress and avoiding unnecessary preemption, as well as by optimizing the context switch code itself to minimize overhead. However, there are some cases where more frequent context switches may be desirable, such as for real-time systems or for load balancing in distributed systems.

An outline of what we did for the assignment:
We implemented a shell using tokens- makes from one string an array of string. With this we imlemented piping which has one child process, then first parent process which takes arguments from first child process. Then parent forks again and uses it for child2. Processes communicate mutally with each other. Also we have acase that if we don't have piping then we have what will happen for only one child process.

Instructions for compiling your programs/scripts:
Our programs are already send with compile files. In case that doesn't work just write in terminal gcc -o executiablename filename.c -Wall. To run you write ./filename

Any challenges you encountered along the way:
Making this project was challenging but interesting. We needed to use boyond our knowledge and reasarch a lot which is a good thing but it was very challenging. Also, it was diffucult to find some information online, to better understand what we need to do, since there is not a lot of information online.

Any sources/tutorials you have used to complete the assignment:
Google, man page, ChatGPT, collegues help to better understand what we need to do.

