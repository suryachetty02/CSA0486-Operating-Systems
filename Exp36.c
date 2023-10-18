#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

// Data structure for a disk block
struct DiskBlock {
    int data;                // Data stored in the block
    struct DiskBlock* next;  // Pointer to the next block
};

// Data structure for a file
struct File {
    char name[100];            // File name
    struct DiskBlock* first;   // Pointer to the first block
    struct DiskBlock* last;    // Pointer to the last block
};

struct DiskBlock disk[MAX_BLOCKS];  // Simulated disk blocks
struct File files[10];              // Array to hold files (up to 10 files)

// Initialize the disk blocks
void initializeDisk() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i].data = -1; // Initialize data to -1 to represent empty block
        disk[i].next = NULL;
    }
}

// Create a new file
int createFile(char name[]) {
    for (int i = 0; i < 10; i++) {
        if (files[i].first == NULL) {
            struct File newFile;
            strcpy(newFile.name, name);
            newFile.first = NULL;
            newFile.last = NULL;
            files[i] = newFile;
            return i;
        }
    }
    return -1;  // No free slots for a new file
}

// Allocate a block to a file
void allocateBlock(int fileIndex, int blockData) {
    struct DiskBlock* newBlock = &disk[blockData];
    if (files[fileIndex].first == NULL) {
        files[fileIndex].first = newBlock;
        files[fileIndex].last = newBlock;
    } else {
        files[fileIndex].last->next = newBlock;
        files[fileIndex].last = newBlock;
    }
    newBlock->next = NULL;
    newBlock->data = blockData;
}

// Display the blocks allocated to a file
void displayFileBlocks(int fileIndex) {
    struct DiskBlock* current = files[fileIndex].first;
    printf("File: %s\n", files[fileIndex].name);
    printf("Blocks allocated: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("End of file.\n");
}

int main() {
    initializeDisk();

    int choice, fileIndex, blockData;
    char name[100];

    while (1) {
        printf("1. Create a file\n2. Allocate a block\n3. Display file blocks\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the file name: ");
                scanf("%s", name);
                fileIndex = createFile(name);
                if (fileIndex != -1) {
                    printf("File created with index %d\n", fileIndex);
                } else {
                    printf("No free slots for a new file\n");
                }
                break;
            case 2:
                printf("Enter the file index: ");
                scanf("%d", &fileIndex);
                printf("Enter the block data: ");
                scanf("%d", &blockData);
                allocateBlock(fileIndex, blockData);
                break;
            case 3:
                printf("Enter the file index: ");
                scanf("%d", &fileIndex);
                displayFileBlocks(fileIndex);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
