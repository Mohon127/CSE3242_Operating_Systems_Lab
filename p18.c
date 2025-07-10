#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME "/counter_sem"

int main() {
    // Create a counting semaphore with initial value 2 (2 resources)
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 2);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    printf("Process %d waiting for resource...\n", getpid());
    sem_wait(sem); // Try to acquire one unit

    printf("Process %d got resource!\n", getpid());
    sleep(2); // Simulate doing some work

    printf("Process %d releasing resource.\n", getpid());
    sem_post(sem); // Release the unit

    sem_close(sem); // Close the semaphore (doesn't delete it)a

    return 0;
}
