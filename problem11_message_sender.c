#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

struct msg_queue {
    long type;
    char text[80];
};

int main() {
    key_t key = ftok("test.c", 65); 

    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msg_queue msg;
    msg.type = 1;

    char *prompt = "Enter a message to send: ";
    write(1, prompt, strlen(prompt));  // Write prompt to stdout

    // Read user input from stdin (file descriptor 0)
    read(0, msg.text, sizeof(msg.text));


    // Send message to queue
    if (msgsnd(msqid, &msg, strlen(msg.text), 0) == -1) {
        perror("msgsnd failed");
        exit(EXIT_FAILURE);
    }

    write(1, "Message sent successfully.\n", 28);

    return 0;
}
