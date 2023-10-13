#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define the message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a unique key for the message queue
    key = ftok("Sender.c", 65);

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive the message from the sender
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    printf("Received data from Sender: %s\n", message.msg_text);

    // Count and display odd numbers
    int oddCount = 0;
    char *token = strtok(message.msg_text, " ");
    while (token != NULL) {
        int num = atoi(token);
        if (num % 2 != 0) {
            printf("%d is odd\n", num);
            oddCount++;
        }
        token = strtok(NULL, " ");
    }

    printf("Total no.of odd numbers received: %d\n", oddCount);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}