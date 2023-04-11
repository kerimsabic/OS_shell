#include <unistd.lib>

void forkbomb() {
   while (1) {
       fork();    // create a new child process
   }
}

int main() {
   forkbomb();
   return 0;
}


//do not run this code since it may lead to system crash!!!
/*
A "fork bomb" is a type of denial-of-service attack that can be executed on a Linux or Unix-based operating system.
In a fork bomb attack, the attacker creates a process that rapidly replicates itself by calling the system function "fork()".
Each new process also calls "fork()" and creates more processes,
and this continues until the system is overwhelmed and can no longer function properly.
*/


/*
Since each new process takes up system resources such as memory and CPU time,
a fork bomb can quickly consume all available resources on a system and cause it to crash
or become unresponsive.
It's important to note that forkbomb() is a dangerous command and should not be used unless you have
a legitimate need to test or analyze its effects. Otherwise, it can cause serious damage to the system and disrupt normal operation.
*/


//The following characters comprise a basic Linux shell script used to launch a fork bomb:
//:(){ :|: & };:
/*
:() -> Defined the bash function called;
{ : |: &} -> Body of the function,  :|: -> call the function and pipe the output to the same function , & -> send process to background
; -> end of statement
: -> Run the function
*/

