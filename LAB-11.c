#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 6
#define NUM_RESOURCES 4

int MAX[NUM_PROCESSES][NUM_RESOURCES];
int ALLOCATION[NUM_PROCESSES][NUM_RESOURCES];
int AVAILABLE[NUM_RESOURCES];
int NEED[NUM_PROCESSES][NUM_RESOURCES];

void initialize() {
    // Initialize MAX and ALLOCATION matrices and calculate NEED matrix
    // You can set these matrices according to your scenario
}

bool request_is_safe(int process, int request[NUM_RESOURCES]) {
    // Check if the request is valid and if it leads to a safe state
    // Implement the Banker's algorithm logic here
}

void grant_request(int process, int request[NUM_RESOURCES]) {
    // Update the matrices when a request is granted
    // Implement the update logic here
}

int main() {
    initialize();

    // Main loop to take user input for additional resource requests
    while (1) {
        int process;
        printf("Enter the process (0 to 5) for additional request (or -1 to exit): ");
        scanf("%d", &process);

        if (process == -1) {
            break;
        }

        int request[NUM_RESOURCES];
        printf("Enter the request for process P%d (%d values separated by spaces): ", process, NUM_RESOURCES);
        for (int j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &request[j]);
        }

        if (request_is_safe(process, request)) {
            // Grant the request and update matrices
            grant_request(process, request);
            printf("SAFE - Request granted. Updated matrices.\n");
        } else {
            printf("UNSAFE - Request denied.\n");
        }
    }

    return 0;
}
