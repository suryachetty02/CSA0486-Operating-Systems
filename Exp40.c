#include <stdio.h>
#include <sys/stat.h>

int main() {
    // Define the file path and the desired permissions
    const char *filepath = "example.txt";
    mode_t permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // Read and write for owner, read for group and others

    // Set the file permissions using chmod
    if (chmod(filepath, permissions) == 0) {
        printf("File permissions set successfully.\n");
    } else {
        perror("chmod");
        return 1;
    }

    // Display the file permissions
    struct stat fileStat;
    if (stat(filepath, &fileStat) == 0) {
        printf("File permissions: %o\n", fileStat.st_mode & 0777);
    } else {
        perror("stat");
        return 1;
    }

    return 0;
}
