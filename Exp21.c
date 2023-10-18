#include <stdio.h>

#define MEMORY_SIZE 100
#define MAX_PROCESS 10

int memory[MEMORY_SIZE];
int processSize[MAX_PROCESS];
int processAllocated[MAX_PROCESS];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0; // Initialize all memory locations to 0
    }
}

void worstFit(int n) {
    for (int i = 0; i < n; i++) {
        int worstBlockSize = -1;
        int worstBlockIndex = -1;

        for (int j = 0; j < MEMORY_SIZE; j++) {
            int blockSize = 0;
            while (j < MEMORY_SIZE && memory[j] == 0) {
                blockSize++;
                j++;
            }

            if (blockSize > worstBlockSize) {
                worstBlockSize = blockSize;
                worstBlockIndex = j - blockSize;
            }
        }

        if (worstBlockIndex != -1 && worstBlockSize >= processSize[i]) {
            for (int j = worstBlockIndex; j < worstBlockIndex + processSize[i]; j++) {
                memory[j] = i + 1;
            }
            processAllocated[i] = worstBlockIndex;
        } else {
            processAllocated[i] = -1; // Process could not be allocated
        }
    }
}

void displayMemory() {
    printf("Memory Allocation:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] == 0) {
            printf("- ");
        } else {
            printf("%d ", memory[i]);
        }
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    initializeMemory();
    worstFit(n);

    printf("\nMemory after worst fit allocation:\n");
    displayMemory();

    printf("\nProcess Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (processAllocated[i] != -1) {
            printf("Process %d is allocated at position %d\n", i + 1, processAllocated[i]);
        } else {
            printf("Process %d could not be allocated\n", i + 1);
        }
    }

    return 0;
}

