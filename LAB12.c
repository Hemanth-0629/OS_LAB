#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Define semaphores
sem_t forks[NUM_PHILOSOPHERS];
sem_t eating_semaphore;

void *philosopher(void *arg) {
    int philosopher_id = *(int *)arg;
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", philosopher_id);
        sleep(1);

        // Acquire eating_semaphore (limits two philosophers eating simultaneously)
        sem_wait(&eating_semaphore);

        // Acquire left fork
        sem_wait(&forks[left_fork]);
        printf("Philosopher %d has acquired the left fork (%d).\n", philosopher_id, left_fork);

        // Acquire right fork
        sem_wait(&forks[right_fork]);
        printf("Philosopher %d has acquired the right fork (%d).\n", philosopher_id, right_fork);

        // Eating
        printf("Philosopher %d is eating.\n", philosopher_id);
        sleep(2); // Simulate eating

        // Release right fork
        sem_post(&forks[right_fork]);
        printf("Philosopher %d has released the right fork (%d).\n", philosopher_id, right_fork);

        // Release left fork
        sem_post(&forks[left_fork]);
        printf("Philosopher %d has released the left fork (%d).\n", philosopher_id, left_fork);

        // Release eating_semaphore
        sem_post(&eating_semaphore);
    }
    return NULL;
}

int main() {
    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&eating_semaphore, 0, 2);

    // Create philosopher threads
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish (this will never happen as they run forever)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}



