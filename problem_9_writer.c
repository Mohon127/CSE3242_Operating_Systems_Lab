#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> 

int main(){
    char buffer[80];
    char *msg = "Type a message for sending reader: ";
  
    write(1, msg, strlen(msg)); // Write to stdout
    read(0, buffer, sizeof(buffer)); // Read from stdin
    

    //Open nammed pipe in read mode
    char *named_pipe_path = "/home/mohon/temp/named_pipe"; // Path to the named pipe
    int fd;
    fd = open(named_pipe_path, O_WRONLY); // Open named pipe in write mode
    if( fd < 0){
        perror("Error opening named pipe");
        exit(EXIT_FAILURE);
    }
    write(fd, buffer, strlen(buffer)); // Write to the named pipe
    close(fd); // Close the file descriptor



    exit(EXIT_SUCCESS); // Exit the process
}