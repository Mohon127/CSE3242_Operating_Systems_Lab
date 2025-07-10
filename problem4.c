/* 
Write a C program to create a main process named ‘parent_process’ having 3 
child processes without any grandchildren processes. Child Processes’ 
names are child_1, child_2, child_3. Trace the position in the process tree.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/prctl.h>

int main() {
    prctl(PR_SET_NAME, "parent_process");  // Set parent process name

    printf("Parent process started. PID: %d\n", getpid());

    char *child_names[3] = {"child_1", "child_2", "child_3"};
    pid_t pids[3];

    for (int i = 0; i < 3; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) {
            prctl(PR_SET_NAME, child_names[i]);  // Set child process name
            printf("Hello from %s, PID: %d, PPID: %d\n", child_names[i], getpid(), getppid());
            exit(EXIT_SUCCESS);  
        }
    }

    sleep(20);
    // Parent waits for all children to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent process: All child processes have finished.\n");

    exit(EXIT_SUCCESS);
}
