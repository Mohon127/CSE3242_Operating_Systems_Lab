#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> 

int main() {
    char buffer[80];

    // Open named pipe in read mode
    char *named_pipe_path = "/home/mohon/temp/named_pipe"; // Path to the named pipe
    int fd;
    fd = open(named_pipe_path, O_RDONLY); // Open named pipe in read mode
    if (fd < 0) {
        perror("Error opening named pipe");
        exit(EXIT_FAILURE);
    }

    
    // Print the received message
    char *msg = "Received message: ";

    read(fd , buffer, sizeof(buffer)); // Read from the named pipe
    write(1, msg, strlen(msg)); 
    write(1, buffer, strlen(buffer)); 

    close(fd); // Close the file descriptor

    exit(EXIT_SUCCESS); // Exit the process
}
