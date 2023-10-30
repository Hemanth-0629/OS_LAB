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
    int work[NUM_RESOURCES];
    int finish[NUM_PROCESSES];

    // Initialize work and finish arrays
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = AVAILABLE[i];
    }
    for (int i = 0; i < NUM_PROCESSES; i++) {
        finish[i] = 0;
    }

    // Check if the request can be granted
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > NEED[process][i] || request[i] > work[i]) {
            return false;
        }
    }

    // Simulate the request
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] -= request[i];
        ALLOCATION[process][i] += request[i];
        NEED[process][i] -= request[i];
    }

    // Check if the system is in a safe state
    while (1) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < NUM_RESOURCES; j++) {
                    if (NEED[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == NUM_RESOURCES) {
                    for (int k = 0; k < NUM_RESOURCES; k++) {
                        work[k] += ALLOCATION[i][k];
                    }
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    // If all processes finish, it's safe
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            return false;
        }
    }

    return true;
}

void grant_request(int process, int request[NUM_RESOURCES]) {
    // Grant the request and update matrices
    for (int i = 0; i < NUM_RESOURCES; i++) {
        AVAILABLE[i] -= request[i];
        ALLOCATION[process][i] += request[i];
        NEED[process][i] -= request[i];
    }
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
        printf("Enter the request for process P%d (%d values separated  by spaces): ", process, NUM_RESOURCES);
        for (int j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &request[j]);
        }

        if (request_is_safe(process, request)) {
            // Grant the request and update matrices
            grant_request( process, request );
            printf("SAFE - Request granted. Updated matrices.\n");
        } else {
            printf ("UNSAFE - Request denied.\n");
        }
    }

    return 0;
}
