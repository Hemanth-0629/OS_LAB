#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_NUMBERS 1000

int numbers[NUM_NUMBERS];
int totalSum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* threadSum(void* arg) {
    int threadId = *((int*)arg);
    int start = threadId * (NUM_NUMBERS / NUM_THREADS);
    int end = (threadId + 1) * (NUM_NUMBERS / NUM_THREADS);


    int threadSum = 0;

    for (int i = start; i < end; i++) {
        threadSum += numbers[i];
    }

    pthread_mutex_lock(&mutex);
    totalSum += threadSum;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS];

    // Initialize the array with numbers from 1 to 1000
    for (int i = 0; i < NUM_NUMBERS; i++) {
        numbers[i] = i + 1;
    }

    // Create and start the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadSum, (void*)&threadIds[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total sum: %d\n", totalSum);

    return 0;
}
