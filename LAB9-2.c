#include <stdio.h>
#include <pthread.h>

#define MATRIX_SIZE 3

int M1[MATRIX_SIZE][MATRIX_SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int M2[MATRIX_SIZE][MATRIX_SIZE] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int A[MATRIX_SIZE][MATRIX_SIZE];
int S[MATRIX_SIZE][MATRIX_SIZE];
int M[MATRIX_SIZE][MATRIX_SIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* matrixOperation(void* arg) {
    int operation = *((int*)arg);
    
    switch (operation) {
        case 0: // Addition
            for (int i = 0; i < MATRIX_SIZE; i++) {
                for (int j = 0; j < MATRIX_SIZE; j++) {
                    pthread_mutex_lock(&mutex);
                    A[i][j] = M1[i][j] + M2[i][j];
                    pthread_mutex_unlock(&mutex);
                }
            }
            break;

        case 1: // Subtraction
            for (int i = 0; i < MATRIX_SIZE; i++) {
                for (int j = 0; j < MATRIX_SIZE; j++) {
                    pthread_mutex_lock(&mutex);
                    S[i][j] = M1[i][j] - M2[i][j];
                    pthread_mutex_unlock(&mutex);
                }
            }
            break;

        case 2: // Multiplication
            for (int i = 0; i < MATRIX_SIZE; i++) {
                for (int j = 0; j < MATRIX_SIZE; j++) {
                    M[i][j] = 0;
                    for (int k = 0; k < MATRIX_SIZE; k++) {
                        pthread_mutex_lock(&mutex);
                        M[i][j] += M1[i][k] * M2[k][j];
                        pthread_mutex_unlock(&mutex);
                    }
                }
            }
            break;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int additionOp = 0, subtractionOp = 1, multiplicationOp = 2;

    pthread_create(&threads[0], NULL, matrixOperation, &additionOp);
    pthread_create(&threads[1], NULL, matrixOperation, &subtractionOp);
    pthread_create(&threads[2], NULL, matrixOperation, &multiplicationOp);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Matrix M1:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", M1[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix M2:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", M2[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix Addition (A):\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix Subtraction (S):\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", S[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix Multiplication (M):\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    return 0;
}
