#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>

int main() {
    const char *fifo_path = "myfifo_receiver";
    int fd;
    mkfifo(fifo_path, 0666); // Create the named pipe (FIFO) if it doesn't exist

    fd = open(fifo_path, O_RDONLY); // Open the FIFO for reading
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int receivedValue; // Read the message from the FIFO
    if (read(fd, &receivedValue, sizeof(int)) == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Receiver: Received %d from Sender\n", receivedValue);

    int binaryBits[32];
    int n = receivedValue;
    int i = 0;
    while (n > 0) {
        if (n % 2 == 0)
            binaryBits[i++] = 1;
        else
            binaryBits[i++] = 0;
        n = n / 2;
    }

    int onesComplement = 0;
    for (int j = 0; j < i; j++) {
        onesComplement += pow(2, j) * binaryBits[j];
    }

    close(fd); // Close the FIFO

    fd = open(fifo_path, O_WRONLY); // Open the FIFO for writing
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (write(fd, &onesComplement, sizeof(int)) == -1) { // Write the one's complement back to the FIFO
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Receiver: Sent one's complement %d to Sender\n", onesComplement);
    close(fd); // Close the FIFO

    return 0;
}
