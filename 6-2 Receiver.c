#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

// Function to create or get the shared memory segment
int createSharedMemorySegment() {
    key_t key = ftok("shared_memory_key", 65);
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    return shmid;
}

// Function to attach the shared memory segment
char *attachSharedMemorySegment(int shmid) {
    char *shared_memory = (char *)shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        perror("shmat");
        exit(1);
    }
    return shared_memory;
}

// Function to read data from shared memory
void readDataFromSharedMemory(char *shared_memory) {
    printf("Receiver: Received data from Sender CS21B2039: %s\n", shared_memory);
}

// Function to write data to shared memory
void writeDataToSharedMemory(char *shared_memory, const char *response) {
    strncpy(shared_memory, response, SHM_SIZE);
    printf("Receiver: Wrote data to shared memory: %s\n", response);
}

// Function to detach shared memory
void detachSharedMemorySegment(char *shared_memory) {
    shmdt(shared_memory);
}

int main() {
    int shmid = createSharedMemorySegment();
    char *shared_memory = attachSharedMemorySegment(shmid);

    // Reading data from shared memory
    readDataFromSharedMemory(shared_memory);

    // Writing data to shared memory
    char response[] = "Receiver: Data received!";
    writeDataToSharedMemory(shared_memory, response);

    // Detaching shared memory
    detachSharedMemorySegment(shared_memory);

    return 0;
}