#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int a[5];

void display(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("Element[%d]: %d, Address: %p\n", i, a[i], &a[i]);
    }
}

void update(int *a, int as, int n){
    for (int i = 0; i < as; i++)
           a[i] += n;
           
}

int main() {
    int i;
    printf("enter 5 elements : ");
    for (i = 0; i < 5; i++)
    scanf("%d", &a[i]);

    // Creating child process
    pid_t cpid = fork();

    if (cpid == 0) {
        // Child process
        printf("\nChild Process:\n");
        printf("Child pid: %d\n", getpid());
        printf("Parent pid: %d\n", getppid());

        update(a,5,2);

        printf("\nChild Process elements:\n");
        display(a, 5);

        int max = a[0];
        for (i = 1; i < 5; i++) {
            if (a[i] > max) {
                max = a[i];
            }
        }
        printf("\nChild Process max element: %d\n", max);
    } else if (cpid > 0) {
        // Parent process
        printf("\nParent Process:\n");
        printf("Parent pid: %d\n", getpid());
        printf("Child pid: %d\n", cpid);

        update(a,5,-3);

        printf("\nParent Process elements:\n");
        display(a, 5);

        int min = a[0];
        for (i = 1; i < 5; i++) {
            if (a[i] < min) {
                min = a[i];
            }
        }
        printf("\nParent Process min element: %d\n", min);
    } else {
        // Forking failed
        fprintf(stderr, "Forking failed!!!\n");
        return 1;
    }

    return 0;
}