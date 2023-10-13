#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo_path = "myfifo";
    int fd;
    int receivedValue;

    mkfifo(fifo_path, 0666); // Create the named pipe (FIFO) if it doesn't exist

    fd = open(fifo_path, O_WRONLY); // Open the FIFO for writing
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int originalValue = 8; // Message to be sent

    if (write(fd, &originalValue, sizeof(int)) == -1) { // Write the message to the FIFO
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Sender: Sent %d to Receiver\n", originalValue);
    close(fd); // Close the FIFO

    fd = open(fifo_path, O_RDONLY); // Reopen the FIFO for reading

    if (read(fd, &receivedValue, sizeof(int)) == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Sender: Received %d from Receiver\n", receivedValue);
    close(fd);

    return 0;
}
