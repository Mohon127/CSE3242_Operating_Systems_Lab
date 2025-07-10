#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct msg_queue {
    long type;
    char text[80];
};

int main() {
    key_t key = ftok("test.c", 65); // Must match the sender's key

    if (key == -1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    int msqid = msgget(key, 0666);
    if (msqid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct msg_queue msg;

    if (msgrcv(msqid, &msg, sizeof(msg.text), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(EXIT_FAILURE);
    }

    printf("Received message: %s", msg.text);

    // Optionally remove the queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl (remove queue) failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
