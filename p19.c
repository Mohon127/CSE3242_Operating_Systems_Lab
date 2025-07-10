/*
Write a C program for creating a multi-threaded process and check: 

A. If one thread in the process calls fork(), does the new process 
duplicate all threads, or is the new process single-threaded? 
B. If a thread invokes the exec() system call, does it replace the entire 
code of the process? 
C. If exec() is called immediately after forking, will all threads be 
duplicated?
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

void* threadA_func(void* arg) {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child from fork(): only one thread exists here\n");
        exit(0);
    } else {
        printf("Parent after fork()\n");
    }
   
}
void* threadB_func(void* arg) {
    printf("Thread calling exec()\n");
    execl("./hello_program", "hello_program", NULL); // Custom Hello World program
    perror("exec failed");
    
}

void* threadC_func(void* arg) {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child after fork(), now calling exec()\n");
        execl("./hello_program", "hello_program", NULL);
        perror("exec failed");
        exit(1);
    } else {
        printf("Parent after fork from thread C\n");
    }
    
}

int main() {
    pthread_t tA, tB, tC;

    pthread_create(&tA, NULL, threadA_func, NULL);
    pthread_join(tA, NULL); // Case A

    

    pthread_create(&tC, NULL, threadC_func, NULL);
    pthread_join(tC, NULL); // Case C

    pthread_create(&tB, NULL, threadB_func, NULL);
    pthread_join(tB, NULL); // Case B — may not return if exec succeeds

  
}
