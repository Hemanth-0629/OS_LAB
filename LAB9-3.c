#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphoreX, semaphoreY;

void* threadX(void* arg) {
    // Statement X1 (formerly A1)
    printf("Statement X1\n");

    // Signal Thread Y to continue
    sem_post(&semaphoreY);

    // Wait for Thread Y to complete Statement Y2 (formerly B2)
    sem_wait(&semaphoreX);

    // Statement X2 (formerly A2)
    printf("Statement X2\n");

    // Signal Thread Y to continue
    sem_post(&semaphoreY);

    pthread_exit(NULL);
}

void* threadY(void* arg) {
    // Statement Y1 (formerly B1)
    printf("Statement Y1\n");

    // Signal Thread X to continue
    sem_post(&semaphoreX);

    // Wait for Thread X to complete Statement X2 (formerly A2)
    sem_wait(&semaphoreY);

    // Statement Y2 (formerly B2)
    printf("Statement Y2\n");

    // Signal Thread X to continue
    sem_post(&semaphoreX);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread_X, thread_Y;

    sem_init(&semaphoreX, 0, 0);
    sem_init(&semaphoreY, 0, 0);

    // Create Thread X and Thread Y
    pthread_create(&thread_X, NULL, threadX, NULL);
    pthread_create(&thread_Y, NULL, threadY, NULL);

    // Wait for both threads to finish
    pthread_join(thread_X, NULL);
    pthread_join(thread_Y, NULL);

    // Clean up the semaphores
    sem_destroy(&semaphoreX);
    sem_destroy(&semaphoreY);

    return 0;
}
