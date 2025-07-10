#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main() {
    char *named_pipe_path = "/home/mohon/temp/named_pipe";
    char buffer[80];
    int fd;

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    else if (pid == 0) {
        // Child Process: Reader
        sleep(1); // Ensure writer has opened the pipe

        fd = open(named_pipe_path, O_RDONLY); // Open pipe in read mode
        if (fd < 0) {
            perror("Error opening named pipe");
            exit(EXIT_FAILURE);
        }

        read(fd, buffer, sizeof(buffer)); // Read message from pipe
        char *msg = "Child received: ";
        write(1, msg, strlen(msg));
        write(1, buffer, strlen(buffer));

        close(fd);
        exit(EXIT_SUCCESS);
    }

    else {
        // Parent Process: Writer
        char *prompt = "Parent: Type a message for child: ";
        write(1, prompt, strlen(prompt));
        read(0, buffer, sizeof(buffer)); // Read from stdin

        fd = open(named_pipe_path, O_WRONLY); // Open pipe in write mode
        if (fd < 0) {
            perror("Error opening named pipe");
            exit(EXIT_FAILURE);
        }

        write(fd, buffer, strlen(buffer)); // Write message to pipe
        close(fd);
        wait(NULL); // Wait for child to finish
    }

    

    return 0;
}
