/*
Write a C program to show how data inconsistency arises in a multi-threaded
process.
*/
#include <stdio.h>
#include <pthread.h>

int count = 0; // Shared variable

void* increment1(void* arg) {
    for (int i = 0; i < 10; i++) {
        count++; // No synchronization
        printf("Thread 1: count = %d\n", count);
    }
    return NULL;
}

void* decrement1(void* arg) {
    for (int i = 0; i < 10; i++) {
        count--; // No synchronization
        printf("Thread 2: count = %d\n", count);
    }
    return NULL;
}



int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment1, NULL);
    pthread_create(&t2, NULL, decrement1, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final count: %d\n", count);

    return 0;
}
