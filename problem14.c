#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(){
	// Shared memory pointer and loop variable
	int *shmaddr;
	int i;

	// Create a shared memory segment
	int shmid;
	key_t key = 5678;
	shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	if(shmid == -1){
		perror("shmget: ");
		exit(EXIT_FAILURE);	
	}
	
	// Create a child process
	pid_t pid;
	pid = fork(); 
	if(pid == -1){
		perror("fork: ");
		exit(EXIT_FAILURE);
	}
	
	if(pid == 0){ // Child process
		shmaddr = shmat(shmid, NULL, 0);
		if(shmaddr == (int*) -1){
			perror("shmat (child): ");
			exit(EXIT_FAILURE);
		}
		
		for(i = 0; i < 10; i++){
			printf("Child before write: shared_var = %d\n", *shmaddr);
			*shmaddr = 100;
			printf("Child after  write: shared_var = %d\n", *shmaddr);
		}
		
		if(shmdt(shmaddr) == -1){
			perror("shmdt (child): ");
			exit(EXIT_FAILURE);		
		}		
	}
	else{ // Parent process
		shmaddr = shmat(shmid, NULL, 0);
		if(shmaddr == (int*) -1){
			perror("shmat (parent): ");
			exit(EXIT_FAILURE);
		}
		
		for(i = 0; i < 10; i++){
			printf("Parent before write: shared_var = %d\n", *shmaddr);
			*shmaddr = 999;
			printf("Parent after  write: shared_var = %d\n", *shmaddr);
		}
		
		int status;
		wait(&status);
		
		printf("Parent final read   : shared_var = %d\n", *shmaddr);
		
		if(shmdt(shmaddr) == -1){
			perror("shmdt (parent): ");
			exit(EXIT_FAILURE);		
		}	
		
		if(shmctl(shmid, IPC_RMID, NULL) == -1){
			perror("shmctl: ");
			exit(EXIT_FAILURE);
		}
	}
	
	exit(EXIT_SUCCESS);
}
