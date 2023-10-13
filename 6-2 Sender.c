#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 100  // Size of the shared memory segment

// Function to create or get the shared memory segment
int createSharedMemory() {
    key_t key = ftok("shared_memory_key", 65);  // Create a unique key
    int shmid;

    // Create a shared memory segment or get an existing one
    if ((shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    return shmid;
}

// Function to attach the shared memory segment
char *attachSharedMemory(int shmid) {
    // Attach the shared memory segment
    char *shmaddr = shmat(shmid, (void *)0, 0);
    if (shmaddr == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    return shmaddr;
}

// Function to write data to shared memory
void writeToSharedMemory(char *shmaddr, const char *message) {
    // Write data to shared memory
    strncpy(shmaddr, message, SHM_SIZE);
}

// Function to detach and remove the shared memory segment
void cleanupSharedMemory(int shmid, char *shmaddr) {
    // Detach the shared memory segment
    shmdt(shmaddr);

    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);
}

int main() {
    int shmid = createSharedMemory();
    char *shmaddr = attachSharedMemory(shmid);

    // Write data to shared memory
    const char *message = "this is from CS21B2039";
    writeToSharedMemory(shmaddr, message);

    // Wait for Receiver to read and write
    sleep(5);

    // Read data written by Receiver
    printf("Sender Received: %s\n", shmaddr);

    // Detach and remove the shared memory segment
    cleanupSharedMemory(shmid, shmaddr);

    return 0;
}