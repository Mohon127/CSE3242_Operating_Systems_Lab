 /*
Write a C program to show how two related processes can communicate with
each other by an unnamed pipe.
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sched.h>
#include <string.h>

void main(){
  pid_t pid;
  int processor_no;
  int pipe_fd[2];// Pipe Descriptor
  char buffer[80];
  
  
  pipe(pipe_fd);
  
  //Create a child
  pid = fork();
  
  if(pid < 0){
    perror("Fork");
    exit(EXIT_FAILURE);
  }else if(pid == 0){ //Child process
    pid = getpid();
    
    char *msg = "Type a message for the Parent: ";
    write(1, msg, strlen(msg));
    read(0, buffer, sizeof(buffer));
    
    //Write Child message to the pipe
    close(pipe_fd[0]); 
    write(pipe_fd[1], buffer, strlen(buffer)); 
    close(pipe_fd[1]); 
    
  }else{  //Parent Process
    
    //Read Child's message from the pipe
    close(pipe_fd[1]);
    read(pipe_fd[0], buffer, sizeof(buffer));
    close(pipe_fd[0]);
    
    char *msg = "Parent received message: ";
    write(1, msg, strlen(msg));
    write(1, buffer, strlen(buffer));
    int status;
    wait(&status);
  }
  exit(EXIT_SUCCESS);
}