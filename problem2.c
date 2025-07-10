/* Write a C program to create an orphan process. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        printf("Parent process:\n");    
        printf("My PID: %d\n", getpid());
        printf("My Parent PID: %d\n", getppid());
        sleep(20);
        printf("Parent process exiting...\n");
        exit(EXIT_SUCCESS);
    } else {
        // Child process
        printf("Child process (before orphan):\n");
        printf("My PID: %d\n", getpid());
        printf("My Parent PID: %d\n", getppid());
        sleep(50);  // Ensure parent exits before child runs this
        printf("Child process (after orphan):\n");
        printf("My PID: %d\n", getpid());
        printf("My Parent PID: %d\n", getppid());  // This will be 1 or systemd PID
    }

    exit(EXIT_SUCCESS);
}
