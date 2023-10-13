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
    message.msg_type = 1;

    printf("enter the number(s):\n");

    // Read input numbers from the user
    fgets(message.msg_text, sizeof(message.msg_text), stdin);

    // Send the message
    msgsnd(msgid, &message, sizeof(message), 0);

    printf("Data sent to Receiver: %s\n", message.msg_text);

    // Sleep for a while to allow the Receiver to process
    sleep(2);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}