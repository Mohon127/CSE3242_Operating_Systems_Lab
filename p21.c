#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int fib[100];   
int n;          

void* generate_fib(void* arg) {
    fib[0] = 0;
    if (n > 1)
        fib[1] = 1;

    for (int i = 2; i < n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./fib_thread <number_of_terms>\n");
        return 1;
    }

    n = atoi(argv[1]);
    if (n < 0) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    pthread_t t1;

    pthread_create(&t1, NULL, generate_fib, NULL);
    pthread_join(t1, NULL);  // Wait for child thread to finish

    printf("Fibonacci sequence up to %d terms:\n", n);
    for (int i = 0; i < n; i++)
        printf("%d ", fib[i]);

    printf("\n");
    return 0;
}
