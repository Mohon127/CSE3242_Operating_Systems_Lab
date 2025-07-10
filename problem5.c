/*
Write a C program to create a main process named ‘parent_process’ having 
‘n’ child processes without any grandchildren processes. Child Processes’ 
names are child_1, child_2, child_3,......., child_n. Trace the position in the 
process tree. Number of child processes (n) and name of child processes will 
be given in the CLI of Linux based systems.  
 
Example: 
$ ./parent_process 3 child_1 child_2 child_3

*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <n> <child_1> <child_2> ... <child_n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);

    if (argc != n + 2) {
        printf("Error: You must enter %d child names.\n", n);
        exit(EXIT_FAILURE);
    }

    prctl(PR_SET_NAME, "parent_process");  // Rename main process

    printf("Parent (PID: %d) started.\n", getpid());

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // In child process
            prctl(PR_SET_NAME, argv[i + 2]);  // Set child name
            printf("Child %d — Name: %s, PID: %d, PPID: %d\n",
                   i + 1, argv[i + 2], getpid(), getppid());
            exit(EXIT_SUCCESS);  // No grandchildren
        }
    }

    sleep(20);  // Allow children to run for a while

    // Parent waits for all children
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Parent done. All %d children finished.\n", n);
    exit(EXIT_SUCCESS);
}
