#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int average;
int minimum;
int maximum;

int *numbers;
int count;

// Function to calculate average
void* calc_average(void* arg) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    average = sum / count;
    pthread_exit(NULL);
}

// Function to find minimum
void* calc_minimum(void* arg) {
    minimum = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] < minimum)
            minimum = numbers[i];
    }
    pthread_exit(NULL);
}

// Function to find maximum
void* calc_maximum(void* arg) {
    maximum = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] > maximum)
            maximum = numbers[i];
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s num1 num2 ...\n", argv[0]);
        return 1;
    }

    count = argc - 1;
    numbers = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    pthread_t tid1, tid2, tid3;

    // Create threads
    pthread_create(&tid1, NULL, calc_average, NULL);
    pthread_create(&tid2, NULL, calc_minimum, NULL);
    pthread_create(&tid3, NULL, calc_maximum, NULL);

    // Wait for threads to complete
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // Output results
    printf("The average value is %d\n", average);
    printf("The minimum value is %d\n", minimum);
    printf("The maximum value is %d\n", maximum);

    free(numbers);
    return 0;
}
