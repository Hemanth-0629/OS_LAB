#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void c3() {
    printf("Child 3 My id is %d and my parent id is %d.\n", getpid(), getppid());
    exit(0);
}

void c4() {
    printf("Child 4 My id is %d and my parent id is %d.\n", getpid(), getppid());
    exit(0);
}

void c2() {
    int c3_pid, c4_pid;
    c3_pid = fork();

    if (c3_pid == 0) {
        c3();
    } else {
        wait(NULL);
        c4_pid = fork();

        if (c4_pid == 0) {
            c4();
        } else {
            wait(NULL);
            printf("Child 2 My id is %d and my parent id is %d.\n", getpid(), getppid());
            exit(0);
        }
    }
}

void c1() {
    printf("Child 1 My id is %d and my parent id is %d.\n", getpid(), getppid());
    exit(0);
}

void parent_function() {
    int c1_pid;
    wait(NULL);
    c1_pid = fork();

    if (c1_pid == 0) {
        c1();
    } else {
        wait(NULL);
        printf("Parent Process my id is %d and my parent id is %d.\n", getpid(), getppid());
    }
}

int main() {
    int c2_pid = fork();
    if (c2_pid == 0) {
        c2();
    } else {
        parent_function();
    }
    return 0;
}