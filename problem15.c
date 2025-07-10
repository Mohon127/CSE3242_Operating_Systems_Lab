#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

#define SHM_KEY 1234

int main() {
    int *shmaddr;
    int shmid;
    int i;

    // Create or get shared memory
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write to shared memory
    for (i = 0; i < 100; i++) {
        printf("Before write: shared_var = %d\n", *shmaddr);
        (*shmaddr )++;  // Write random value
        usleep(100000);            // Small delay to allow overlap
        printf("After  write: shared_var = %d\n", *shmaddr);
    }

    // Detach from shared memory
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == 0) {
        printf("Shared memory segment deleted.\n");
    }

    exit(EXIT_SUCCESS);
}


