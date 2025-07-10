/*
Write a C program to analyze the effect of local and global variables on a
parent process and a child process.
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int global_var = 10; // Global variable

int main() {
    int local_var = 20; // Local variable

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        global_var += 5;
        local_var += 5;
        printf("Child process:\n");
        printf("  global_var = %d\n", global_var);
        printf("  local_var  = %d\n", local_var);
    } else {
        // Parent process waits for child to finish
        wait(NULL);
        printf("Parent process:\n");
        printf("  global_var = %d\n", global_var);
        printf("  local_var  = %d\n", local_var);
    }

    exit(EXIT_SUCCESS);
}
