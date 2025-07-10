#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int a = 10, b = 5;  // Variables initialized in the parent process
    pid_t pid1, pid2, pid3;

    printf("Parent Process (PID: %d): Starting with values a = %d, b = %d\n", getpid(), a, b);

    // First child - addition
    pid1 = fork();
    if (pid1 == 0) {
        printf("Child 1 (PID: %d, PPID: %d): Doing addition: %d + %d = %d\n", getpid(), getppid(), a, b, a + b);
        exit(EXIT_SUCCESS);  // Child exits
    }

    // Second child - subtraction
    pid2 = fork();
    if (pid2 == 0) {
        printf("Child 2 (PID: %d, PPID: %d): Doing subtraction: %d - %d = %d\n", getpid(), getppid(), a, b, a - b);
        exit(EXIT_SUCCESS);  // Child exits
    }

    // Third child - multiplication
    pid3 = fork();
    if (pid3 == 0) {
        printf("Child 3 (PID: %d, PPID: %d): Doing multiplication: %d * %d = %d\n", getpid(), getppid(), a, b, a * b);
        exit(EXIT_SUCCESS);  // Child exits
    }

    // Parent process waits for all children
    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent Process (PID: %d): All child processes completed.\n", getpid());

    exit(EXIT_SUCCESS);
}
