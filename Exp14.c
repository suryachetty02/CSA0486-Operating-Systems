#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_FILENAME_LENGTH 20

struct File {
    char name[MAX_FILENAME_LENGTH];
    int size;
};

struct Directory {
    struct File files[MAX_FILES];
    int num_files;
};

void initializeDirectory(struct Directory *dir) {
    dir->num_files = 0;
}

void createFile(struct Directory *dir, const char *filename, int size) {
    if (dir->num_files >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }

    if (strlen(filename) >= MAX_FILENAME_LENGTH) {
        printf("Filename is too long. Maximum length is %d characters.\n", MAX_FILENAME_LENGTH - 1);
        return;
    }

    strcpy(dir->files[dir->num_files].name, filename);
    dir->files[dir->num_files].size = size;
    dir->num_files++;

    printf("File '%s' created with size %d bytes.\n", filename, size);
}

void displayFiles(struct Directory *dir) {
    printf("Files in the directory:\n");
    for (int i = 0; i < dir->num_files; i++) {
        printf("%s (%d bytes)\n", dir->files[i].name, dir->files[i].size);
    }
}

int main() {
    struct Directory directory;
    initializeDirectory(&directory);

    while (1) {
        int choice;
        char filename[MAX_FILENAME_LENGTH];
        int size;

        printf("\nSingle-Level Directory Management:\n");
        printf("1. Create a file\n");
        printf("2. Display files\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the filename (up to %d characters): ", MAX_FILENAME_LENGTH - 1);
                scanf("%s", filename);
                printf("Enter the file size (in bytes): ");
                scanf("%d", &size);
                createFile(&directory, filename, size);
                break;
            case 2:
                displayFiles(&directory);
                break;
            case 3:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

