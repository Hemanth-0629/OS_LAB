#include <stdio.h>
#include <stdlib.h> // Include the <stdlib.h> header for rand
#include <stdbool.h>

#define NUM_PROCESSES 6
#define NUM_RESOURCES 4

int MAX[NUM_PROCESSES][NUM_RESOURCES];
int ALLOCATION[NUM_PROCESSES][NUM_RESOURCES];
int AVAILABLE[NUM_RESOURCES];
int NEED[NUM_PROCESSES][NUM_RESOURCES];

// Function to check if a state is safe
bool isSafe(int process, int request[]) {
    int work[NUM_RESOURCES];
    int finish[NUM_PROCESSES];

    // Temporary matrices to simulate resource allocation
    int temp_max[NUM_PROCESSES][NUM_RESOURCES];
    int temp_allocation[NUM_PROCESSES][NUM_RESOURCES];
    int temp_available[NUM_RESOURCES];

    // Initialize temporary matrices
    for (int i = 0; i < NUM_PROCESSES; i++) {
        finish[i] = 0;
        for (int j = 0; j < NUM_RESOURCES; j++) {
            temp_max[i][j] = MAX[i][j];
            temp_allocation[i][j] = ALLOCATION[i][j];
        }
    }

    // Simulate the allocation of resources
    for (int j = 0; j < NUM_RESOURCES; j++) {
        temp_available[j] -= request[j];
        temp_allocation[process][j] += request[j];
        temp_max[process][j] -= request[j];
    }

    // Check if the simulated state is safe
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            int j;
            for (j = 0; j < NUM_RESOURCES; j++) {
                if (temp_max[i][j] > temp_available[j]) {
                    break;
                }
            }
            if (j == NUM_RESOURCES) {
                finish[i] = 1;
                for (int k = 0; k < NUM_RESOURCES; k++) {
                    temp_available[k] += temp_allocation[i][k];
                }
            }
        }
    }

    // If all processes can finish, it's safe
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    // Initialize MAX and ALLOCATION matrices with random values
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            MAX[i][j] = rand() % 5 + 1;
            ALLOCATION[i][j] = rand() % MAX[i][j] + 1;
            NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
        }
    }

    // Calculate the AVAILABLE array
    for (int j = 0; j < NUM_RESOURCES; j++) {
        int total_resources = 0;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            total_resources += ALLOCATION[i][j];
        }
        AVAILABLE[j] = total_resources;
    }

    // Main loop to take user input for additional resource requests
    int process;
    while (1) {
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

        //   Check if the request is valid
        bool valid_request = true;
        for (int j = 0; j < NUM_RESOURCES; j++) {
            if (request[j] > NEED[process][j] || request[j] > AVAILABLE[j]) {
                valid_request = false;
                break;
            }
        }

        if  (valid_request && isSafe(process, request)) {
            // Grant the request and update matrices
            for (int j = 0; j < NUM_RESOURCES; j++) {
                AVAILABLE[j] -= request[j];
                ALLOCATION[process][j] += request[j];
                NEED[process][j] -= request[j];
            }
            printf("SAFE - Request granted. Updated matrices.\n");
        } else {
            printf("UNSAFE - Request denied.\n");
        }
    }

    return 0;
}
