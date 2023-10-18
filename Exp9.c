#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 12345 // The key to identify the shared memory segment
#define SHARED_MEMORY_SIZE sizeof(int) // Size of the shared memory segment

int main() {
    int shmid;
    int *shared_value; // Pointer to the shared integer value

    // Create a shared memory segment
    shmid = shmget(SHM_KEY, SHARED_MEMORY_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    shared_value = (int *)shmat(shmid, NULL, 0);
    if ((int)shared_value == -1) {
        perror("shmat");
        exit(1);
    }

    // Producer: Write a value to the shared memory
    printf("Producer: Enter an integer value: ");
    scanf("%d", shared_value);

    // Detach the shared memory segment
    shmdt(shared_value);

    // Create a new process for the consumer
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // This code is executed by the child process (consumer)

        // Attach the shared memory segment to the child process
        shared_value = (int *)shmat(shmid, NULL, 0);
        if ((int)shared_value == -1) {
            perror("shmat");
            exit(1);
        }

        // Consumer: Read and print the value from shared memory
        printf("Consumer: Received value: %d\n", *shared_value);

        // Detach the shared memory segment
        shmdt(shared_value);
    }

    // Wait for the child process to finish
    wait(NULL);

    // Mark the shared memory segment for removal
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

