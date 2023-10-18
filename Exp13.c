#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

// Structure to represent a memory block
struct MemoryBlock {
    int size;
    int allocated;
};

// Function to initialize the memory with a specified size
void initializeMemory(struct MemoryBlock memory[], int size) {
    memory[0].size = size;
    memory[0].allocated = 0;
}

// Function to display the current state of memory
void displayMemory(struct MemoryBlock memory[], int numBlocks) {
    printf("Memory Status:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: Size = %d, Allocated = %d\n", i, memory[i].size, memory[i].allocated);
    }
    printf("\n");
}

// First Fit Allocation
int firstFit(struct MemoryBlock memory[], int numBlocks, int requestSize) {
    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize) {
            memory[i].allocated = 1;
            return i;
        }
    }
    return -1; // No suitable block found
}

// Best Fit Allocation
int bestFit(struct MemoryBlock memory[], int numBlocks, int requestSize) {
    int bestFitIndex = -1;
    int bestFitSize = MEMORY_SIZE;

    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize && memory[i].size < bestFitSize) {
            bestFitIndex = i;
            bestFitSize = memory[i].size;
        }
    }

    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = 1;
    }

    return bestFitIndex;
}

// Worst Fit Allocation
int worstFit(struct MemoryBlock memory[], int numBlocks, int requestSize) {
    int worstFitIndex = -1;
    int worstFitSize = -1;

    for (int i = 0; i < numBlocks; i++) {
        if (!memory[i].allocated && memory[i].size >= requestSize && memory[i].size > worstFitSize) {
            worstFitIndex = i;
            worstFitSize = memory[i].size;
        }
    }

    if (worstFitIndex != -1) {
        memory[worstFitIndex].allocated = 1;
    }

    return worstFitIndex;
}

int main() {
    struct MemoryBlock memory[MEMORY_SIZE];

    int choice, requestSize;
    initializeMemory(memory, MEMORY_SIZE);

    while (1) {
        printf("Memory Allocation Strategies:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        printf("Enter memory request size: ");
        scanf("%d", &requestSize);

        int blockIndex = -1;

        switch (choice) {
            case 1:
                blockIndex = firstFit(memory, MEMORY_SIZE, requestSize);
                break;
            case 2:
                blockIndex = bestFit(memory, MEMORY_SIZE, requestSize);
                break;
            case 3:
                blockIndex = worstFit(memory, MEMORY_SIZE, requestSize);
                break;
            default:
                printf("Invalid choice.\n");
                continue;
        }

        if (blockIndex != -1) {
            printf("Memory allocated in Block %d\n", blockIndex);
        } else {
            printf("Memory allocation failed. No suitable block found.\n");
        }

        displayMemory(memory, MEMORY_SIZE);
    }

    return 0;
}

