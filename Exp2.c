#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Open the source file for reading
    int source_fd = open("source.txt", O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(1);
    }

    // Open the destination file for writing (create if it doesn't exist, truncate if it does)
    int dest_fd = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        exit(1);
    }

    char buffer[4096];
    ssize_t bytes_read, bytes_written;

    // Copy content from source to destination
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Write error");
            exit(1);
        }
    }

    if (bytes_read == -1) {
        perror("Read error");
        exit(1);
    }

    // Close the files
    close(source_fd);
    close(dest_fd);

    printf("File copy completed successfully.\n");

    return 0;
}

