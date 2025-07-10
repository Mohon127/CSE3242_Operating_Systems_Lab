#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define SHM_KEY 1234
#define SEM_NAME "/my_named_sem"

int main() {
    // Create or get shared memory
    int shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    int *shared_val = (int *)shmat(shmid, NULL, 0);
    if (shared_val == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    // Open or create named semaphore
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Do work with synchronization
    for (int i = 0; i < 20; i++) {
        sem_wait(sem); // Lock
        (*shared_val)++;
        printf("PID %d updated value to %d\n", getpid(), *shared_val);
        sem_post(sem); // Unlock
        usleep(100000); // 100ms
    }

    // Detach shared memory
    shmdt(shared_val);

    // Close semaphore 
    sem_close(sem);

    return 0;
}
