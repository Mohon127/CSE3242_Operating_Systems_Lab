/* Write a C program to create a zombie process.  */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>



int main() {

    int pid;

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // child process
        printf("Child process (PID: %d) created. Exiting...\n", getpid());
        // Child exits immediately, creating a zombie process
        exit(EXIT_SUCCESS);
    } else { // parent process
        printf("Parent process (PID: %d) created child with PID: %d\n", getpid(), pid);
        // Parent sleeps to allow the child to become a zombie
        sleep(30); 
        printf("Parent process exiting...\n");

    }



    exit(EXIT_SUCCESS);




    
}
