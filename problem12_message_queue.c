// Inter-Process Communication using Message Queue in C
// Description: This program demonstrates the use of System V message queues for inter-process communication in C.
// It creates a message queue, forks a child process, and sends a message from the child to the parent process.
// The parent process waits for the message and then prints it out. Finally, it cleans up the message queue.


#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Create a message queue
    key_t key = ftok("message_queue.c", 24); 
    //printf("Key : %d\n", key);

    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msg_queue {
        long type;
        char text[80];
    } msg;
   
    

    pid_t pid = fork();

    if (pid == -1) {  // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        msg.type = 1;  // Child sends message of type 1
        
        char *prompt = "Child: Enter a message to send to parent: ";
        write(1, prompt, strlen(prompt));  // Write prompt to stdout
        read(0, msg.text, sizeof(msg.text));

        // Send the message
        if (msgsnd(msqid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }

    } else { // Parent process
        int status;
        wait(&status);  // Wait for the child to finish


        // Receive the message
        if (msgrcv(msqid, &msg, sizeof(msg.text), 1, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }

        printf("Parent received: %s\n", msg.text);

        // Remove the message queue
        if (msgctl(msqid, IPC_RMID, 0) == -1) {
            perror("msgctl failed");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
