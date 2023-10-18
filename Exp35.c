#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#define MAX_BLOCKS 100

// Data structure for a disk block
struct DiskBlock {
    int data; // Data stored in the block
};

// Data structure for an index block
struct IndexBlock {
    int blockPointers[MAX_BLOCKS]; // Pointers to file blocks
    int numBlocks;                // Number of blocks in the file
};

// Data structure for a file
struct File {
    char name[100];            // File name
    struct IndexBlock index;   // Index block for the file
};

struct DiskBlock disk[MAX_BLOCKS];  // Simulated disk blocks
struct File files[10];              // Array to hold files (up to 10 files)

// Initialize the disk blocks
void initializeDisk() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        disk[i].data = -1; // Initialize data to -1 to represent empty block
    }
}

// Create a new file
int createFile(char name[]) {
    for (int i = 0; i < 10; i++) {
        if (files[i].index.numBlocks == 0) {
            struct File newFile;
            	strcpy(newFile.name, name);
            newFile.index.numBlocks = 0;
            files[i] = newFile;
            return i;
        }
    }
    return -1;  // No free slots for a new file
}

// Allocate a block to a file
void allocateBlock(int fileIndex, int blockData) {
    struct IndexBlock* index = &files[fileIndex].index;
    if (index->numBlocks < MAX_BLOCKS) {
        index->blockPointers[index->numBlocks] = blockData;
        index->numBlocks++;
    } else {
        printf("File is full. Cannot allocate more blocks.\n");
    }
}

// Display the blocks allocated to a file
void displayFileBlocks(int fileIndex) {
    struct IndexBlock* index = &files[fileIndex].index;
    printf("File: %s\n", files[fileIndex].name);
    printf("Blocks allocated: ");
    for (int i = 0; i < index->numBlocks; i++) {
        printf("%d -> ", index->blockPointers[i]);
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
